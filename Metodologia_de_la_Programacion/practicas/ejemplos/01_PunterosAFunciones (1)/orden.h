#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int es_mayor(int a, int b);
int es_menor(int a, int b);
void burbuja(int* V, int izda, int dcha,int(*comparacion)(int, int));
void seleccion(int* V, int izda, int dcha, int(*comparacion)(int, int));
