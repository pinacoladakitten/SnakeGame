//
//
//
//
//

#include <cstdlib>
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

void delArr(int**, int);

int main(int argc, char** argv){
    //Vars-----------------------
    // Global
    int frameMax=20000, frame=0;
    bool bIsRun = true;
    srand (time(0));
    
    // Board
    int rows=15, cols=35;
    int** snakeArr = new int*[rows];
    // Initialize array rows
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            snakeArr[i] = new int[cols];
        }
    }
    
    // Player
    int dirX=1, dirY=0, len=1;
    int** plXY = new int*[1];
    // Initialize array rows
    for(int i = 0; i < len; ++i){
        for(int j = 0; j < 2; ++j){
            //Row X and Y
            plXY[i] = new int[2];
            
            //EACH ROW IS XCOORD[0], YCOORD[0]
        }
    }
    
    // X POS
    plXY[0][0] = cols/2;
    // Y POS
    plXY[0][1] = rows/2;
    
    //Pellet
    int alX=rand() % cols + 1, alY=rand() % rows + 1;
    
    while(bIsRun){
        //Progress frames
        frame+=1;
        
        //Get keyboard inputs
        if(GetAsyncKeyState(VK_UP)){
            dirX=0;
            dirY=-1;
        }
        else if(GetAsyncKeyState(VK_DOWN)){
            dirX=0;
            dirY=1;
        }
        else if(GetAsyncKeyState(VK_LEFT)){
            dirX=-1;
            dirY=0;
        }
        else if(GetAsyncKeyState(VK_RIGHT)){
            dirX=1;
            dirY=0;
        }
        else if(GetAsyncKeyState(VK_LSHIFT)){
            bIsRun = false;
        }
        //Output nothing if nothing is hit
        else{
             if(frame==frameMax) cout << "";
        }
        
        if(frame == frameMax){
            //Draw array
            cout << endl << endl;
            cout <<"Xcord: "<<plXY[0][0]<<" "<<"Ycord: "<<plXY[0][1]<<endl;
            
            for(int i = 0; i < rows; ++i){
                for(int j = 0; j < cols; ++j)
                {
                    //Draw player at coord
                    for(int m = 0; m < len; ++m){
                        (j==plXY[m][0] && i==plXY[m][1]) ? cout << "X" : cout << "*";
                    }
                    //Draw pellet
                    (j==alX && i==alY) ? cout << "O" : cout << "*";
                }
                cout << endl;
            }
            
            //Move player
            for(int i = 0; i < len; ++i){
                if(i==0){
                    plXY[i][0]+=dirX;
                    plXY[i][1]+=dirY;
                }
                else{
                    plXY[i][0]=plXY[i-1][0]-1;
                    plXY[i][1]=plXY[i-1][1]-1;
                }
                    
                //Wrap player movement
                //X
                if(plXY[i][0] >= cols) plXY[0][0]=0;
                if(plXY[i][0] < 0) plXY[0][0]=cols;
                //Y
                if(plXY[i][1] >= rows) plXY[0][1]=0;
                if(plXY[i][1] < 0) plXY[0][1]=rows;
            }
            
            //See if player overlaps pellet
            if(plXY[0][0]==alX && plXY[0][1]==alY){
                // Randomize pellet coords
                alX=rand() % cols;
                alY=rand() % rows;
                
            }
        }
        
        //Reset frame count upon reaching frame max
        if(frame==frameMax) frame = 0;
    }
    
    // Delete board array
    delArr(snakeArr, len);
    
    // Delete player array
    delArr(plXY, len);
    
}

void delArr(int**array, int rows){
    // Delete array
    for(int i = 0; i < rows; ++i){
        delete[] array[i];
    }
    
    delete[] array;
}