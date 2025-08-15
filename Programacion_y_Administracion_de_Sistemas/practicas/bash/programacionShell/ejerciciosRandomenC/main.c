#include <stdio.h>
#include <stdlib.h>

#define max_linea 100

struct LibrosDatos{
	char titulo[15];
	char autor[15];
	int precio;
	int unidad;

};

int contarLibros(char *fichero){
FILE *pFichero;
int nLibros=0;
struct LibrosDatos libros;

pFichero= fopen(fichero, "r" );
while(fscanf(pFichero,"%s\n%s\n%i %i", libros.titulo, libros.autor, &libros.precio, &libros.unidad)!=EOF){
	nLibros++;
}
fclose(pFichero);
return (nLibros);
}



int main(){
	int nLibros;
	char fichero[max_linea];
	printf("Introduce el nombre del fichero: "); //nombre del fichero que vamos a usar con su .txt
	scanf("%s", fichero);
	nLibros= contarLibros(fichero);
	printf("El numero de libros es: %i\n",nLibros);

	return(0);

}