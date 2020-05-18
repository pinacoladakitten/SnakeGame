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

Board::Board(int rows, int cols, int numPlayers) {
    // ------Init Vars------
    this->rows = rows;          // Board rows
    this->cols = cols;          // Board cols
    this->playerNum = numPlayers;
    
    // ------Set random seed------
    srand (time(0));
    
    // ------Init Pellet------
    pelletX = rand() % cols;    // Random location on the x-axis in array
    pelletY = rand() % rows;    // Random location on the y-axis in array
}

Board::~Board() {
    // Delete Players
    for(int i = 1; i <= playerNum; i++){
        delete players[i];
    }
    // Delete arrays
    delete[] players;
}

void Board::gameRoom(){
    // -----Create player object (constructor args sets where the player loops)-----
    players = new SnakePlayer*[playerNum];
    
    for(int i = 1; i <= playerNum; i++){
        players[i] = new SnakePlayer(rows, cols, i);
    }
    
    // -----The main logic while the game state is running (TWO checks, end by LSHIFT or if player dies)-----
    bool GameOver=false;
    
    while(this->bIsRun && !GameOver)
    {
        // -----Frame logic-----
        (frame>=frameMax) ? frame=0 : frame++;  // Print and update when we reach the frameMax (delay effect)
        
        //-----Get Base Inputs-----
        if(GetAsyncKeyState(VK_LSHIFT))         // Ending the game from input
        {
            bIsRun = false;
        }
        
        //-----Get Player Inputs and Check Game Over-----
        for(int i = 1; i <= playerNum; i++){
            
            //-----On Frame Update-----
            if(frame == frameMax)
            {
                players[i]->getInputs();                // NOTE: We are checking OUTSIDE when the frame updates
                                                    // this is to ensure no inputs are skipped
                if (players[i]->getGameOver()){
                    GameOver = true;
                }
                
                players[i]->move();         // Update player movement

                // When the player hits the pellet
                if(players[i]->getCurX() == pelletX && players[i]->getCurY() == pelletY)
                {
                    //Randomize pellet local
                    pelletX = rand() % cols;
                    pelletY = rand() % rows;

                    //Increase player tail size
                    players[i]->addToArry();
                }
            }
        }
        
        if(frame==frameMax)printBoard();               // Print the board
    }
    
    //GAME END
    cout << "===============================" << endl;
    cout << "           GAMEOVER            " << endl;
    cout << "===============================" << endl;
}

void Board::printBoard(){
    
    //-----Print information to the player-----
    cout << endl << endl;
    cout << "Player X:   " << players[1]->getCurX();    // Print the player X
    cout << "\tPlayer Y: " << players[1]->getCurY();    // Print the player Y
    cout << "\tTail Size:" << players[1]->getLen();     // Print tail size
    cout << endl;
    
    
    //-----Print the board-----
    for(int i = 0; i < rows; i++)     // Loop through rows
    {
        for(int j = 0; j < cols; ++j) // Loop through cols
        {
            bool playerExists = false;
            bool print = false;
            
            for(int m = 1; m <= playerNum; m++)
            {
                if(i == players[m]->getCurY() && j == players[m]->getCurX()){ // Check if we're at the player's position
                    playerExists = true;
                }
                else {
                    //-----Printing the tail-----
                    bool printT = false;     // Flags if we are printing an empty space
                                            // after looping through tail array

                    // Loop through the tail array
                    for(int k = 0; k < players[m]->getLen(); k++)
                    {
                        // Check for each index's position, then print
                        if(players[m]->tailVecX[k] == j && players[m]->tailVecY[k] == i){
                            playerExists = true;   // NOTE: Flags that we will not print the empty space
                        }
                    }
                }
            }
            
            if(i == pelletY && j == pelletX) {   // Check the pellet's position
                cout << " O";       // O represents the pellet
                print = true;
            }
            
            if(playerExists){
                cout << " X";       // X represents the player
                print = true;
            }
            
            if(!print){
                cout << "  ";
            }
        }
        cout << endl;
    }
    cout << endl << endl;
}
