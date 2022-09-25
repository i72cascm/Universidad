--Ejercicio 1:
SELECT votantes.nombrecompleto
FROM votantes
WHERE nombrecompleto LIKE '%n';

--Ejercicio 2:
SELECT votantes.dni
FROM votantes
WHERE dni LIKE '%5%5%5%';

--Ejercicio 3:
SELECT votantes.nombrecompleto
FROM votantes
WHERE fechanacimiento > '01/01/1990';

--Ejercicio 4:
SELECT votantes.nombrecompleto, localidades.nombre
FROM votantes, localidades
WHERE localidades.idlocalidad = votantes.localidad 
AND localidades.numerohabitantes > 300000;

--Ejercicio 5:
SELECT votantes.nombrecompleto, provincias.comunidad
FROM votantes, provincias, localidades
WHERE votantes.localidad = localidades.idlocalidad
AND localidades.provincia = provincias.idprovincia
AND localidades.numerohabitantes > 300000;

--Ejercicio 6: 
SELECT partidos.idpartido "Partido", COUNT(consultas_datos.consulta) "Conteo"
FROM partidos, consultas_datos
WHERE partidos.idpartido = consultas_datos.partido
GROUP BY partido
ORDER BY partido;
--NOTA: ORDER BY TIENE QUE IR AL FINAL.

--Ejercicio 8:
SELECT partidos.nombrecompleto
FROM partidos, consultas_datos
WHERE partidos.idpartido = consultas_datos.partido
HAVING COUNT(consultas_datos.consulta) > 10
GROUP BY partidos.nombrecompleto;

--Ejercicio 9:
SELECT partidos.nombrecompleto, COUNT(consultas_datos.consulta) "Conteo"
FROM partidos, consultas_datos
WHERE partidos.idpartido = consultas_datos.partido
HAVING COUNT(consultas_datos.consulta) > 10
GROUP BY partidos.nombrecompleto;

--Ejercicio 10:
SELECT partidos.nombrecompleto, COUNT(consultas_datos.consulta) "Conteo"
FROM partidos, consultas_datos
WHERE partidos.idpartido = consultas_datos.partido
AND consultas_datos.respuesta LIKE 'Si'
AND consultas_datos.certidumbre > 0.8
GROUP BY partidos.nombrecompleto;