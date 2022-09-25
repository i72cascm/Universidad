#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "mincol.h"

int main(){
	int **matriz;
	int nFilas;
	int nColumnas;
	printf("Introduzca nº de filas y luego nº de columnas\n");
	scanf("%i",&nFilas);
	scanf("%i",&nColumnas);
	matriz=reservarMemoria(nFilas,nColumnas);
	rellenaMatriz(matriz,nFilas,nColumnas);
	imprimeMatriz(matriz,nFilas,nColumnas);
	minCol(matriz,nFilas,nColumnas);
	liberarMemoria(&matriz,nFilas);
	return 0;
}