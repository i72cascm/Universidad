#ifndef GAME_H
#define GAME_H

#define UP 1
#define RIGHT 2
#define DOWN -1
#define LEFT -2



void initGame();
void display();
static void reshape(int,int);
void WindowSwap(unsigned char, int, int);
void Snake_move(int,int,int);
void FPSload(int);
void grid(int,int);
void colorGrid(int,int);
void gridPosition();
void snakePosition();
void foodPosition();
void random(int&,int&);


#endif 