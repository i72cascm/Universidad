read(variable);

if(variable = 0) then 
    print_string('La variable es igual a cero.');
else
    print_string('La variable no es igual a cero.'); 
end_if;


N := 5;
i := 0;

for i from  1 to N step 1 do  
    print_string('El bucle for se esta ejecutando'); 
end_for;

variable := 0;
while (variable <> 100) do
    variable := variable + 10;
end_while;

repeat
    read_string(cadena); 
    print_string('La cadena ingresada es: ' || cadena); 
until(cadena = 'Salir');

menu := 2;
case (menu) 
    value 1:
        print_string('La variable es 1');
        break
    value 2:
        print_string('La variable es 2');
        break
    value 3:
        print_string('La variable es 3');
        break
    [default: print_string('La variable no es 1, 2 o 3');]
end_case;

print_string('El programa ha finalizado.');