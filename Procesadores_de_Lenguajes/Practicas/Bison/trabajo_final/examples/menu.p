<<
  Asignatura:    Procesadores de Lenguajes

  Titulación:    Ingeniería Informática
  Especialidad:  Computación
  Curso:         Tercero
  Cuatrimestre:  Segundo

  Departamento:  Informática y Análisis Numérico
  Centro:        Escuela Politécnica Superior de Córdoba
  Universidad de Córdoba
 
  Curso académico: 2022 - 2023

  Fichero de ejemplo para interpreter.exe
>>

# Bienvenida

clear_screen;
place(10,10);
print_string('Introduce tu nombre --> ');
place(12,10);
read_string(nombre);

clear_screen;
place(10,10);
print_string(' Bienvenido/a << ');
print_string(nombre);
print_string(' >> a \'interpreter.exe\'.');

place(40,10);
print_string('Pulsa una tecla para continuar');
read_string( pausa);


repeat 

 # Opciones disponibles

 clear_screen;
 place(10,10);
 print_string(' Factorial de un número --> 1 ');

 place(11,10);
 print_string(' Máximo común divisor ----> 2 ');

 place(12,10);
 print_string(' Finalizar ---------------> 0 ');

 place(15,10);
 print_string(' Elige una opcion ');

 read(opcion);

 clear_screen;

 # Fin del programa
 if (opcion = 0)       		
    then  
        place(10,10);
        print_string(nombre);
        print_string(': gracias por usar el intérprete ipe.exe ');
 else 					
	# Factorial de un número
	if (opcion = 1)
   	    then
			place(10,10);
			print_string(' Factorial de un numero  ');

			place(11,10);
			print_string(' Introduce un numero entero ');
			read(N);

			factorial := 1;

       		for i from 2 to N step 1 do
	            factorial := factorial * i;
	        end_for;

        	# Resultado
			place(15,10);
			print_string(' El factorial de ');
			print(N);
			print_string(' es ');
			print(factorial);

	else 
	   	# Máximo común divisor
		if (opcion = 2)
			then
				place(10,10);
				print_string(' Máximo común divisor de dos números ');

				place(11,10);
                print_string(' Algoritmo de Euclides ');

                place(12,10);
                print_string(' Escribe el primer número ');
                read(a);

                place(13,10);
                print_string(' Escribe el segundo número ');
                read(b);

                # Se ordenan los números
				if (a < b)
					then 
						auxiliar := a;
						a := b;
						b := auxiliar;
				end_if;

				# Se guardan los valores originales
					A1 := a;
					B1 := b;

				# Se aplica el método de Euclides	
				resto  := a % b;

				while (resto <> 0) do
					a :=  b;
					b := resto;
					resto := a % b;
				end_while;
         
				# Se muestra el resultado
				place(15,10);
				print_string(' Máximo común divisor de ');
				print(A1);
				print_string(' y ');
				print(B1);
				print_string(' es ---> ');
				print(b);

		# Resto de opciones
 		else  
			place(15,10);
		    print_string(' Opcion incorrecta ');
		end_if;   
  	end_if;                 
  end_if;                          

 place(40,10); 
 print_string('\n Pulse una tecla para continuar --> ');
 read_string(pausa);
 
until (opcion = 0);             

# Despedida final
clear_screen;
place(10,10);
print_string('El programa ha concluido');
