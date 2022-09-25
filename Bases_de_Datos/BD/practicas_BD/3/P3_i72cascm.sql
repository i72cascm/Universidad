--Ejercicio 1--

select nombrecompleto
from votantes
where substr(dni,8,8)=localidad+1;

--Ejercicio 2--

select nombrecompleto, nombre
from votantes, localidades
where localidades.idlocalidad = decode(votantes.localidad, 1,9,2,9,3,9, votantes.localidad);

--Ejercicio 3--

select a.siglas
from partidos a, eventos_resultados b
where a.idpartido=b.partido
group by a.siglas
having count(b.partido) = (select max(count (b.partido))
from partidos a, eventos_resultados b
where a.idpartido=b.partido
group by a.siglas);


--Ejercicio 4--

select v.dni
from votantes v
where v.fechanacimiento = (select min(v.fechanacimiento) from votantes v
where v.fechanacimiento > (select min(v.fechanacimiento) from votantes v ));

--Ejercicio 5--

select v.dni, count(c.votante)
from votantes v, consultas c
where v.dni=c.votante
group by v.dni
order by count(c.votante) desc;

--Ejercicio 6--

select v.dni, count(c.votante)
from votantes v, consultas c
where v.dni=c.votante
group by v.dni
having count(c.votante) > (select avg(count(c.votante))
from votantes v, consultas c
where v.dni=c.votante
group by v.dni)
order by count(c.votante) desc;

--Ejercicio 7--

SELECT v.nombrecompleto
from consultas c, votantes v
where v.dni=c.votante
group by v.nombrecompleto
having count(c.votante) > (select avg(count(c.votante))
from votantes v, consultas c
where v.dni=c.votante
group by v.nombrecompleto);

--Ejercicio 8--


