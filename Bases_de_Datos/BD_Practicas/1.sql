------------------------
------ Práctica 1 ------
------------------------

-- Ejercicio 1 --

-- Check --

-- Ejercicio 2 --

select table_name from user_tables;

-- Ejercicio 3 --

describe eventos;

-- Ejercicio 4 --

drop table votantes cascade constraints;

-- Ejercicio 5 --

insert into votantes values (30653845,'Maria Gonzalez Ramirez', 'Doctorado', 'Activo', 'goram@telefonica.es', 1, '21/08/1989', 677544822);

-- Ejercicio 6 --

select * from votantes;

-- Ejercicio 7 --

select * from votantes;

delete from votantes where dni = 30653845;

select * from votantes;

-- Ejercicio 8 --

-- Check --

-- Ejercicio 9 --

select nombre, tipo, fecha from eventos;

-- Ejercicio 10 --

select nombre || ' de tipo ' || tipo as Convocatoria from eventos;

-- Ejercicio 11 --

-- Check --