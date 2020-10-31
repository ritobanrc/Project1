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
#include "SideData.h"


class Game {
public:
    Game();
    virtual ~Game();

    void PlayGame(bool);
    bool AddPiece(Side);

    struct Move {
        Piece* piece; // if nullptr, that means the piece must be created
        Square* target;
    };

    std::deque<Move> GetPossibleMoves();
    void ApplyMove(Move);
    void NextTurn();

    Board board;
    DiceRoller diceRoller;

    // This is public because there's a getter inside SideData
    SideData<std::set<Piece*>> pieces;
    SideData<int> remainingPieces;
    SideData<int> completedPieces;
    SideData<std::list<Square*>> path;

private:
    Side turn = white;
};

#endif /* GAME_H */

