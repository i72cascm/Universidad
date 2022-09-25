//prueba los diferentes modos de apertura de un fichero
#include <stdio.h>

int main()
{
  FILE* fOrigen;
  char nombreOrigen[]="modos.txt", modo[]="r+";  
  int cod;
  
  if((fOrigen=fopen(nombreOrigen, modo))!=NULL)
  {
    cod = fprintf(fOrigen, "\n%s","ADIOS"); 
    fclose(fOrigen);
    //printf("\nEl programa ha terminado con normalidad. Modo:%s Cod=%d", modo, cod);
    return(0);
  }
  else
  {
    printf("\nEl fichero <%s> no existe", nombreOrigen);
    return(1);
  }
}

