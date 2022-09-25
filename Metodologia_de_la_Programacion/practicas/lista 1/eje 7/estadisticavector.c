#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "estadisticavector.h"

int main(){
int *vector, n;
float media=0,varianza=0,dt;
printf("Introduzca numero de parametros.\n");
scanf("%d",&n);
reservaVector(&vector, n);
leeVector(vector, n);
imprimeVector(vector,n);
doMedia(vector, n,&media);
doVarianza(vector, n,media,&varianza);
doDt(varianza,&dt);
imprimeResultados(media,varianza,dt);
}