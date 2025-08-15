--------------------------
------ Práctica 2.1 ------
--------------------------

-- Ejercicio 1 --

select nombrecompleto
from votantes v
where nombrecompleto like '%n';

-- Ejercicio 2 --

select dni
from votantes
where dni like '%5%5%5%';

-- Ejercicio 3 --

select nombrecompleto
from votantes v
where fechaNacimiento > '01/01/1990';

-- Ejercicio 4 --

select nombrecompleto, nombre
from votantes v, localidades l
where v.localidad = l.idlocalidad and l.numerohabitantes > 300000;

-- Ejercicio 5 --

select nombrecompleto, comunidad
from votantes v, provincias p, localidades l
where v.localidad = l.idlocalidad and l.provincia = p.idprovincia and l.numerohabitantes > 300000;

-- Ejercicio 6 --

select idpartido, count(partido) as "conteo"
from partidos p, consultas_datos c
where p.idpartido = c.partido
group by idpartido;

-- Ejercicio 7 --

select idpartido, count(partido) as "conteo"
from partidos p, consultas_datos c
where p.idpartido = c.partido
group by countpartido;

-- Ejericio 8 --

select nombrecompleto
from partidos p, consultas_datos c
where p.idpartido = c.partido
having count(c.partido) > 10
group by nombrecompleto;

-- Ejercicio 9 --

select nombrecompleto, count(partido) as conteo
from partidos p, consultas_datos c
where p.idpartido = c.partido
having count(c.partido) > 10
group by p.nombrecompleto;

-- Ejercicio 10 --

select nombrecompleto, count(partido) as conteo
from partidos p, consultas_datos c
where p.idpartido = c.partido and c.respuesta = 'Si' and certidumbre > 0.8
group by nombrecompleto;
