--------------------------
------ Práctica 3.1 ------
--------------------------

-- Ejercicio 1 --

select nombrecompleto
from votantes v
where substr(v.dni,-1,1) = v.localidad + 1;

-- Ejercicio 2 --

select nombrecompleto, decode(l.nombre,'Cordoba', 'Madrid', 'Montilla', 'Madrid', 'Baena', 'Madrid', l.nombre) as nombre
from votantes v, localidades l
where v.localidad = l. idlocalidad
order by 2;

-- Ejercicio 3 --

select p.siglas
from partidos p, eventos_resultados er
where p.idpartido = er.partido
having count(er.partido) = (select max(count(er2.partido))
                            from eventos_resultados er2, partidos p2
                            where er2.partido = p2.idpartido
                            group by p2.siglas)
group by p.siglas
order by p.siglas;

-- Ejercicio 4 --

select v.dni
from votantes v
where v.fechanacimiento = (select min(v3.fechanacimiento)
                            from votantes v3
                            where v3.fechanacimiento > (select min(v2.fechanacimiento)
                                                        from votantes v2)); 

-- Ejercicio 5 --

select distinct c.votante, count(c.votante)
from consultas c
group by c.votante
order by 2 desc;

-- Ejercicio 6 --

select distinct c.votante, count(c.votante)
from consultas c
having count(c.votante) > (select avg(count(c2.votante))
                            from consultas c2
                            group by c2.votante)
group by c.votante
order by 2 DESC;

-- Ejercicio 7 --

select v.nombrecompleto
from votantes v, consultas c
where v.dni = c.votante
having count(c.votante) > (select avg(count(c2.votante))
                            from consultas c2
                            group by c2.votante)
group by v.nombrecompleto;

-- Ejercicio 8 --

select c.votante, count(c.votante)
from consultas c, votantes v
where v.dni = c.votante and v.fechanacimiento != (select min(v3.fechanacimiento)
                                                    from votantes v3
                                                    where v3.fechanacimiento > (select min(v2.fechanacimiento)
                                                                                from votantes v2))
group by c.votante
order by 2 desc;