/* 
 * File:   Square.cpp
 * Author: ritoban
 * 
 * Created on October 26, 2020, 8:37 AM
 */

#include "Square.h"
#include <string>
#include <vector>

Square::Square() {
    this->isStarSquare = false;
}

Square::Square(const Square& orig) {
}

Square::~Square() {
}

char Square::GetDisplayCharAt(int i, int j) {
    bool horizontalEdge = i == 0 || i == CELL_WIDTH - 1;
    bool verticalEdge = j == 0 || j == CELL_HEIGHT - 1;

    const std::vector<std::string> star ={
R"(     ,    )",
R"(  __/ \__ )",
R"(  \     / )",
R"(  /_   _\ )",
R"(    \ /   )",
R"(     '    )" };

    if (horizontalEdge && verticalEdge) {
        return '+';
    } else if (horizontalEdge) {
        return '|';
    } else if (verticalEdge) {
        return '-';
    } else {
        if (isStarSquare && (j - 1) < star.size() && i < star[0].size()) {
            return star[j - 1][i];
        } else {
            return ' ';
        }
    }
}
