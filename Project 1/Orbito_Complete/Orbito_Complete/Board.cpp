/*
 * File:   Board.cpp
 * Author: Daniel
 * 
 * Created on November 11, 2023, 7:06 PM
 */

#include <iostream>
#include <stack>
#include <list>
#include <set>
#include <algorithm>
#include "Board.h"


using namespace std;

Board::Board()
{
    size = 16;
    
    for (int i = 1; i <= size; i++)
    {
        string s;
        char* temp = new char[2];
        temp[0] = (i-1)/4 + 'A';
        temp[1] = (i%4 == 0) ? 4 + '0' : (i % 4) + '0';
        s.append(temp);
        
        board.insert(make_pair(s, ' '));
    }
}
void Board::printBoard()
{
    int perLine = 4;
    
    map<string, char>::iterator it;
    int i = 0;
    cout << endl;
    cout << "      1  2  3  4" << endl;
    cout << "    -------------";
    for (it = board.begin(); it != board.end(); it++)
    {
        if (i % perLine == 0) cout << endl << "  " << static_cast<char>(i/perLine + 'A') << " | ";
        cout << it->second << "  ";
        i++;
    }
    cout << endl;
}
void Board::editBoard(int p)
{
    string key;
    bool valid;
    
    do {
        cout << endl << "Enter position to place your piece  "; 
        cin >> key;
        valid = true;
        key[0] = toupper(key[0]);
        
        if(board.count(key)==0){
            cout << "That spot does not exist!" << endl; 
            valid = false;
        }
        else if(board[key]!=' '){
            cout << "That spot is already occupied!" << endl;
            valid = false;
        }
    } while (!valid);
    board[key] = p==1? 'X':'O';
}

void Board::movePiece(int p)
{
    string key, key2;
    bool valid;
    
    do {
        cout << endl << "Enter the position of an opponent's piece ('s' to skip)  ";
        cin >> key;
        valid = true;
        key[0] = toupper(key[0]);
        
        if(key == "S") return;
        if(board.count(key)==0){
            cout << "That spot does not exist!" << endl;
            valid = false;
        }
        else if((board[key]=='X' && p==1) || board[key]==' ' || (board[key]=='O' && p==2)){
            cout << "Choose a spot occupied by your opponent!" << endl;
            valid = false;
        }
        else if(!hasAdjacent(key)){
            cout << "No open adjacent spots to move that piece!" << endl;
            valid = false;
        }
    } while(!valid);
    
    do {
        cout << endl << "Enter position where you want to move that piece ('c' to go back)  ";
        cin >> key2;
        key2[0] = toupper(key2[0]);
        valid = true;
        
        if(key2 == "C"){movePiece(p); return;}
        if(board.count(key2)==0){
            cout << "That spot does not exist!" << endl;
            valid = false;
        }
        else if(!isAdjacent(key, key2)){
            cout << "That spot is not adjacent to the original spot!" << endl;
            valid = false;
        }
        else if(board[key2]!=' '){
            cout << "Choose an empty spot!" << endl;
            valid = false;
        }
    } while(!valid);
    swap(board[key], board[key2]);
}

bool Board::isAdjacent(string spot1, string spot2){
    list<string> l;
    listAdjacent(spot1, l);
    
    if(find(l.begin(), l.end(), spot2) != l.end()) return true;
    else return false;
}
void Board::listAdjacent(string key, list<string> &filList){
    map<string, char>::iterator it;
    list<string> l, l2;
    int altL, altI; //change values for loop and it if special case (col 1 or 4)
    
    if     (key.at(1) == '1'){altL=1; altI=1;}
    else if(key.at(1) == '4'){altL=1; altI=0;}
    else                     {altL=0; altI=0;}
    

    //search row above
    if(key.at(0) != 'A'){
        it = board.find(key);
        it = next(it, -5+altI);
        for(int i=0; i<3-altL; i++) l.push_back((it++)->first); 
    }
    
    //search row where key is
    it = board.find(key);
    it = next(it, -1+altI*2);
    for(int i=0; i<2-altL; i++) {
        l.push_back(it->first);
        it = next(it, 2);
    }
    
    //search row below
    if(key.at(0) != 'D'){
        it = board.find(key);
        it = next(it, 3+altI);    
        for(int i=0; i<3-altL; i++) l.push_back((it++)->first);
    }
    
    l2.resize(l.size()+filList.size());
    merge(l.begin(), l.end(), filList.begin(), filList.end(), l2.begin());
    filList = l2;
}
bool Board::hasAdjacent(string key){
    list<string> l;
    listAdjacent(key,l);
    set<char> s;
    
    for(list<string>::iterator it = l.begin(); it != l.end(); it++){
        s.insert(board[*it]);
    }
    
    if(s.find(' ') != s.end()) return true; //there is an open spot adjacent to the key
    else return false; // there is no open spots adjacent to the key
}

void Board::orbit()
{
    map<string, char>::iterator it2, it = board.begin();
    stack<char> sfil;
    list<char> lfil;
    list<char>::iterator lit;
    
    
    //outer square fill stack
    for(int i = 0; i < 4; i++){     //read A-row (1-4)
        sfil.push((it++)->second);
    }
    it--;
    for(int i = 0; i < 3; i++){     //read 4-col (B-D)
        it = next(it, 4);
        sfil.push(it->second);
    }
    for(int i = 0; i < 3; i++){     //read D-row (1-3)
        sfil.push((--it)->second);
    }
    for(int i = 0; i < 2; i++){     //read 1-col (B-C)
        it = next(it, -4);
        sfil.push(it->second);
    }
    
    //put back stack into map with orbit completed
    it = next(it,4);            //B1->C1
    it->second = sfil.top(); 
    sfil.pop();
    
    it = next(it, 4);
    for(int i = 0; i<4; i++){   //move D-row (1-4)
        (it++)->second = sfil.top();
        sfil.pop();
        
    }
    it--;
    for(int i = 0; i<3; i++){   //move 4-col (A-C)
        it = next(it, -4);
        it->second = sfil.top();
        sfil.pop();
    }
    for(int i = 0; i<3; i++){   //move A-row (1-3)
        (--it)->second = sfil.top();
        sfil.pop();
    }
    it = next(it, 4);       //A1->B1
    it->second = sfil.top();
    sfil.pop();
        
    //it->first == B1 (this is true)
    it = next(it, 5); //it->first == C2
    
    it2 = it++;
    swap(it2->second, it->second);          //C2<->C3
    it = next(it2, -4);
    swap(it2->second, it->second);               //C2<->B2
    it2 = it++;
    swap(it2->second, it->second);               //B2<->B3
    
}

int Board::findStalemate()
{
    list<char> temp;
    for(map<string,char>::iterator it = board.begin(); it != board.end(); it++){
        temp.push_back(it->second); 
    }
    if(count(temp.begin(), temp.end(), 'O') == size/2) return 1;
    else return 0;
}

int Board::findWin()
{
    //this function can be changed to use sets and using equal algorithm function
    
    int w, p1W=0, p2W=0; //# of wins from each player
    map<string, char>::iterator it, it2;
    
    //check down each column
    for(int i=0; i<4; i++)
    {
        it = next(board.begin(), i);
        if(it->second != ' '){
            bool match = true;
            for(int j=1;j<=3;j++)
            {
                it2 = next(it, 4*j);
                if(it2->second != it->second) match = false;
            }
            if(match){
                if(it->second == 'X') p1W++; //player 1 has 4 in a row
                else p2W++; //player 2 has 4 in a row
            }
        }
    }
    
    //check each row left to right
    for(int i=0; i<4; i++)
    {
        it = next(board.begin(), i*4);
        if(it->second != ' '){
            bool match = true;
            for(int j=1; j<=3; j++)
            {
                it2 = next(it, j);
                if(it2->second != it->second) match = false;
            }
            if(match){
                if(it->second == 'X') p1W++; //player 1 has 4 in a row
                else p2W++; //player 2 has 4 in a row
            }
        }
    }
    
    //check diagonal (like this \)
    it=board.begin();
    if(it->second!=' '){
        bool match = true;
        for(int i=1; i<=3; i++)
        {
            it2 = next(it, 5*i);
            if(it2->second != it->second) match = false;
        }
        if(match){
            if(it->second=='X') p1W++;
            else p2W++;
        }
    }
    
    //check diagonal (like this /)
    it= next(board.begin(), 3);
    if(it->second!=' '){
        bool match = true;
        for(int i=1; i<=3; i++)
        {
            it2 = next(it, i*3);
            if(it2->second != it->second) match = false;
        }
        if(match){
            if(it->second=='X') p1W++;
            else p2W++;
        }
    }
    
    
    if(p1W>p2W) return 1;               //PLAYER 1 WINS
    if(p1W<p2W) return 2;               //PLAYER 2 WINS
    if(p1W != 0 && p2W != 0) return 3;  //DRAW
    return 0;                           //still no winner
}