//Ejemplo de apertura de un fichero de texto en modo lectura
#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE* f; //Es el flujo asociado al fichero
  
  //Apertura del fichero para lectura
  if((f=fopen("fich_datos.txt", "r"))==NULL)  
  {
    printf("\nError al abrir fichero <%s>", "fich_datos.txt");
    exit(-1);
  }
  //Instrucciones de procesamiento del fichero
  //..............  
  
  //Cierre del flujo/fichero
  fclose(f);
  return(0);
}