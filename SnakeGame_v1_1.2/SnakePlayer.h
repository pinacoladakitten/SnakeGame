/* 
 * File:   SnakePlayer.h
 * Author: Anthony, Danielle Carlos
 * Purpose: Head player Object - Translation into object for object-oriented snake
 * Created on April 1st, 2020 - 11:14 AM
 */

#ifndef SNAKEPLAYER_H
#define SNAKEPLAYER_H

#include <Windows.h>

class SnakePlayer {
private:
    int currX, currY; // current x and y positions for the head
    int prevX, prevY; //previous positions for the head after the game has begun
    int length;       //current length of the tail
public:
    SnakePlayer();
    virtual ~SnakePlayer();
    
    //Getters/Setters for current x/y coords and prev x/y coords and length
    void setCurX(int); //sets current x coordinate for snake
    void setCurY(int); //sets current y coordinate for snake
    void setPreX(int); //sets previous x coordinate for snake
    void setPreY(int); //sets previous y coordinate for snake
    void setLen(int); //sets length of snake tail
    
    int getCurX(); //returns current x coordinate for snake
    int getCurY(); //returns current y coordinate for snake
    int getPreX(); //returns previous x coordinate for snake
    int getPreY(); //returns previous y coordinate for snake
    int getLen();  //returns length of the snake's tail
    
    //Directional Movement Prototype Function
    void move(); //function to determine direction of head
};

#endif /* SNAKEPLAYER_H */

