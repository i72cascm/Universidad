#include <stdio.h>

void ver(void *,int tipo);

void main()
{
  char a='b';
  int x=3;
  double y=4.5;
  char *cad="hola";
  ver(&a,1);
  ver(&x,2);
  ver(&y,3);
  ver(cad,4);
}


void ver( void *p, int tipo)
{
  switch(tipo)
  {
    case 1: printf("%c\n",*(char *)p);
            break;
    case 2: printf("%d\n",*(int *)p);
            break;
    case 3: printf("%ld\n",*(double *)p);
            break;
    case 4: printf("%s\n",(char *)p);
            break;
  }
}

