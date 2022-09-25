#ifndef PRUEBA_H
#define PRUEBA_H

void reservaMemoria(int **v, int *n);
void reservaMemoria2(int **v, int n);
void leeVector1(int *v, int n);
void imprimeVector1(int *v,int n);
void contadores(int *v,int n,int *contadorMenor,int *contadorMayor,int *num);
void divideVectores(int *v,int n,int *vMayor,int *vMenor,int num);
void imprimeVectores(int *vMayor,int *vMenor,int contadorMayor,int contadorMenor);

#endif