/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Square.h
 * Author: ritoban
 *
 * Created on October 26, 2020, 8:37 AM
 */

#ifndef SQUARE_H
#define SQUARE_H

#include <utility>

class Piece;

class Square {
public:
    Square(int);
    Square(const Square& orig);
    virtual ~Square();

    char GetDisplayCharAt(int, int);
    void SetStar(bool val) { isStarSquare = val; }
    bool GetStar() { return isStarSquare; }

    Piece* piece;
    // The int describes the move number to display, the bool is true if it should be shown.
    std::pair<int, bool> moveNumber;
    int xPos; // for sorting
private:
    bool isStarSquare;

};


const int CELL_WIDTH = 12;
const int CELL_HEIGHT = 8;

#endif /* SQUARE_H */

