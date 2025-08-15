#include <ctime>
#include <cstring>
#include <iostream>

#include "game.h"
#include <stdio.h>
#include <GL/freeglut.h>
#include <stdlib.h>

using namespace std;



extern int sDirection;

//definimos el tamaño de bloque
const extern int Block=1;

//bloques tanto de altura como de anchura que compondran el videojuego
const int HeightBlocks=45; 
const int WidthBlocks=60;


//Tamaño del header
const int Header = 5; 

//Definición del tablero de juego mediante los parametros anteriores
const int WidthTable = WidthBlocks*Block;
const int HeigthTable = HeightBlocks*Block;


//Definición de la ventana donde se colocara el tablero
const int WidthWindows = WidthTable;
const int HeigthWindows = HeigthTable + Header;

//Bandera que indicará si el juego esta en la pantalla del titulo, en el propio juego o en la pantalla de fin de juego
int Flag = 1;

//Puntuacion del juego
int score=0;
int FPS=10;


int main(int argcp, char **argv){
    
    glutInitWindowSize (1250 , 1250);

    //Inicialización de la ventana emergente de la aplicacion
	glutInit(&argcp, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Videogame: SNAKE");

    /////////////////////////////////////////////////////////////////////
    glOrtho(0.0, WidthWindows, 0.0, HeigthWindows, -1.0, 1.0);
	/////////////////////////////////////////////////////////////////////

    //Funciones para funcionalidad del teclado y teclas especiales
    glutTimerFunc(0,FPSload,0);
	glutKeyboardFunc(WindowSwap);
    glutSpecialFunc(Snake_move);

    //Funciones para la ventana
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

    
    //init juego
    initGame();
	glutMainLoop();
}


void display(){
    
    string score_txt, score_p, finalScore;

    if(Flag == 1){

           
            glClearColor(0.0, 0.7, 0.9, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            glFlush();

            glLoadIdentity ();
            glColor3f(0.0, 0.0, 0.0);
            glFlush();
          
            glRasterPos2d(27.0, 27.0); 
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)"Press `A` to start:");
            glRasterPos2d(27.0, 25.0);
            glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char*)"i72cascm's game \n");

            glFlush();

    }else if (Flag == 2 ){

            glClearColor(0.0, 0.8, 0.9, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            glLoadIdentity ();

            gridPosition();
            snakePosition();
            foodPosition();
            glFlush();

            glColor3f(0.0, 0.0, 0.0);
          
            glRasterPos2d(40, 47.0);
            glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)"Snake Game");

            glRasterPos2d(5, 47.0);
            glFlush();
           
          
            score_txt= "       SCORE";
            score_p = to_string(score);
            finalScore= score_p + score_txt;


            for (int i=0; i<finalScore.size(); i++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, finalScore[i]);
            }
            

            glFlush();

    } else if (Flag == 3){

        glLoadIdentity ();
        glColor3f(0.7, 0.0, 0.0);
        glRasterPos2d(27, 23.0);
        glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)"GAME OVER");
        glFlush();
    }
 
	glutSwapBuffers();

}


void WindowSwap(unsigned char key, int x, int y){
    //
    switch(key){
        case 'a':
            if(Flag==2){ 
                Flag=3;
            }else if(Flag==1){ 
                Flag=2;
            }
            
            break;

        case 'A':
            if(Flag==2){ 
                Flag=3;
            }else if(Flag==1){ 
                Flag=2;
            }
            
            break;
    }

    glutPostRedisplay();

}


void Snake_move(int key, int, int){
    
    switch(key){

        case GLUT_KEY_RIGHT: //flecha derecha
            if (sDirection!=LEFT){ //bloqueamos izquierda
                sDirection=RIGHT;
            }
        break;

        case GLUT_KEY_DOWN: //flecha abajo
            if (sDirection!=UP){ // bloqueamos arriba
                sDirection=DOWN;
            }
        break;

        case GLUT_KEY_UP: //flecha arriba
            if (sDirection!=DOWN){ //bloqueamos dirección abajo
                sDirection=UP; //cambiar dirección
            }
        break;

        case GLUT_KEY_LEFT: //flecha izquierda
            if (sDirection!=RIGHT){ //bloqueamos derecha
                sDirection=LEFT;
            }
        break;                
    }

}


static void reshape(int a, int b){

	glViewport(0, 0, a, b);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
	glOrtho(0.0, WidthWindows, 0.0, HeigthWindows, -1.0, 1.0);
    glLoadIdentity ();
    glFlush();

}


void FPSload(int){

    glutPostRedisplay(); //nos pide el siguiente display
    glutTimerFunc(1000/FPS, FPSload, 0); //pide el tiempo en milisegundos, se llama para recursividad y el 0 para 0 segundos de delay

}


void initGame(){

    grid(WidthBlocks, HeightBlocks);
    glFlush();
}