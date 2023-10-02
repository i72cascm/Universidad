@ Ejemplo de menu con sentencia CASOS

repetir 

 @ Opciones disponibles

 escribir_cadena(' OPCIONES\n');
 escribir_cadena(' OPCION 1 ----> 1\n');
 escribir_cadena(' OPCION 2 ----> 2\n');
 escribir_cadena(' OPCION 3 ----> 3\n');
 escribir_cadena(' FINALIZAR ---> 4\n');
 escribir_cadena(' Elige una opcion: ');

 leer(opcion);

 casos(opcion)
    valor 1: escribir_cadena('\n Has elegido la opcion 1\n');
    valor 2: escribir_cadena('\n Has elegido la opcion 2\n');
    valor 3: escribir_cadena('\n Has elegido la opcion 3\n');
    valor 4: escribir_cadena('\n Que tenga un buen día\n');
    defecto:
        escribir_cadena('\n La opcion no es valida\n');
        escribir_cadena(' Prueba de nuevo\n');
 fin_casos;
 
 escribir_cadena('\n Pulse una tecla para continuar --> ');
 leer_cadena(pausa);

 #borrar;
 
hasta (opcion = 4); 