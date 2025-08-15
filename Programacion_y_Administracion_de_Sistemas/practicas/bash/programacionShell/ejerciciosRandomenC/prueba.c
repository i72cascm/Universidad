#include <stdlib.h>
#include <stdio.h>

struct persona{
	char nombre[100];
	char apellido1[100];
	char apellido2[100];
	int edad;
};

int numeroRegistros(char test[100]){
	FILE* f;
	struct persona aux;
	int contador=0;
	if((f=fopen(test,"r"))==NULL){
		printf("Error 1\n");
		exit(-1);
	}
	while(fscanf(f,"%s %s %s %d",aux.nombre,aux.apellido1,aux.apellido2,&aux.edad)==4){
		contador++;
	}
	fclose(f);
	return contador;
}

void cargarvector(char test[100],struct persona *vector){
	int contador=0; 
	FILE* f;
	if((f=fopen(test,"r"))==NULL){
		printf("Error 2\n");
		exit(-1);
	}
	while(fscanf(f,"%s %s %s %d",vector[contador].nombre,vector[contador].apellido1,vector[contador].apellido2,&vector[contador].edad)==4){
		contador++;
	}
}

void modfificarEdad(int nEle, struct persona *vector){
	int edad;
	printf("Introduzca a partir de que edad desea modificar.\n");
	scanf("%d",&edad);
	for (int i = 0; i < nEle; ++i)	{
		if(vector[i].edad>=edad){
			vector[i].edad++;
		}
	}
}

void cargarFichero(struct persona *vector,int nEle, char test[50]){
	FILE* f;
	if((f=fopen(test,"w"))==NULL){
		printf("Error 3\n");
		exit(-1);
	}
	for (int i = 0; i < nEle; ++i)	{
		fprintf(f, "%s %s %s %d",vector[i].nombre, vector[i].apellido1, vector[i].apellido2, vector[i].edad);
	}
}

void verRegistro(int nEle,struct persona *vector){
	for (int i = 0; i < nEle; ++i)	{
		printf("Nombre: %s\n",vector[i].nombre );
		printf("Apellido 1: %s\n",vector[i].apellido1 );
		printf("Apellido 2: %s\n",vector[i].apellido2 );
		printf("Edad: %d\n",vector[i].edad );
	}
}

void comprobarExistencia(char test[100]){
	FILE* f;
	if((f=fopen(test,"r"))==NULL){
		printf("El fichero no existe.\n");
		exit(-1);
	}else{
		printf("El fichero existe.\n");
	}

}

int main(int argc, char *argv[]){
	int nEle;
	struct persona *vector;
	nEle=numeroRegistros(argv[1]);
	vector=(struct persona*)malloc(nEle*sizeof(struct persona));
	cargarvector(argv[1],vector);
	verRegistro(nEle,vector);
	modfificarEdad(nEle,vector);
	cargarFichero(vector,nEle,argv[1]);
	verRegistro(nEle,vector);
	comprobarExistencia(argv[1]);
	return 0;
}