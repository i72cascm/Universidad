<<
  Programa de ejemplo de conversión de tipo.
  Se comprueba la conversión de tipo de una variable
>>

clear_screen;

place(3,10);
print_string('Ejemplo de cambio del tipo de valor de una variable \n');

print_string('Introduce un número --> ');
read(dato);

print_string('El número introducido es -> ');
print(dato);

print_string('Introduce una cadena de caracteres --> ');
read_string(dato);

print_string('La cadena introducida es -> ');
print_string(dato);

place(20,10);
print_string(' Fin del ejemplo de cambio del tipo de valor \n');