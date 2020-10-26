/* 
 * File:   main.cpp
 * Author: ritoban
 *
 * Created on October 25, 2020, 6:55 PM
 */

#include "Display.h"
#include "Color.h"
#include "Board.h"
#include "DiceRoller.h"

#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;

int main(int argc, char** argv) {
    srand(time(0));

    Display::BeginColor(COLOR["Red"].AsFG());
    Display::BeginBold();
    cout << "Welcome to the Royal Game of Ur!";
    Display::EndFormat();
    Display::NewLine();

    Board board;

    board.ShowBoard();

    DiceRoller roller;
    roller.RollDice();
    roller.ShowDiceRoller();

    return 0;
}

