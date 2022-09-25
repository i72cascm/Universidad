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
 int (*punteroFuncion[3])(int, int) = {&suma, &resta};
 
 resultado = (*punteroFuncion[0])(a, b);
 printf("La suma es : %d\n", resultado);

 resultado = (*punteroFuncion[1])(a, b);
 printf("La resta es : %d\n", resultado); 

 punteroFuncion[2]=&producto;  
 resultado = (*punteroFuncion[2])(a, b);
 printf("El producto es : %d\n", resultado);
}
