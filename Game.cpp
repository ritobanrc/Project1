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

    // End at nullptr
    whitePath.push_back(nullptr);
    blackPath.push_back(nullptr);
}

Game::~Game() {
}

void Game::PlayGame() {
    using namespace std::chrono_literals;
    while (true) {
        board.ShowBoard();

        Display::PrintBold("Turn: ");
        Display::BeginColor(COLOR["White"].AsFG());
        Display::PrintBold("WHITE");
        Display::EndFormat();
        Display::NewLine();

        Display::Print("Press ENTER to roll dice...");
        std::cin.ignore(INT32_MAX, '\n');

        diceRoller.RollDice();
        diceRoller.ShowDiceRoller();

        Display::PrintUnderlined(diceRoller.CountDice());
        if (diceRoller.CountDice() == 0) {
            Display::BeginColor(COLOR.at("Red").AsFG());
            std::cout << "ZERO! Better luck next time!";
            Display::EndFormat();
            return;
        }

        Display::Print("Press ENTER to get possible moves...");
        std::cin.get();

        auto moves = GetPossibleMoves();

        if (moves.empty()) {
            Display::BeginColor(COLOR.at("Red").AsFG());
            Display::Print("No possible moves!");
            continue;
        }

        int moveNumber = 1;
        std::for_each(moves.begin(), moves.end(), 
                [&](Game::Move m){ 
                m.target->moveNumber = std::make_pair(moveNumber, true);
                moveNumber++; 
        });

        Display::PrintBold("Possible Moves: \n");

        board.ShowBoard();

        std::cout << "Please select a move between 1 and " << moves.size(); 
        Display::NewLine();

        int moveSelected;
        std::cin >> moveSelected;
        this->ApplyMove(moves.at(moveSelected - 1));
        board.ClearPossibleMoves();

        //std::cin.ignore();

        std::this_thread::sleep_for(1s);
    }

}

std::deque<Game::Move> Game::GetPossibleMoves() {
    int rolled = diceRoller.CountDice();
    auto moves = std::deque<Game::Move>();

    if (rolled == 0) {
        return moves; // welp you miss a turn!
    }

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


    std::set<Piece*>& thisSidePieces = pieces.Get(turn);
    for (auto piece = thisSidePieces.begin(); piece != thisSidePieces.end(); piece++) {
        auto pos = (*piece)->GetPosition();
        // advance the iterator by however much we rolled
        int n = rolled;
        while (n > 0) {
            n--;
            pos++;
        }

        Square* s = *pos;
        if (s->piece == nullptr) {
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
        piece = new Piece(path.Get(s).cbegin());
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

        Piece* piece = new Piece(pos);
        (*pos)->piece = piece;
        pieces.Get(turn).insert(piece);
        remainingPieces.Get(turn)--;

    } else {
        Square* currentPos = *(m.piece->GetPosition());
        currentPos->piece = nullptr;
        m.piece->AdvanceUntil(m.target);
        m.target->piece = m.piece;
    }
}
