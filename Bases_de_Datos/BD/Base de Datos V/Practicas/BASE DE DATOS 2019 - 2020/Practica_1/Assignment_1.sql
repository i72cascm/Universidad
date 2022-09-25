--Ejercicio 2:
SELECT table_name
FROM user_tables;

--Ejercicio 3:
DESCRIBE consultas;
DESCRIBE consultas_datos;
DESCRIBE eventos;
DESCRIBE eventos_resultados;
DESCRIBE localidades;
DESCRIBE partidos;
DESCRIBE provincias;
DESCRIBE votantes;
DESCRIBE votantes_antiguos;

--Ejercicio 4:
DROP TABLE votantes;
--Para poder eliminar la tabla votantes, primero hay que eliminar la tabla que apunta a votantes, y luego ya se podrá eliminar la tabla votantes.

--Ejercicio 5:
INSERT INTO votantes (votantes.dni, votantes.nombrecompleto, votantes.estudiossuperiores, votantes.situacionlaboral, votantes.email, votantes.localidad, votantes.fechanacimiento, votantes.telefono)
VALUES (30653845, 'Maria Gonzalez Ramirez', 'Doctorado', 'Activo', 'goram@telefonica.es', 1, '21/08/1989', 677544822);

--Ejercicio 6:
SELECT *
FROM votantes;

--Ejercicio 7:
DELETE
FROM votantes
WHERE dni = 30653845;

SELECT *
FROM votantes;

--Ejercicio 9:
SELECT eventos.nombre, eventos.tipo, eventos.fecha
FROM eventos;

--Ejercicio 10:
SELECT eventos.nombre || ' de tipo ' || eventos.tipo "Convocatoria"
FROM eventos;

--Ejercicio 11:
--Ejemplo 1.
SELECT votantes.nombrecompleto || ' nacido/a en ' || votantes.fechanacimiento "Votantes"
FROM votantes;
--Ejemplo 2.
SELECT ' Hay ' || provincias.numerohabitantes || ' habitantes en ' || provincias.nombre "Provincias"
FROM provincias;