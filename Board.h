/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Board.h
 * Author: ritoban
 *
 * Created on October 25, 2020, 6:56 PM
 */

#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "Square.h"
#include "SideData.h"

constexpr int BOARD_WIDTH = 8;
constexpr int BOARD_HEIGHT = 3;

class Board {
public:
    Board();
    virtual ~Board();

    void ShowBoard();
    Square* GetSquare(int x, int y) { return grid[y][x]; }
    void ClearPossibleMoves();

    SideData<Square*> startSquare;
    SideData<int> endMoveNumber = SideData<int>(-1, -1);
private:
    std::array<std::array<Square*, BOARD_WIDTH>, BOARD_HEIGHT> grid;

};

#endif /* BOARD_H */

