--Ejercicio 1: Obtener el DNI de todos los votantes que tengan dos 6s en su telefono pero contemplar que no tienen mas de tres
SELECT votantes.dni, votantes.telefono "Prueba"
FROM votantes
WHERE votantes.telefono LIKE '%6%6%'
AND votantes.telefono NOT LIKE '%6%6%6%';

--Ejercicio 2: Obtener el DNI de todos los votantes que tengan tres 6s en su telefono pero contemplar que no tienen mas de tres, dos de ellos deben estar juntos
SELECT votantes.dni, votantes.telefono "Prueba"
FROM votantes
WHERE votantes.telefono LIKE '%6%6%6%'
AND votantes.telefono NOT LIKE '%6%66%6%';

--Ejercicio 3: Mostrar aquella localidad cuyo numero de habitantes acaba igual que su numero de provincia, mostrando tambien el nombre de la provincia a la que pertenece
select localidades.nombre, provincias.nombre
from localidades, provincias
where localidades.provincia = provincias.idprovincia
and localidades.numerohabitantes like '%_' || provincias.idprovincia;

--Ejercicio 4: Mostrar el nombre completo de los votantes cuyo telefono acaba igual que su dni
select votantes.nombrecompleto
from votantes
where telefono like '%_' || substr(dni, -1, 1);
NOTA: substr(expresion, inicio, longitud)
NOTA2: En este caso al poner el comienzo en -1 inicia desde el final.

--Ejercicio 5: Mostrar el nombre completo de aquellos votantes que contienen al menos una 'S' y cuya fecha de nacimiento es anterior al 12 de Febrero de 1990
SELECT votantes.nombrecompleto, votantes.fechanacimiento "Prueba"
FROM votantes
WHERE votantes.nombrecompleto LIKE '%s%'
AND votantes.fechanacimiento < '12/02/1990';

--Ejercicio 6: Usar el operador DISTINCT (http://www.w3schools.com/sql/sql_distinct.asp). Obtener todos los votantes que han participado en alguna consulta. Dichos votantes deben aparecer en orden decreciente de dni
SELECT DISTINCT consultas.votante
FROM consultas
ORDER BY consultas.votante DESC;

--Ejercicio 7: Mostrar el dni de aquellos votantes que han participado en mas de tres consultas
SELECT consultas.votante, COUNT(consultas.votante) "Prueba: Consultas"
FROM consultas
HAVING COUNT(consultas.votante) > 3
GROUP BY consultas.votante;

--Ejercicio 8: Mostrar el nombre completo de los votantes que han participado en mas de tres consultas y especificar en cuantas consultas participaron (en orden creciente)
select votantes.nombrecompleto "Votante", count(consultas.votante) "nº consultas"
from votantes, consultas
where votantes.dni = consultas.votante
having count(consultas.votante) > 3
group by votantes.nombrecompleto
order by "nº consultas" asc;

--Ejercicio 9: Obtener el nombre de los votantes y el nombre de su localidad para aquellos votantes que han sido consultados en una localidad que tiene mas de 300000 habitantes
SELECT DISTINCT consultas.votante, localidades.nombre "Localidad"
FROM consultas, votantes, localidades
WHERE consultas.votante = votantes.dni
AND votantes.localidad = localidades.idlocalidad
AND localidades.numerohabitantes > 300000;

--Ejercicio 10: Mostrar el nombre de cada partido politico y la maxima certidumbre que tiene para sus consultas
SELECT partidos.nombrecompleto, MAX(consultas_datos.certidumbre) "Maxima certidumbre"
FROM partidos, consultas_datos
WHERE partidos.idpartido = consultas_datos.partido
GROUP BY partidos.nombrecompleto;

--Ejercicio 11: Mostrar el nombre del votante y su certidumbre media en todas las consultas en las que ha respondido de manera afirmativa
SELECT votantes.nombrecompleto, AVG(consultas_datos.certidumbre) "Certidumbre media"
FROM votantes, consultas_datos, consultas
WHERE votantes.dni = consultas.votante
AND consultas.idconsulta = consultas_datos.idrecogida
AND consultas_datos.respuesta = 'Si'
GROUP BY votantes.nombrecompleto;

--Ejercicio 12: Mostrar el nombre del votante y su certidumbre media en todas las consultas en las que ha respondido de manera afirmativa UNICAMENTE para aquellos votantes cuyo certidumbre media esta entre 0'5 y 0'8
SELECT votantes.nombrecompleto, AVG(consultas_datos.certidumbre) "Certidumbre media"
FROM votantes, consultas_datos, consultas
WHERE votantes.dni = consultas.votante
AND consultas.idconsulta = consultas_datos.idrecogida
AND consultas_datos.respuesta = 'Si'
HAVING AVG(consultas_datos.certidumbre) < 0.8
AND AVG(consultas_datos.certidumbre) > 0.5
GROUP BY votantes.nombrecompleto;

--Ejercicio 13: Mostrar el nombre de los partidos y la certidumbre media obtenida para cada partido considerando solo aquellas consultas en las que el encuestado ha contestado negativamente a votar a dicho partido y con una certidumbre significativa (por encima del 60%)
SELECT partidos.nombrecompleto, AVG(consultas_datos.certidumbre)
FROM partidos, consultas_datos
WHERE partidos.idpartido = consultas_datos.partido
AND consultas_datos.respuesta = 'No'
AND consultas_datos.certidumbre > 0.6
GROUP BY partidos.nombrecompleto;