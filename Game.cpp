/* 
 * File:   Game.cpp
 * Author: ritoban
 * 
 * Created on October 25, 2020, 6:56 PM
 */

#include "Game.h"
#include "Piece.h"
#include "Display.h"
#include <set>
#include <list>
#include <deque>
#include <algorithm>
#include <utility>

Game::Game() {
    remainingWhitePieces = remainingBlackPieces = 7;
    completedWhitePieces = completedBlackPieces = 0;

    whitePieces = std::set<Piece*>();
    blackPieces = std::set<Piece*>();

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

Game::Game(const Game& orig) {
}

Game::~Game() {
}

void Game::PlayGame() {
    board.ShowBoard();

    Display::PrintBold("Turn: ");
    Display::BeginColor(COLOR["White"].AsFG());
    Display::PrintBold("WHITE");
    Display::EndFormat();
    Display::NewLine();

    Display::Print("Press any key to roll dice...");
    std::cin.ignore();

    diceRoller.RollDice();
    diceRoller.ShowDiceRoller();

    auto moves = GetPossibleMoves();
    int moveNumber = 0;
    std::for_each(moves.begin(), moves.end(), [&](Game::Move m){ m.target->moveNumber = std::make_pair(moveNumber, true); moveNumber++; });

    board.ShowBoard();

}

std::deque<Game::Move> Game::GetPossibleMoves() {
    int rolled = diceRoller.CountDice();
    auto moves = std::deque<Game::Move>();

    if (rolled == 0) {
        return moves; // welp you miss a turn!
    }

    auto path = GetPath(turn).begin();;
    // we can move up to rolled number of times
    // start at 1 because we're adding a new piece to the board
    for (int i = 1; i < rolled; i++) {
        path++;
    }
    if ((*path)->piece == nullptr) {
        // it's empty!
        auto m = Game::Move();
        m.piece = nullptr;
        m.target = *path;
        moves.push_back(m);
    }

    return moves;
}

/// Tries to add a piece to the board. Returns false if the start square is already occupied.
bool Game::AddPiece(Side s) {
    Piece* piece;
    switch (s) {
        case white:
            if (board.whiteStartSquare->piece == nullptr) {
                piece = new Piece(whitePath.cbegin());
                whitePieces.insert(piece);
                board.whiteStartSquare->piece = piece;
            } else {
                return false;
            }
            break;
        case black:
            if (board.blackStartSquare->piece == nullptr) {
                piece = new Piece(blackPath.cbegin());
                blackPieces.insert(piece);
                board.blackStartSquare->piece = piece;
            } else {
                return false;
            }
            break;
    }
    return true;
}
