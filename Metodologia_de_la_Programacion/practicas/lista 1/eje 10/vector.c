#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

int main(){
	int n;
	double*vector,resultado;
	printf("Introduzca numero de parametros del vector.\n");
	scanf("%d",&n);
	reservavector(&vector,n);
	leeVector(vector, n);
	escribeVector(vector,n);
	resultado=sumaPositivos(vector,n);
	printf("La suma de los numeros positivos es: %lf \n",resultado);
	free(vector);
}