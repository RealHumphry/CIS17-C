/*
 * File:   Player.cpp
 * Author: Daniel
 * 
 * Created on November 11, 2023, 11:00 PM
 */

#include "Player.h"
#include <iostream>

using namespace std;

void Player::refill()
{
    player.push(1);
    player.push(2);
}
int Player::getTurn()
{
    int p = player.front();
    player.pop();
    if(player.empty()) refill();
    return p;
}
int Player::startTurn(int t)
{
    int p = getTurn();
    cout << endl << endl;
    cout << "Player " << p << "'s turn: " << endl;
    b.printBoard();
    
    cout << "You are ";
    if(p==1) cout << "X" << endl;
    if(p==2) cout << "O" << endl;
    
    if (t!=0)b.movePiece(p);
    b.editBoard(p);
    b.orbit();
    
   
    int w = b.findWin();
    if(w>0) {
        b.printBoard();
        if(w==1) cout << "Player 1 wins!" << endl;
        else if(w==2) cout << "Player 2 wins!" << endl;
        else if(w==3) cout << "It's a tie!" << endl;
        return 0;
    }
    else{
        if(b.findStalemate()) {
            cout << "No more moves can be played! Orbiting board 5 times:";
            for(int i=0; i<5; i++) b.orbit();
            
            w = b.findWin();
            b.printBoard();
            if(w==1) cout << "Player 1 wins!" << endl;
            else if(w==2) cout << "Player 2 wins!" << endl;
            else if(w==3) cout << "It's a tie!" << endl;
            return 0;
        }
    }
    return 1;
}


