#include <stdlib.h>
#include <stdio.h>

void vectorMayor(int *vec,int *vecmayor,int n, int num){
	int contador=0;
	printf("El vector de mayores vale: \n");
	for (int i = 0; i < n; ++i){
		if (vec[i]>num){
			printf("%d \n",vec[i] );
			vecmayor[contador]=vec[i];
			contador++;
		}
	}
}

void vectorMenor(int *vec,int *vecmenor,int n, int num){
	int contador=0;
	printf("El vector de menores vale: \n");
	for (int i = 0; i < n; ++i){
		if (vec[i]<=num){
			printf("%d \n",vec[i] );
			vecmenor[contador]=vec[i];
			contador++;
		}
	}
}