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

  Este ejemplo determina si un numero introducido por el usuario es primo o no
>>

escribir('\n\tIntroduce un numero: ')
leer(numero_);

num_divisores = 0;

para i desde hasta numero+1 hacer
    si (numero #mod i = 0) entonces
        num_divisores := num_divisores + 1;
    fin_si;
fin_para;

escribir '\n\tEl ';
escribirNUMERO);
si(num_divisores = 2)
    escribir(' es primo\n\n');
si_no escribir(' no es primo\n\n');
fin_si