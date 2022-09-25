//Crea el fichero "letra_A.txt" y escribe el caracter 'A' y un salto de linea
#include <stdio.h>
int main()
{
  FILE* f;
  
  // Apertura del fichero en modo escritura:
  // creacion del fichero "letra_a"
  // si el fichero existe lo sobreescribe
  if((f=fopen("letra_A.txt", "w"))==NULL)  
  {
    printf("Error: No se pudo crear el fichero <letra_A.txt>");
    exit(-1);
  }
  fputc('A', f); //Escribe el caracter 'A'
  fputc('\n', f); //escribe el '\n'
  
  fclose(f);
  return(0);
}
