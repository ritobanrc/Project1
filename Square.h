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

//#include "Piece.h"
//
class Piece;

class Square {
public:
    Square();
    Square(const Square& orig);
    virtual ~Square();

    char GetDisplayCharAt(int, int);
    void SetStar(bool val) { isStarSquare = val; }

    Piece* piece;
private:
    bool isStarSquare;

};


const int CELL_WIDTH = 12;
const int CELL_HEIGHT = 8;

#endif /* SQUARE_H */

