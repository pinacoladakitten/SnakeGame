/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Board.cpp
 * Author: Anthony
 * 
 * Created on March 24, 2020, 6:40 PM
 */

#include "Board.h"

Board::Board(int rows, int cols) {
    // ------Init Vars------
    this->rows = rows;          // Board rows
    this->cols = cols;          // Board cols
    
    // ------Set random seed------
    srand (time(0));
    
    // ------Init Pellet------
    pelletX = rand() % cols;    // Random location on the x-axis in array
    pelletY = rand() % rows;    // Random location on the y-axis in array
}

Board::~Board() {
    //Delete assets
    delete player;
}

void Board::gameRoom(){
    // -----Create player object (constructor args sets where the player loops)-----
    player = new SnakePlayer(rows, cols);
    
    // -----The main logic while the game state is running (TWO checks, end by LSHIFT or if player dies)-----
    while(this->bIsRun && !player->getGameOver())
    {
        // -----Frame logic-----
        (frame>=frameMax) ? frame=0 : frame++;  // Print and update when we reach the frameMax (delay effect)
        
        //-----Get Base Inputs-----
        if(GetAsyncKeyState(VK_LSHIFT))         // Ending the game from input
        {
            bIsRun = false;
        }
        
        //-----Get Player Inputs-----
        player->getInputs();                    // NOTE: We are checking OUTSIDE when the frame updates
                                                // this is to ensure no inputs are skipped
        
        
        //-----On Frame Update-----
        if(frame == frameMax)
        {
            printBoard();           // Print the board
            player->move();         // Update player movement
            
            // When the player hits the pellet
            if(player->getCurX() == pelletX && player->getCurY() == pelletY)
            {
                //Randomize pellet local
                pelletX = rand() % cols;
                pelletY = rand() % rows;
                
                //Increase player tail size
                player->addToArry();
            }
        }
    }
    
    //GAME END
    cout << "===============================" << endl;
    cout << "           GAMEOVER            " << endl;
    cout << "===============================" << endl;
}

void Board::printBoard(){
    
    //-----Print information to the player-----
    cout << endl << endl;
    cout << "Player X:   " << player->getCurX();    // Print the player X
    cout << "\tPlayer Y: " << player->getCurY();    // Print the player Y
    cout << "\tTail Size:" << player->getLen();     // Print tail size
    cout << endl;
    
    
    //-----Print the board-----
    for(int i = 0; i < rows; i++)     // Loop through rows
    {
        for(int j = 0; j < cols; ++j) // Loop through cols
        {
            if(i == player->getCurY() && j == player->getCurX()) // Check if we're at the player's position
            {
                cout << " X";       // X represents the player
            }
            else if(i == pelletY && j == pelletX)               // Check the pellet's position
            {
                cout << " O";       // O represents the pellet
            }
            else
            {
                //-----Printing the tail-----
                bool print = false;     // Flags if we are printing an empty space
                                        // after looping through tail array
                
                // Loop through the tail array
                for(int m = 0; m < player->getLen(); ++m)
                {
                // Check for each index's position, then print
                    if(player->tailVecX[m] == j && player->tailVecY[m] == i){
                        cout << " X";
                        print = true;   // NOTE: Flags that we will not print the empty space
                    }
                }
                
                // Print the empty space if nothing else is true
                if(!print){
                    cout << "  ";
                }
            }
        }
        cout << endl;
    }
    cout << endl << endl;
}
