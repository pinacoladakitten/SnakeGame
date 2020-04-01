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

//SnakePlayer's Constructors/Destructors
SnakePlayer::SnakePlayer() {
}

SnakePlayer::~SnakePlayer() {
}


//Getters/Setters Definitions for current x/y coords and prev x/y coords and length
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

//Directional Movement Prototype Function
void SnakePlayer::move(){
    if(GetAsyncKeyState(VK_UP)){
        prevY = currY; //Set previous Y coordinate to current Y coordinate
        currY-=1; //Alter the current head coordinate to move "up" (-1)
    }
    else if(GetAsyncKeyState(VK_DOWN)){
        prevY = currY;
        currY+=1;
    }
    else if(GetAsyncKeyState(VK_LEFT)){
        prevX = currX;
        currX-= 1;
    }
    else if(GetAsyncKeyState(VK_RIGHT)){
        prevX = currX;
        currX += 1;
    }
    //LSHIFT and quitting game should be managed elsewhere
}