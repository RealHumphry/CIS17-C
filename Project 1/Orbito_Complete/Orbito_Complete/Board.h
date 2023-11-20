 /*
 * File:   Board.h
 * Author: Daniel
 *
 * Created on November 11, 2023, 7:06 PM
 */

#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <list>
#include <string> 
#include <iterator>

using namespace std;


class Board {

private:
    int size;
    map<string, char> board;
    bool hasAdjacent(string);
    bool isAdjacent(string, string);
    void listAdjacent(string, list<string>&);
    
public:
    Board();
    void printBoard();
    void editBoard(int);
    void orbit();
    void movePiece(int);
    int findStalemate();
    int findWin();
};

#endif /* BOARD_H */

