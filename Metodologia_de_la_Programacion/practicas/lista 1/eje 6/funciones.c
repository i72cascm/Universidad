#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void minimo_referencia(int a, int b, int* resultado){
	if (a<=b){
		*resultado=a;
	}else{
		*resultado=b;
	}
}

int minimo(int a, int b){
	int resultado;
	if (a<=b){
		resultado=a;
	}else{
		resultado=b;
	}
	return resultado;
}