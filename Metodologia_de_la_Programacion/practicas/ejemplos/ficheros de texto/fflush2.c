#include <stdio.h>

int main()
{
  char acumulador[BUFSIZ]; //Definido en stdio.h

  setbuf( stdout, acumulador );

  printf( "Esto es una prueba\n" );
  printf( "Este mensaje se mostrara a la vez\n" );
  printf( "setbuf, acumula los datos en un puntero\n" );
  printf( "hasta que se llene completamente\n" );
  
  getchar(); 
  fflush( stdout );
  
  setbuf( stdout, NULL);
  printf( "Esto ya no se almacena en buffer\n" );
  return 0;
}

