#include <stdlib.h>
#include <stdio.h>

void reservavector(double ** vector,int n){
	*vector=(double*)malloc(n*sizeof(double));
	if (*vector==NULL){
		printf("Error al reservar memoria.\n");
		exit(-1);
	}
}

void leeVector(double *vec, int n){
	double aux;
	for (int i = 0; i < n; ++i){
		printf("Introduzca un numero\n");
		scanf("%lf",&aux);
		vec[i]=aux;
	}
}

void escribeVector(double *vec,int n){
	printf("Vector introducido:\n");
	for (int i = 0; i < n; ++i){
		printf("%lf\n",vec[i]);
	}
}

int sumaPositivos(double *vec,int n){
	double res=0;
	for (int i = 0; i < n; ++i){
		if (vec[i]>0){
			res=res+vec[i];			
		}
	}
	return res;
}