--Enero 2019/2020:
--Ejercicio 1: Se desea visualizar el número de votantes de cada localidad respecto a su situación laboral. Muestre el número total de votantes de cada localidad en una columna. En las otras columnas debe aparecer el número total de votantes de esa localidad según su situación laboral: parado, activo, estudiante o jubilado.
SELECT localidades.nombre "Localidad", 
(SELECT COUNT(votantes.dni) FROM votantes WHERE votantes.localidad = localidades.idlocalidad) "Votantes", 
(SELECT COUNT(votantes.dni) FROM votantes WHERE votantes.localidad = localidades.idlocalidad AND votantes.situacionlaboral LIKE 'Parado') "Parados",
(SELECT COUNT(votantes.dni) FROM votantes WHERE votantes.localidad = localidades.idlocalidad AND votantes.situacionlaboral LIKE 'Activo') "Activos",
(SELECT COUNT(votantes.dni) FROM votantes WHERE votantes.localidad = localidades.idlocalidad AND votantes.situacionlaboral LIKE 'Jubilado') "Jubilados",
(SELECT COUNT(votantes.dni) FROM votantes WHERE votantes.localidad = localidades.idlocalidad AND votantes.situacionlaboral LIKE 'Estudiante') "Estudiantes"
FROM localidades;

--Ejercicio 2: Muestre el nombre de los votantes cuya longitud del primer nombre sea menor que el ID  de la localidad a la que pertenecen y junto a ella muestre la diferencia de edad (en años) entre la persona más joven y más mayor de su localidad.
SELECT a.nombrecompleto "Nombre", ROUND((a.fechanacimiento - (SELECT MIN(b.fechanacimiento) FROM votantes b WHERE b.localidad = a.localidad))/365) "Diferencia"
FROM votantes a
WHERE LENGTH(SUBSTR(a.nombrecompleto, 1, INSTR(a.nombrecompleto, ' '))) < a.localidad;

--Ejercicio 3: Determinar cuál es el partido político con más resultados de eventos. Se tiene que hacer mediante un consulta PL/SQL.
--Es más fácil si se interpreta el mapa como un vector.
DECLARE
  TYPE hash_map IS TABLE OF NUMBER INDEX BY partidos.nombrecompleto%type;
  my_hm hash_map;
  key partidos.nombrecompleto%type;
  CURSOR c IS SELECT partidos.nombrecompleto, consultas_datos.partido FROM partidos, consultas_datos WHERE partidos.idpartido = consultas_datos.partido;
  mayor partidos.nombrecompleto%type;
BEGIN
  FOR num_row IN c 
  LOOP
    IF my_hm.exists(num_row.nombrecompleto) THEN my_hm(num_row.nombrecompleto) := my_hm(num_row.nombrecompleto)+1;
    ELSE my_hm(num_row.nombrecompleto) := +1;
    END IF;
  END LOOP;
  key := my_hm.FIRST;
  mayor := my_hm.FIRST;
  WHILE key IS NOT NULL LOOP
    IF my_hm(key) >= my_hm(mayor) THEN mayor := key; 
    END IF;
    key := my_hm.NEXT(key);
  END LOOP;
DBMS_OUTPUT.PUT_LINE(mayor||' -> '||my_hm(mayor));
END;

--Ejercicio 4: Cree una restricción para que no se inserten email inválidos. Los emails de los votantes deben tener antes del @ uno o más caracteres. Entre el @ y el . debe haber uno o más caracteres (asumiendo que sólo puede haber un . eb ek email) y ue después del . haya al menos dos caracteres.
ALTER TABLE votantes
ADD CONSTRAINT constraint_email CHECK(email LIKE '%_@_%._%');