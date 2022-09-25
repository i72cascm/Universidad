#include <stdio.h>
#include <string.h>

int es_sufijo(char *cadena, char *sufijo){
	char *comprueba;
		comprueba=strstr(cadena,sufijo);
		if (comprueba==NULL){
			return 0;
		}else{
			if (strlen(comprueba)==strlen(sufijo)){
				return 1;
			}else{
				return 0;
			}
		}
	
}
int main(){
	char cadena[999];
	char sufijo[999];
	printf("Introduce las dos cadenas para comprobar si existe sufijo:\n");
	scanf("%s",cadena);
	scanf("%s",sufijo);
	if(es_sufijo(cadena,sufijo)==1){
		printf("Es un sufijo\n");
	}else{
		printf("No es un sufijo\n");
	}

}
