escribir_cadena('Introduce un numero: ');
leer(dato);

escribir dato;
escribir '\n';

si (dato < 0) entonces
  f := 0
si_no
  i := dato;
  f := 1;
  mientras i>1) hacer
    f := f * i;
    i := i - 1;
  fin_mientras;
fin_si

escribir f; 
escribir '\n';
