#include <stdio.h>
#include <stdlib.h>

void leeVector1(int *v, int n){
	int aux;
	for (int i = 0; i < n; ++i)	{
		printf("Introduzca valor de la posicion %d: \n",i+1 );
		scanf("%d",&aux);
		v[i]=aux;
	}
}

void imprimeVector1(int *v,int n){
	for (int i = 0; i < n; ++i)	{
		printf("Valor de la posicion %d: %d \n",i+1,v[i] );
	}
}