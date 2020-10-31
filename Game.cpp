/* 
 * File:   Game.cpp
 * Author: ritoban
 * 
 * Created on October 25, 2020, 6:56 PM
 */

#include "Game.h"
#include "Piece.h"
#include "Display.h"
#include "SideData.h"
#include <set>
#include <list>
#include <deque>
#include <algorithm>
#include <utility>
#include <thread>
#include <cstdlib>

Game::Game() : pieces(std::set<Piece*>(), std::set<Piece*>()), remainingPieces(7, 7), completedPieces(0, 0), path(std::list<Square*>(), std::list<Square*>()) {
    std::list<Square*>& whitePath = path.Get(white);
    std::list<Square*>& blackPath = path.Get(black);

    for (int i = 3; i >= 0; i--) {
        whitePath.push_back(board.GetSquare(i, 2));
        blackPath.push_back(board.GetSquare(i, 0));
    }

    for (int i = 0; i < 8; i++) {
        whitePath.push_back(board.GetSquare(i, 1));
        blackPath.push_back(board.GetSquare(i, 1));
    }

    for (int i = 7; i >= 6; i--) {
        whitePath.push_back(board.GetSquare(i, 2));
        blackPath.push_back(board.GetSquare(i, 0));
    }
}

std::string side_str(Side s) {
    if (s == white) {
        return "WHITE";
    } else {
        return "BLACK";
    }
}


Game::~Game() {
}

void Game::PlayGame(bool againstComputer) {
    while (true) {
        Display::BeginBold();
        std::cout << "BLACK Remaining Pieces: " << remainingPieces.Get(black) << std::endl;
        std::cout << "BLACK Finished Pieces: " << completedPieces.Get(black) << std::endl;
        Display::EndFormat();
        board.ShowBoard();
        Display::BeginBold();
        std::cout << "WHITE Remaining Pieces: " << remainingPieces.Get(white) << std::endl;
        std::cout << "WHITE Finished Pieces: " << completedPieces.Get(white) << std::endl;
        Display::EndFormat();

        Display::PrintBold("Turn: ");
        if (turn == white) {
            Display::BeginColor(COLOR["Green"].AsFG());
            Display::PrintBold("WHITE");
        } else {
            Display::BeginColor(COLOR["Black"].AsFG());
            Display::PrintBold("BLACK");
        }
        Display::EndFormat();
        Display::NewLine();

        Display::Print("Press ENTER to roll dice...");
        std::cin.ignore();

        diceRoller.RollDice();
        diceRoller.ShowDiceRoller();

        if (diceRoller.CountDice() == 0) {
            Display::BeginColor(COLOR.at("Red").AsFG());
            std::cout << "ZERO! Better luck next time!";
            Display::NewLine();
            Display::EndFormat();
            NextTurn();
            continue;
        }

        if (!againstComputer || turn == white) {
            Display::Print("Press ENTER to get possible moves...");
            std::cin.ignore();
        }

        auto moves = GetPossibleMoves();

        if (moves.empty()) {
            Display::BeginColor(COLOR.at("Red").AsFG());
            Display::Print("No possible moves!");

            NextTurn();
            continue;
        }

        int moveNumber = 1;
        std::cout << "Got here move number" << std::endl;
        std::for_each(moves.begin(), moves.end(), 
            [&](Game::Move m){ 
                if (m.target != nullptr) {
                    m.target->moveNumber = std::make_pair(moveNumber, true);
                } else {
                    board.endMoveNumber.Get(turn) = moveNumber;
                }
                moveNumber++; 
        });

        Display::PrintBold("Possible Moves: \n");

        int moveSelected;
        if (!againstComputer || turn == white) {
            board.ShowBoard();

            std::cout << "Please select a move between 1 and " << moves.size(); 
            Display::NewLine();

            std::cin >> moveSelected;
            std::cin.ignore();
        } else {
            moveSelected = rand() % moves.size() + 1;
        }
        Move move = moves.at(moveSelected - 1);
        this->ApplyMove(move);
        board.ClearPossibleMoves();

        if (move.target != nullptr && move.target->GetStar()) {
            Display::BeginColor(COLOR["Magenta"].AsFG());
            Display::PrintBold("You landed on a Star! You get another turn!");
            Display::NewLine();
            Display::EndFormat();

            continue;
        }

        if (completedPieces.Get(turn) == 7) {
            Display::BeginBold();
            std::cout << side_str(turn) << " WINS!!!!!!" << std::endl;
            return;
        }


        NextTurn();
    }

}

std::deque<Game::Move> Game::GetPossibleMoves() {
    int rolled = diceRoller.CountDice();
    auto moves = std::deque<Game::Move>();

    if (rolled == 0) {
        return moves; // welp you miss a turn!
    }

    if (remainingPieces.Get(turn) > 0) {
        auto thisSidePath = this->path.Get(turn).begin();
        // we can move up to rolled number of times
        // start at 1 because we're adding a new piece to the board
        for (int i = 1; i < rolled; i++) {
          thisSidePath++;
        }
        if ((*thisSidePath)->piece == nullptr) {
          // it's empty!
          auto m = Game::Move();
          m.piece = nullptr;
          m.target = *thisSidePath;
          moves.push_back(m);
        }
    }


    std::set<Piece*>& thisSidePieces = pieces.Get(turn);

    for (auto piece = thisSidePieces.begin(); piece != thisSidePieces.end(); piece++) {
        auto pos = (*piece)->GetPosition();
        // advance the iterator by however much we rolled
        int n = rolled;
        auto end = this->path.Get((*piece)->side).cend();
        while (n > 0 && pos != end) {
            n--;
            pos++;
        }

        if (pos == end) {
            if (n == 0) {
                // Yay! The piece made it to the end
                auto m = Game::Move();
                m.piece = *piece;
                m.target = nullptr;
                moves.push_back(m);
            } 
            // We rolled something past the end, this is not a valid move
            continue;
        }

        Square* s = *pos;
        if (s->piece == nullptr || (s->piece->side != (*piece)->side && s->GetStar() == false)) {
            // either we're at the end, we're moving to an empty square, or we can capture a piece.
            auto m = Game::Move();
            m.piece = *piece;
            m.target = *pos;
            moves.push_back(m);
        }
    }

    return moves;
}

/// Tries to add a piece to the board. Returns false if the start square is already occupied.
bool Game::AddPiece(Side s) {
    Piece* piece;

    if (board.startSquare.Get(s)->piece == nullptr) {
        piece = new Piece(s, path.Get(s).cbegin());
        pieces.Get(s).insert(piece);
        remainingPieces.Get(s)--;
        board.startSquare.Get(s)->piece = piece;
    } else {
        return false;
    }
    return true;
}

void Game::ApplyMove(Game::Move m) {
    if (m.piece == nullptr) {
        std::list<Square*>::iterator pos = path.Get(turn).begin();
        while (*(pos) != m.target) {
            pos++;
        }

        Piece* piece = new Piece(turn, pos);
        (*pos)->piece = piece;
        pieces.Get(turn).insert(piece);
        remainingPieces.Get(turn)--;

    } else {
        Square* currentPos = *(m.piece->GetPosition());
        currentPos->piece = nullptr;

        if (m.target == nullptr) {
            Display::BeginColor(COLOR["Magenta"].AsFG());
            Display::Print("Success! ");
            Display::Print(side_str(turn));
            Display::Print(" completes 1 piece! \n");
            Display::EndFormat();

            this->pieces.Get(turn).erase(m.piece);

            completedPieces.Get(turn)++;
            return;
        }

        m.piece->AdvanceUntil(m.target);
        if (m.target->piece != nullptr) {
            // this piece just got captured!
            Side capturedSide = m.target->piece->side;
            this->pieces.Get(capturedSide).erase(m.target->piece);
            this->remainingPieces.Get(capturedSide) += 1;
        }
        m.target->piece = m.piece;
    }
}

void Game::NextTurn() {
    if (turn == white) {
        turn = black;
    } else {
        turn = white;
    }
}
