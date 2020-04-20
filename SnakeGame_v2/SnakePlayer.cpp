/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SnakePlayer.cpp
 * Author: Anthony, Danielle Carlos
 * 
 * Created on April 1, 2020 - 11:30 AM
 */

#include "SnakePlayer.h"

//-----SnakePlayer's Constructors/Destructors-----
SnakePlayer::SnakePlayer(int rows, int cols) {
    // Sets the point where we loop back (THIS SHOULD BE THE BOARD SIZE!)
    maxRow = rows;
    maxCol = cols;
}

SnakePlayer::~SnakePlayer() {
}


//-----Getters/Setters Definitions for current x/y coords and prev x/y coords and length------
void SnakePlayer::setCurX(int x){
   //sets current x coordinate for snake
    currX = x;
} 
void SnakePlayer::setCurY(int y){
     //sets current y coordinate for snake
    currY = y;
}
void SnakePlayer::setPreX(int x){
    //sets previous x coordinate for snake
    prevX = x;
}
void SnakePlayer::setPreY(int y){
    //sets previous y coordinate for snake
    prevY = y;
}
void SnakePlayer::setLen(int length){
    //sets length of snake tail
    this->length = length;
} 

int SnakePlayer::getCurX(){
    //returns current x coordinate for snake
    return currX;
}
int SnakePlayer::getCurY(){
   //returns current y coordinate for snake
    return currY;
} 
int SnakePlayer::getPreX(){
    //returns previous x coordinate for snake
    return prevX;
}
int SnakePlayer::getPreY(){
    //returns previous y coordinate for snake
    return prevY;
}
int SnakePlayer::getLen(){
    return length;
}

//-----Directional Movement Function-----
void SnakePlayer::getInputs(){                  // The player's movement increments by
    if(GetAsyncKeyState(VK_UP)){                // the dirX & dirY amount (think of x+= dirX  y+= dirY).   
        if (dirY == 0){dirX = 0; dirY = -1;}    // The if statement limits our movement to only move
    }                                           // perpendicular to our current direction.
    else if(GetAsyncKeyState(VK_DOWN)){
        if (dirY == 0){dirX = 0; dirY = 1;}
    }
    else if(GetAsyncKeyState(VK_LEFT)){
        if (dirX == 0){dirX = -1; dirY = 0;}
    }
    else if(GetAsyncKeyState(VK_RIGHT)){
        if (dirX == 0){dirX = 1; dirY = 0;}
    }
}

void SnakePlayer::move(){  
    //-----Updating our player's coordinates-----
    prevX = currX;      // Set the previous coords to current
    prevY = currY;
    currX += dirX;      // Then increment our current coords by dir
    currY += dirY;
    
    
    //-----Loop back when reaching the end of the board-----
    if(currX >= maxCol)  {currX = 0;}           // Hitting the right
    if (currX < 0)       {currX = maxCol-1;}    // Hitting the left
    if(currY >= maxRow)  {currY = 0;}           // Hitting the bottom
    if(currY < 0)        {currY = maxRow-1;}    // Hitting the top
    
    
    //-----The first index in tail is the head-----
    tailVecX[0] = currX;
    tailVecY[0] = currY;
    
    
    //-----Creating the tail array-----
    int prev2X, prev2Y;     // Create a second set of previous coords
                            // for each tail index
    
    // Loop through tail
    for(int i = 1; i < length; ++i){
        
        prev2X = tailVecX[i];   // Use the second set of previous coords to
        prev2Y = tailVecY[i];   // store a reference to the tail index we're at.
        
        tailVecX[i] = prevX;    // Then change the tail index's coords
        tailVecY[i] = prevY;    // to the previous coords.
        
        prevX = prev2X;         // Then make the prevXY equal to the second set (Similar to swap).
        prevY = prev2Y;
        
        
        //Check to see if we're running into any tail pos (end the game if so)
        if(tailVecX[i] == currX && tailVecY[i] == currY){
            gameover = true;
        }
    }
    
}

void SnakePlayer::addToArry(){
    //Simply add to the tail array's size
    ++length;
}