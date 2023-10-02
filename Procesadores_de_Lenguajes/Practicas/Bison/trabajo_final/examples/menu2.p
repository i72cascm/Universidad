
repeat 
print_string('Menu:');
print_string('1. Potencia de un número');
print_string('2. Módulo de un número');
print_string('3. Bucle inverso');
print_string('4. Salir');
print_string('Ingrese opcion:');
read(opcion);

if(opcion = 1)
then
	print_string('Introduzca base de la potencia');
	read(base);

	print_string('Introduzca exponente de la potencia');
	read(exponente);

	resultado := base^exponente;
	print(resultado);
else
	if(opcion = 2)
	then
		print_string('Introduzca número');
		read(numero);

		print_string('Introduzca el módulo que desea realizar');
		read(modulo);

		resultado_modulo := numero%modulo;
		print(resultado_modulo);
	else
		if(opcion = 3)
		then
			inicio := 100;
			fin := 1;
			suma := 0;
			paso := 2;
			for i from inicio to fin step paso do
				suma := suma + i;
				print(suma);
			end_for;
			print_string('Resultado final: ');
			print(suma);
		else
			if(opcion = 4)
			then
				print_string('Saliendo del programa...');
			else
				print_string('Opcion invalida.');
			end_if;
		end_if;
	end_if;
end_if;

until (opcion = 4);
