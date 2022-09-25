#ifndef VECTORDINAMICO_H
#define VECTORDINAMICO_H

void reservaMemoria(int **vec,int n);
void leeVector(int *vec, int n);
void Imprimevector(int *vec, int n);
void contadores(int *vec, int n, int*cma, int*cme,int num);
void reservaMenor(int **vecmenor,int cme);
void reservaMayor(int **vecmayor,int cma);
void vectorMayor(int *vec,int *vecmayor,int n, int num);
void vectorMenor(int *vec,int *vecmenor,int n, int num);

#endif