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
#include "SideData.h"

class Piece {
public:
    Piece(Side, std::list<Square*>::const_iterator);
    Piece(const Piece& orig);
    virtual ~Piece();

    std::list<Square*>::const_iterator GetPosition() { return path; }
    void AdvanceUntil(Square*);

    Side side;
private:
    // This is a pointer into the path of where the piece is right now.
    std::list<Square*>::const_iterator path;


};

#endif /* PIECE_H */

