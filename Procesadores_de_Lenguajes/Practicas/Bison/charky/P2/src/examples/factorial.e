escribir_cadena('Introduce un numero: ');
leer(dato);

escribir_cadena('El factorial de ');
escribir(dato);


si (dato < 0) entonces 
  f := 0 ;
si_no 
  i := dato;
  f := 1;

  mientras(i>1) hacer
      f := f * i;
      i := i - 1;
  fin_mientras;
fin_si;

escribir_cadena(' es ');
escribir(f); 
escribir_cadena('\n');