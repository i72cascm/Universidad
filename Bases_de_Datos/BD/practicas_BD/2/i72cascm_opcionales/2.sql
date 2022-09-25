--Valores de prueba para comprobar el ejercicio--

insert into votantes
values (30911712, 'Antonio Lopez Lopez', 'Basicos', 'Parado','jpsssp@gmail.com',5,'23/02/1982',662236293);

insert into votantes
values (80911712, 'Antonio Gomez Lopez', 'Basicos', 'Parado','jpsssp@gmail.com',5,'23/02/1982',622366093);

insert into votantes
values (30915712, 'Antonio Lopez Gomez', 'Basicos', 'Parado','jpsssp@gmail.com',5,'23/02/1982',662636293);

insert into votantes
values (30911733, 'Eduardo Lopez Lopez', 'Basicos', 'Parado','jpsssp@gmail.com',5,'23/02/1982',626236293);

--Ejercicio 2--

select dni 
from votantes 
where telefono 
like '%66%6%' or telefono like '%6%66%' and telefono not like '%6%6%6%';