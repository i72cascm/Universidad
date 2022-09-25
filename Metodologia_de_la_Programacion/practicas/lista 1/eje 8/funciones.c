#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void estadisticasCadena(char cadena[200],int *dig,int *may,int *min,int *esp){
	int n=strlen(cadena);
	for (int i = 0; i < n; ++i)	{
		if (isdigit(cadena[i])){
			*dig=*dig+1;
		}else{
			if (isupper(cadena[i])){
				*may=*may+1;
			}else{
				if (islower(cadena[i])){
					*min=*min+1;
				}else{
					if (isspace(cadena[i])){
						*esp=*esp+1;
					}
				}
			}
		}
	}
}
