/* 
 * File:   main.cpp
 * Author: ritoban
 *
 * Created on October 25, 2020, 6:55 PM
 */

#include <iostream>
#include "Display.h"
#include "Color.h"
#include "Board.h"

#include <map>
#include <string>


using namespace std;

int main(int argc, char** argv) {

    Display::BeginColor(COLOR["Red"].AsFG());
    Display::BeginBold();
    cout << "Welcome to the Royal Game of Ur!";
    Display::EndFormat();
    Display::NewLine();

    Board board;

    board.ShowBoard();

    return 0;
}

