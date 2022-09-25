//Ejemplo de apertura de un fichero de texto en modo escritura

#include <stdio.h>
#include <stdlib.h>
int main()
{
  FILE* f; //Es el flujo asociado al fichero
  
  //Apertura del fichero para escritura
  if((f=fopen("fich_datos.txt", "w"))==NULL)  
  {
    printf("\nError, no se pudo crear fichero <%s>", "fich_datos.txt");
    exit(-1);
  }
  //Instrucciones de procesamiento del fichero
  //..............  
  
  //Cierre del flujo/fichero
  fclose(f);
  return(0);
}