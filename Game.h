/* 
 * File:   Game.h
 * Author: ritoban
 *
 * Created on October 25, 2020, 6:56 PM
 */

#ifndef GAME_H
#define GAME_H

#include <set>
#include <list>
#include <deque>
#include "Piece.h"
#include "Board.h"
#include "DiceRoller.h"

enum Side { white, black };

class Game {
public:
    Game();
    Game(const Game& orig);
    virtual ~Game();

    void PlayGame();
    bool AddPiece(Side);

    struct Move {
        Piece* piece; // if nullptr, that means the piece must be created
        Square* target;
    };

    std::deque<Move> GetPossibleMoves();

    Board board;
    DiceRoller diceRoller;
private:
    std::set<Piece*> whitePieces;
    std::set<Piece*> blackPieces;

    int remainingWhitePieces;
    int remainingBlackPieces;

    int completedWhitePieces;
    int completedBlackPieces;

    std::list<Square*> whitePath;
    std::list<Square*> blackPath;

    inline std::list<Square*>& GetPath(Side s) {
        if (s == white) {
            return this->whitePath;
        } else {
            return this->blackPath;
        }
    }


    Side turn = white;
};

#endif /* GAME_H */

