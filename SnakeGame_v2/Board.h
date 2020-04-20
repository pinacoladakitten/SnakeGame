/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Board.h
 * Author: Anthony
 *
 * Created on March 24, 2020, 6:40 PM
 */

#ifndef BOARD_H
#define BOARD_H

#include <cstdlib>              // rand()
#include <iostream>             // cout, cin
#include <Windows.h>            // Used for input buffers WINDOWS ONLY!! (GetAsyncKeyState)
#include <stdlib.h>             // srand()
#include <time.h>               // Get time for setting random seed 
#include "SnakePlayer.h"        // The player

using namespace std;

class Board {
private:
    int frameMax=20000,         // The number of iterations it takes for the frame to update while running
        frame=0,                // The iterator (increases by 1 for each loop)
        rows, cols;             // The number of rows and columns the board has
    
    bool bIsRun = true;         // A toggle to keep the game running
    
    SnakePlayer* player;        // A pointer to the player object
    int pelletX=0, pelletY=0;   // The pellet's X and Y coordinates
    
public:
    Board(int,int);             // Constructor
    virtual ~Board();           // Destructor
    void gameRoom();            // All of the logic contained in the game
    void printBoard();          // Prints the board
};

#endif /* BOARD_H */

