/* 
 * File:   Piece.cpp
 * Author: ritoban
 * 
 * Created on October 26, 2020, 4:07 PM
 */

#include "Piece.h"
#include <list>

Piece::Piece(std::list<Square*>::const_iterator path) : path(path) {
}

Piece::Piece(const Piece& orig) {
}

Piece::~Piece() {
}

