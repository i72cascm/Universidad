#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "estadisticasCadena.h"

int main(){
	char cadena[200];
	int dig=0, may=0, min=0, esp=0;
	printf("Introduzca una cadena de caracteres.\n");
	scanf("%[^\n]",cadena);
	estadisticasCadena(cadena,&dig,&may,&min,&esp);
	printf("Numero de digitos: %d\n",dig );
	printf("Numero de mayusculas: %d\n",may );
	printf("Numero de minusculas: %d\n",min );
	printf("Numero de espacios en blanco: %d\n",esp );

	return 0;
}
