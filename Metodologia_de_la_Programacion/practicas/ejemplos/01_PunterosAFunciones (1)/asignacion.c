#include <stdio.h>
int suma(int a, int b)
{
 return a +b;
}    
 
int resta(int a, int b)
{
 return a - b;
}    

int producto(int a, int b)
{
 return a*b;
}

main()
{
 int a=3, b=5, resultado;

 int (*punteroFuncion)(int, int);
 punteroFuncion = suma;  //Asignación
 resultado = (*punteroFuncion)(a, b); 
 printf("La suma es : %d\n", resultado);
 
 punteroFuncion = resta;
 resultado = (*punteroFuncion)(a, b);
 printf("La resta es : %d\n", resultado);
 
 punteroFuncion = &producto;
 printf("El producto es : %d\n", (*punteroFuncion)(a, b));
}

