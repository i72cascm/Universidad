--------------------------
------ Práctica 2.2 ------
--------------------------

-- Ejercicio 1 --

select dni, telefono
from votantes v
where telefono like '%6%6%' and telefono not like '%6%6%6%';

-- Ejercicio 2 --

select dni, telefono
from votantes v
where telefono like '%66%6%' and telefono like '%6%66%' and telefono not like '%6%6%6%6%';

-- Ejercicio 3 --

select l.nombre, p.nombre
from localidades l, provincias p
where l.provincia = p.idprovincia and l.numerohabitantes like '%' || l.provincia;

-- Ejercicio 4 --

select nombrecompleto, dni, telefono
from votantes v
where substr(dni,-1,1) = substr(telefono,-1,1);

-- Ejercicio 5 --

select nombrecompleto, fechanacimiento
from votantes v
where nombrecompleto like '%s%' and fechanacimiento < '12/02/1990';

-- Ejercicio 6 --

select distinct nombrecompleto, dni
from votantes v, consultas c
where v.dni = c.votante
order by v.dni;

-- Ejercicio 7 --

select dni
from votantes v, consultas c
where v.dni = c.votante
having count(c.votante) > 3
group by dni;

-- Ejercicio 8 --

select v.nombrecompleto, count(c.votante)
from votantes v, consultas c
where v.dni = c.votante
group by v.nombrecompleto
having count(c.votante) > 3
order by count(c.votante) ASC;

-- Ejercicio 9 --

select distinct v.nombrecompleto, l.nombre
from votantes v, localidades l, consultas c
where l.idlocalidad = v.localidad and v.dni = c.votante and l.numerohabitantes > 300000;

-- Ejercicio 10 --

select p.nombrecompleto, max(c.certidumbre)
from partidos p, consultas_datos c
where c.partido = p.idpartido
group by p.nombrecompleto;

-- Ejercicio 11 --

select v.nombrecompleto, AVG(cd.certidumbre)
from votantes v, consultas_datos cd, consultas c
where v.dni = c.votante and c.idconsulta = cd.consulta and cd.respuesta = 'Si'
group by v.nombrecompleto;

-- Ejercicio 12 --

select v.nombrecompleto, avg(cd.certidumbre)
from votantes v, consultas_datos cd, consultas c
where v.dni = c.votante and c.idconsulta = cd.consulta and cd.respuesta = 'Si'
having avg(cd.certidumbre) between 0.5 and 0.8
group by v.nombrecompleto;

-- Ejercicio 13 --

SELECT p.nombrecompleto, AVG(cd.certidumbre)
FROM partidos p, consultas_datos cd
WHERE p.idpartido = cd.partido AND cd.respuesta = 'No'
HAVING COUNT(cd.certidumbre) > 0.6
GROUP BY p.nombrecompleto;
