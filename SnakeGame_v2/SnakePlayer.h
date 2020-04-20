/* 
 * File:   SnakePlayer.h
 * Author: Anthony, Danielle Carlos
 * Purpose: Head player Object - Translation into object for object-oriented snake
 * Created on April 1st, 2020 - 11:14 AM
 */

#ifndef SNAKEPLAYER_H
#define SNAKEPLAYER_H

#include <Windows.h>
#include <vector>

using namespace std;

class SnakePlayer {
private:
    int currX=0, currY=0;           // current x and y positions for the head
    int prevX, prevY;               // previous positions for the head after the game has begun
    int length=1;                   // current length of the tail
    int dirX=1, dirY=0;             // sets the XY direction the snake moves
    int maxRow, maxCol;             // get the maximum col and row the snake can move (where it loops)
    bool gameover = false;          // Game over state
    
public:
    SnakePlayer(int, int);          // Constructor for inputing the board size
    virtual ~SnakePlayer();         // Destructor
    
    //Getters/Setters for current x/y coords and prev x/y coords and length
    void setCurX(int);              //sets current x coordinate for snake
    void setCurY(int);              //sets current y coordinate for snake
    void setPreX(int);              //sets previous x coordinate for snake
    void setPreY(int);              //sets previous y coordinate for snake
    void setLen(int);               //sets length of snake tail
    
    int getCurX();                  //returns current x coordinate for snake
    int getCurY();                  //returns current y coordinate for snake
    int getPreX();                  //returns previous x coordinate for snake
    int getPreY();                  //returns previous y coordinate for snake
    int getLen();                   //returns length of the snake's tail
    
    //Game States
    bool getGameOver(){return gameover;}          // return game death status
    bool setGameOver(bool game){gameover = game;} // set game death status
    
    //Directional Movement Prototype Function
    void getInputs();   // function to get inputs every update
    void move();        // when the frame updates, change the direction
    
    //Tail Array
    void addToArry();   // increases the tail array's size
    int tailVecX[100];  // NOTE: Initially vectors, but is an array for now
    int tailVecY[100];  // just ignore the 'Vec' part in the name lol 
                        // (for now max size is 100).
};

#endif /* SNAKEPLAYER_H */

