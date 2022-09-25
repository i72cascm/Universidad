//Simulacion muy simple del programa cat
//Muestra el contenido de un fichero que es leido 
//caracter a caracter
#include <stdio.h>
int main()
{
  FILE* f;
  int c;
  char nombreFich[] = "fichtexto.txt";
  //Apertura del fichero en modo lectura
  if((f=fopen(nombreFich, "r"))==NULL)  
  {
    printf("Error: No se pudo abrir el fichero <%s>", nombreFich);
    exit(-1);
  }
  
  while((c=getc(f))!=EOF)
  {putc(c, stdout);}
    
  fclose(f);
  return(0);
}
