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
#include "Piece.h"
#include "Board.h"

enum Side { white, black };

class Game {
public:
    Game();
    Game(const Game& orig);
    virtual ~Game();

    bool AddPiece(Side);

    Board board;
private:
    std::set<Piece*> whitePieces;
    std::set<Piece*> blackPieces;

    int remainingWhitePieces;
    int remainingBlackPieces;

    int completedWhitePieces;
    int completedBlackPieces;

    std::list<Square*> whitePath;
    std::list<Square*> blackPath;

};

#endif /* GAME_H */

