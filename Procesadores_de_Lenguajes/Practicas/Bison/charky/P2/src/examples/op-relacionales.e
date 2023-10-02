dato1 := verdadero;
dato2 := falso;

si(dato1 #O dato2) entonces
    escribir(dato1);
    escribir(' o ');
    escribir(dato2);
    escribir(' es igual a verdadero\n');
si_no
    escribir(dato1);
    escribir(' o ');
    escribir(dato2);
    escribir(' es igual a falso\n');
fin_si;

escribir('Aunque dato2');
escribir(' sea ');
escribir(dato2);
escribir(', si lo negamos es ');
escribir(#NO DATO2);
escribir('\n');