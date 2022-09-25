--Ejercicio 1:
select substr(votantes.nombrecompleto, 1, instr(votantes.nombrecompleto, ' ')) "Nombre", localidades.nombre "Localidad", provincias.comunidad "Comunidad"
from votantes, localidades, provincias
where votantes.localidad = localidades.idlocalidad
and localidades.provincia = provincias.idprovincia
and localidades.idlocalidad in(1, 3, 9);

--Ejercicio 2:
select concat(a.nombre, concat(' va antes que ', b.nombre))
from localidades a, localidades b
where b.idlocalidad = a.idlocalidad+1
order by a.idlocalidad asc;

--Ejercicio 3:
select localidades.nombre
from localidades
where localidades.numerohabitantes > (select localidades.numerohabitantes from localidades where localidades.nombre like (select localidades.nombre
from localidades, votantes
where localidades.idlocalidad = votantes.localidad
and votantes.fechanacimiento = (select min(votantes.fechanacimiento) from votantes
where votantes.fechanacimiento > (select min(votantes.fechanacimiento) from votantes))));

--Ejercicio 4: FALTA POR TERMINAR
select votantes.nombrecompleto, votantes.localidad, votantes.fechanacimiento
from votantes
where votantes.localidad in(2, 4, 8)

--Ejercicio 5:
select localidades.nombre, localidades.numerohabitantes, provincias.comunidad
from localidades, provincias
where localidades.provincia = provincias.idprovincia
and localidades.provincia in(1, 2, 3)
and localidades.numerohabitantes > (select localidades.numerohabitantes from localidades where localidades.idlocalidad = 4);

--Ejercicio 6:
select votantes.nombrecompleto
from votantes, consultas
where votantes.dni = consultas.votante
and votantes.situacionlaboral = 'Activo'
having count(consultas.votante) < (select avg(count(consultas.votante)) from consultas group by consultas.votante)
group by votantes.nombrecompleto;

--Ejercicio 7:
select localidades.nombre "Localidad", avg(decode(votantes.estudiossuperiores, 'Ninguno', 0, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3, votantes.estudiossuperiores)) "Estudios"
from localidades, votantes
where votantes.localidad = localidades.idlocalidad
group by localidades.nombre
order by "Estudios" desc;

--Ejercicio 8:
select localidades.nombre "Localidad"
from localidades, votantes, provincias
where votantes.localidad = localidades.idlocalidad
and localidades.provincia = provincias.idprovincia
having avg(decode(votantes.estudiossuperiores, 'Ninguno', 0, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3, votantes.estudiossuperiores))
> all(select avg(decode(votantes.estudiossuperiores, 'Ninguno', 0, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3, votantes.estudiossuperiores)) 
from votantes, localidades, provincias
where votantes.localidad = localidades.idlocalidad
and localidades.provincia = provincias.idprovincia
group by provincias.nombre) group by localidades.nombre;