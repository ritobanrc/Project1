/* 
 * File:   Game.cpp
 * Author: ritoban
 * 
 * Created on October 25, 2020, 6:56 PM
 */

#include "Game.h"
#include "Piece.h"
#include <set>
#include <list>

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
