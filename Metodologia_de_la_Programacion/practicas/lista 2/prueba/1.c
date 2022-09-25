#include <stdio.h>
#include <stdlib.h>


void reservaMemoria(int **v, int *n){
	printf("Introduzca número de parámetros.\n");
	scanf("%d",&*n);
	*v=(int*)malloc(*n*sizeof(int));
	if(*v==NULL){
		printf("Error al reservar memoria\n");
		exit(-1);
	}
}

void reservaMemoria2(int **v, int n){
	*v=(int*)malloc(n*sizeof(int));
	if (*v==NULL)	{
		printf("Error al reservar memoria.\n");
		exit(-1);
	}
}