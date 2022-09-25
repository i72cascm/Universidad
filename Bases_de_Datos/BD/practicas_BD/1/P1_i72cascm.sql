--Ejercicio 1 y 2--

select table_name from user_tables;

--Ejercicio 3--

describe eventos;
describe EVENTOS_RESULTADOS;
describe CONSULTAS;
describe CONSULTAS_DATOS;
describe LOCALIDADES;
describe PARTIDOS;
describe PROVINCIAS;
describe VOTANTES;

--Ejercicio 4--

drop table eventos cascade constraints;
drop table eventos_resultados cascade constraints;
drop table consultas cascade constraints;
drop table consultas_datos cascade constraints;
drop table localidades cascade constraints;
drop table partidos cascade constraints;
drop table provincias cascade constraints;
drop table votantes cascade constraints;

--Ejercicio 5 y 6--

insert into votantes
values (30653845, 'Maria Gonzalez Ramirez', 'Doctorado', 'Activo','goram@telefonica.es',1,'21/8/1989',677544822); 
select * from votantes;

--Ejercicio 7--

delete from votantes where dni=30653845;
select * from votantes;

--Ejercicio 8--

insert into eventos_resultados
values (46, 3, 2, 0.11);
select * from eventos_resultados;
delete from eventos_resultados where idresultado=46;

--Ejercicio 9--

select nombre, tipo, fecha from eventos;

--Ejercicio 10--

select concat(concat(nombre, ' del tipo '),tipo) from eventos;

--Ejercicio 11--

select concat(concat(concat(nombre, ' con '),numeroHabitantes), ' habitantes.') from localidades;
