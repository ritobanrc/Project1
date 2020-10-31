/* 
 * File:   main.cpp
 * Author: ritoban
 *
 * Created on October 25, 2020, 6:55 PM
 */

#include "Display.h"
#include "Color.h"
#include "Board.h"
#include "Game.h"
#include "DiceRoller.h"

#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;

int main(int argc, char** argv) {
    srand(0);

    Display::BeginColor(COLOR["Red"].AsFG());
    Display::BeginBold();
    cout << "Welcome to the Royal Game of Ur!";
    Display::EndFormat();
    Display::NewLine();

    cout << R"(
               The Royal Game of Ur is the world's oldest board game
               discovered in Ancient Mesopotamia by Dr. Irving Finkel.

               The game is a race game, with rules similar to Ludo or 
               Parcheesi. Each player has 7 pieces, which they must get
               through the entire board. Each turn, the player rolls the
               4 tetrahedral dice, each with two white marks at two corners.  
               You move forward based on the number of white marks. The first
               player to get all of their pieces off the board wins.
               However, if you land on one of your opponent's pieces, you 
               "capture" that piece and it gets sent back.
               Additionally, the star squares let you roll a second time when
               you land on them, and the central star square is a safe space,
               where you can't be captured.

               Finally, for visibility, this game uses Green to show white pieces.

               HAVE FUN PLAYING!

               For more information, see this video https://www.youtube.com/watch?v=WZskjLq040I.

               To play against the computer, enter 1.
               To play against another human, enter 2.
               )" << std::endl;

    int sel;
    cin >> sel;
    std::cin.ignore();

    bool againstComputer = sel == 1;


    Game game;
    game.PlayGame(againstComputer);

    return 0;
}

