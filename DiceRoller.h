/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DiceRoller.h
 * Author: ritoban
 *
 * Created on October 26, 2020, 12:20 PM
 */

#ifndef DICEROLLER_H
#define DICEROLLER_H

#include <set>
#include <bitset>

class DiceRoller {
public:
    DiceRoller();
    DiceRoller(const DiceRoller& orig);
    virtual ~DiceRoller();

    void RollDice();
    void ShowDiceRoller();
private:

    std::bitset<4> dice;
};

#endif /* DICEROLLER_H */

