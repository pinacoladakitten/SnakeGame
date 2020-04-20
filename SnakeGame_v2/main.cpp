//
//
//
//
//

#include <cstdlib>
#include <iostream>
#include "Board.h"
using namespace std;

int main(int argc, char** argv){
    //Create the board of any size
    Board game(15,40);
    
    //Run the game
    game.gameRoom();
}