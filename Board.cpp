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
#include "Square.h"

Board::Board() : startSquare(nullptr, nullptr) {
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            if (row != 1 && (col == 4 || col == 5)) {
                this->grid[row][col] = nullptr;
                continue;
            }
            this->grid[row][col] = new Square();
        }
    }

    grid[0][0]->SetStar(true);
    grid[2][0]->SetStar(true);
    grid[1][3]->SetStar(true);
    grid[0][6]->SetStar(true);
    grid[2][6]->SetStar(true);

    startSquare.Get(white) = grid[2][3];
    startSquare.Get(black) = grid[0][3];
}

Board::~Board() {
}

void Board::ShowBoard() {
    Display::BeginColor(COLOR["Blue"].AsFG());
    Display::NewLine();

    for (int row = 0; row < BOARD_HEIGHT; row++) {
        int start = row == 0 ? 0 : 1;
        for (int y = start; y < CELL_HEIGHT; y++) {
            for (int col = 0; col < BOARD_WIDTH; col++) {
                for (int x = 0; x < CELL_WIDTH; x++) {
                    char c;
                    if (grid[row][col] == nullptr) {
                        if (x == CELL_WIDTH - 1 || (x == 0 && grid[row][col - 1] == nullptr)) {
                            continue;
                        }
                        if (y == CELL_HEIGHT - 1 && row < BOARD_HEIGHT - 1 && grid[row + 1][col] != nullptr) {
                            c = grid[row + 1][col]->GetDisplayCharAt(x + 1, 0);
                        } else {
                            c = ' ';
                        }
                    }
                    else {
                        if (x == 0) {
                            if (col == 0 || grid[row][col - 1] == nullptr) {
                                c = grid[row][col]->GetDisplayCharAt(x, y);
                            } else {
                                continue;
                            }
                        } else {
                            c = grid[row][col]->GetDisplayCharAt(x, y);
                        }
                    }

                    std::cout << c;
                }
            }
            Display::NewLine();
        }
    }
    Display::EndFormat();
}

void Board::ClearPossibleMoves() {
    for (auto row = grid.cbegin(); row != grid.cend(); row++) {
        for (auto square = row->cbegin(); square != row->cend(); square++) {
            Square* s = *square;
            if (s != nullptr && s->moveNumber.second) {
                s->moveNumber.second = false;
            }
        }
    }
}
