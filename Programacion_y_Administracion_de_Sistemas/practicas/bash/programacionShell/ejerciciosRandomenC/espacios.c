#include <stdio.h>
#include <stdlib.h>

#define max_linea 100

struct LibrosDatos{
	char titulo[max_linea];
	char autor[max_linea];
	int precio;
	int unidad;

};

int contarLibros(char *fichero){
FILE *pFichero;
int nLibros=0;
struct LibrosDatos libros;

pFichero= fopen(fichero, "r" );

		do{

			fgets(libros.titulo, max_linea, pFichero);
			fgets(libros.autor, max_linea, pFichero);
			fscanf(pFichero,"%i %i\n", &libros.precio, &libros.unidad);

			nLibros++;

		}while(fscanf(pFichero,"%i %i", &libros.precio, &libros.unidad)!=EOF);

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