/*
 *  file: main.cpp
 *  Author: Daniel Zarate
 *  Created on November 11, 2023
 *  Purpose: 12 Changed Board::listAdjacent so that it fills the list with 
 *              board->first instead of board->second
 *              Board::hasAdjacent now uses set which is filled with board->second
 *              wrote Board::isAdjacent function
 *              small changes to spots where it asks for user to enter a key
 */
 //System Libraries
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime> 
#include <queue>

#include "Player.h"

using namespace std;

//User Libraries

//Global Constants

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) 
{

    //Set random seed
    srand(static_cast<unsigned int> (time(0)));
    
    int numTurn = 0;
    Player p;
    
    cout << "\t              ORBITO" << endl;
    cout << "\tGo with the flow & get 4-in-a-row!" << endl;
    cout << endl;
    cout << "  How to play:" << endl;
    cout << "     1) Select an opponent's piece and move" << endl;
    cout << "        it to an adjacent, free spot (optional)" << endl;
    cout << "     2) Choose where to place your piece" << endl;
    cout << "     3) The board will orbit at the end of every turn" << endl;
    cout << "     4) Get 4 in a row to win!" << endl;
    cout << "  If no more moves can be played, the board will orbit 5 times" << endl;
    cout << endl;
    cout << " Note: When entering a position on the board, enter " << endl;
    cout << "       the letter followed by the number without spaces" << endl;
    cout << "            Good: \"A1\" \"c3\"    Bad: \"1A\" \"c 3\"" << endl;
    cout << endl << endl;
    
    
    while(p.startTurn(numTurn)) numTurn++;

    
    //Exit the Program
    return 0;
}