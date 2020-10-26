/* 
 * File:   DiceRoller.cpp
 * Author: ritoban
 * 
 * Created on October 26, 2020, 12:20 PM
 */

#include "DiceRoller.h"
#include "Display.h"
#include <set>
#include <iterator>
#include <cstdlib>
#include <iostream>
#include <vector>

DiceRoller::DiceRoller() {
    dice.reset();
}

DiceRoller::DiceRoller(const DiceRoller& orig) {
}

DiceRoller::~DiceRoller() {
}

void DiceRoller::RollDice() {
    dice.reset();
    for (int i = 0; i < dice.size(); i++) {
        dice.set(i, rand() % 2);
    }
}

void DiceRoller::ShowDiceRoller() {
    const std::vector<std::string> diceArt ={
R"(    ,    )",
R"(   /^\   )",
R"(  /   \  )",
R"( /_____\ )" };

    std::vector<std::string> diceWithPip = diceArt;
    diceWithPip[2][4] = '.';

    for (int y = 0; y < diceArt.size(); y++) {
        for (int d = 0; d < dice.size(); d++) {
            if (this->dice[d]) {
                Display::PrintBold(diceWithPip.at(y));
            } else {
                std::cout << diceArt.at(y);
                //Display::PrintBold(diceArt.at(y));
            }
        }
        std::cout << std::endl;
    }
}
