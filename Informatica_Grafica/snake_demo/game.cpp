#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>
#include <iostream>
#include <ctime>
#include <cstring>
#include "game.h"

//Longuitud máxima de la serpiente y tamaño inicial
int Max_Length = 40;
int Snake_Length = 2;

//Para generar la cuadricula del juego
int grid_X, grid_Y;

//Para posicionar la fruta de la serpiente
bool fruit = true;
int fruit_X, fruit_Y;


extern int score;
extern int Flag;
extern int Block;

//posicion inicial de la serpiente
int poss_X[60] = {15,15,14,14,14};
int poss_Y[60] = {15,14,14,13,12};

//la serpiente se movera hacia arriba en primera instancia
int sDirection = UP;


void random( int &x, int &y){ //random numbers

    srand(time(NULL));
 
    

    int min = 1;
    int X_max = grid_X-1;
    int Y_max = grid_Y-1;
    
    x = min + rand()%(X_max - min);
    y = min + rand()%(Y_max - min);

}


void colorGrid(int x, int y){ //funcion que colorea los bloques del grid, diferencia entre bloques centrales y bordes

    if(x == 0 ||  x == grid_X-1 || y == 0 || y == grid_Y-1){
        glLineWidth(Block*3);
        glColor3f(0.5,0.3,0.3);
    }else{
        glLineWidth(Block);
        glColor3f(0.4,1,0.6);
    }

    glRectf(x,y,x + 1,y + 1);
    
}

void grid(int x, int y){ //definicion del grid
    grid_X = x;
    grid_Y = y;
}


void gridPosition(){ //funcion que coloca los bloques para formar el tablero
    for(int x = 0;x < grid_X; x++){
        for(int y = 0;y < grid_Y; y++){
            colorGrid(x,y);
        }
    }
}


void snakePosition(){ //posicion de la snake y su movimiento


    for(int i = 0 ; i < Snake_Length; i++){
        if(i==0){
            glColor3f(0.5,0.1,1);
        }else{
            glColor3f(0.5,0.0,0.1);
        }
        glRectd(poss_X[i], poss_Y[i], poss_X[i]+1, poss_Y[i]+1);
    }
    

}


void foodPosition(){ //Generacion de la fruta y posicion aleatoria de la misma


    if(fruit){
        random(fruit_X, fruit_Y);
        fruit = false;
    }
    glColor3f(0.3,0.2,1);

    glRectd(fruit_X, fruit_Y, fruit_X+1, fruit_Y+1);

}