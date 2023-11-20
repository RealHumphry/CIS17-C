/*
 * File:   Player.h
 * Author: Daniel
 *
 * Created on November 11, 2023, 11:00 PM
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "Board.h"
#include <queue>

class Player {
    
private:    
    queue<int> player;
    Board b;
    
    void refill();
    int getTurn();
    
public:
    Player(){refill();}
    int startTurn(int);
};

#endif /* PLAYER_H */

