/* 
 * File:   Piece.h
 * Author: ritoban
 *
 * Created on October 26, 2020, 4:07 PM
 */

#ifndef PIECE_H
#define PIECE_H

#include <list>
#include "Square.h"

class Piece {
public:
    Piece(std::list<Square*>::const_iterator);
    Piece(const Piece& orig);
    virtual ~Piece();

private:
    std::list<Square*>::const_iterator path;


};

#endif /* PIECE_H */

