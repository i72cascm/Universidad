#include <stdlib.h>
#include <stdio.h>

void reservaMenor(int **vecmenor,int cme){
	*vecmenor=(int*)malloc(cme*sizeof(int));
	if (*vecmenor==NULL){
		printf("Error al reservar memoria. \n");
		exit(-1);
	}
}

void reservaMayor(int **vecmayor,int cma){
	*vecmayor=(int*)malloc(cma*sizeof(int));
	if (*vecmayor==NULL){
		printf("Error al reservar memoria. \n");
		exit(-1);
	}
}