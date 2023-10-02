<<
  Asignatura:    Procesadores de Lenguajes

  Titulación:    Ingeniería Informática
  Especialidad:  Computación
  Curso:         Tercero
  Cuatrimestre:  Segundo

  Departamento:  Informática y Análisis Numérico
  Centro:        Escuela Politécnica Superior de Córdoba
  Universidad de Córdoba
 
  Curso académico: 2020 - 2021
>>

@ Este fichero pide los argumentos de una ecuacion de segundo grado y la resuelve

a := b := c := 0;
res1 := 'no definido';
res2 := 'no definido';

escribir_cadena('Vamos a resolver una ecuacion de segundo grado\n');
escribir_cadena('Introduce el coeficiente a: ');
leer(a);

escribir_cadena('Introduce el coeficiente b: ');
leer(b);

escribir_cadena('Introduce el coeficiente c: ');
leer(c);

si(a <> 0 #y b <> 0 #y c <> 0) entonces
    raiz := sqrt(b**2 - 4 * a * c);
    res1 := (-b + raiz) / 2 * a;
    res2 := (-b - raiz) / 2 * a;
si_no
    si(a = 0 #y b <> 0 #y c <> 0) entonces
        res1 := -c / b;
    si_no
        si(a <> 0 #y b = 0 #y c <> 0) entonces
            raiz := sqrt(-c / a);
            res1 := raiz;
            res2 := -raiz;
        si_no
            si(a <> 0 #y b <> 0 #y c = 0) entonces
                res1 := 0;
                res2 := -b / a;
            si_no
                res1 := '0 o indefinido';
                escribir('\nO el resultado es 0 o no tiene solucion\n\n');
            fin_si;
        fin_si;
    fin_si;
fin_si;
    

escribir('Dada la ecuacion: ');
escribir(a);
escribir('x^2');

si(b >= 0) entonces
    escribir('+');
fin_si;

escribir(b);
escribir('x');

si(c >= 0) entonces
    escribir('+');
fin_si;

escribir(c);
escribir('=0;\n' || 'Sus resultados son:\n');
escribir('x1 = ');
escribir(res1);
escribir('\nx2 = ');
escribir(res2);

escribir('\n');
