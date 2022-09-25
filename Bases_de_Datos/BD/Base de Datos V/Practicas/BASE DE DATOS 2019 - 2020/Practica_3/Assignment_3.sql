--Ejercicio 1:
SELECT votantes.nombrecompleto
FROM votantes
WHERE votantes.dni LIKE CONCAT('%', (votantes.localidad + 1));

--Ejercicio 2:
SELECT votantes.nombrecompleto, localidades.nombre, DECODE(votantes.localidad, 1, 'Madrid', 2, 'Madrid', 3, 'Madrid', localidades.nombre)
FROM votantes, localidades
WHERE votantes.localidad = localidades.idlocalidad;

--Ejercicio 3:
SELECT partidos.siglas
FROM partidos, eventos_resultados
WHERE partidos.idpartido = eventos_resultados.partido
HAVING COUNT(eventos_resultados.partido) > (SELECT AVG(COUNT(eventos_resultados.partido)) FROM eventos_resultados GROUP BY eventos_resultados.partido)
GROUP BY partidos.siglas;

--Ejercicio 4: NOTA: doble subconsulta
SELECT votantes.dni
FROM votantes
WHERE votantes.fechanacimiento = (SELECT MIN(votantes.fechanacimiento) FROM votantes 
WHERE votantes.fechanacimiento > (SELECT MIN(votantes.fechanacimiento) FROM votantes));

--Ejercicio 5:
SELECT consultas.votante "Votante", COUNT(consultas.votante) "Conteo"
FROM consultas
GROUP BY consultas.votante
ORDER BY "Conteo" DESC;

--Ejercicio 6:
SELECT consultas.votante "Votante", COUNT(consultas.votante) "Conteo"
FROM consultas
HAVING COUNT(consultas.votante) > (SELECT AVG(COUNT(consultas.votante)) FROM consultas GROUP BY consultas.votante)
GROUP BY consultas.votante
ORDER BY "Conteo" DESC;

--Ejercicio 7:
SELECT votantes.nombrecompleto
FROM votantes, consultas
WHERE votantes.dni = consultas.votante
HAVING COUNT(consultas.votante) > (SELECT AVG(COUNT(consultas.votante)) FROM consultas GROUP BY consultas.votante)
GROUP BY votantes.nombrecompleto;

--Ejercicio 8:
SELECT consultas.votante "Votante", COUNT(consultas.votante) "Conteo"
FROM consultas, votantes
WHERE votantes.dni = consultas.votante
AND votantes.dni <> (SELECT votantes.dni FROM votantes WHERE votantes.fechanacimiento = (SELECT MIN(votantes.fechanacimiento) FROM votantes WHERE votantes.fechanacimiento > (SELECT MIN(votantes.fechanacimiento) FROM votantes)))
GROUP BY consultas.votante
ORDER BY "Conteo" DESC;