/* 
 * File:   Board.cpp
 * Author: ritoban
 * 
 * Created on October 25, 2020, 6:56 PM
 */

#include <iostream>
#include <algorithm>

#include "Board.h"
#include "Color.h"
#include "Display.h"

const int CELL_WIDTH = 10;
const int CELL_HEIGHT = 4;

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 3;

Board::Board() {
}

Board::Board(const Board& orig) {
}

Board::~Board() {
}

void display_edge_row(bool skip_middle) {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        char cInside = '-';
        char cEdge = '+';
        if (skip_middle && (i == 4 || i == 5)) {
          cInside = ' ';
          if (i == 5)
              cEdge = ' ';
        }

        std::cout << cEdge;

        for (int j = 0; j < CELL_WIDTH; j++) {
          std::cout << cInside;
        }
    }
    std::cout << '+' << std::endl;
}

void display_empty_row(bool skip_middle) {
    for (int i = 0; i < BOARD_WIDTH; i++) {

        char c = '|';
        if (skip_middle && i == 5) {
            c = ' ';
        }

        std::cout << c;
        for (int j = 0; j < CELL_WIDTH; j++) {
            std::cout << ' ';
        }
    }
    std::cout << '|' << std::endl;
}

void Board::ShowBoard() {
    Display::BeginColor(COLOR["Yellow"].AsFG());

    for (int row = 0; row < BOARD_HEIGHT; row++) {
        display_edge_row(row == 0);
        for (int i = 0; i < CELL_HEIGHT; i++)
            display_empty_row(row != 1);
    }
    display_edge_row(true);
}
