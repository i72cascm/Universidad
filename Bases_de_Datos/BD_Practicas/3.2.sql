--------------------------
------ Práctica 3.2 ------
--------------------------

-- Ejercicio 1 --

select substr(v.nombrecompleto,1,instr(v.nombrecompleto,' ')) as nombre, l.nombre as localidad, p.comunidad
from votantes v, localidades l, provincias p
where v.localidad = l.idlocalidad and l.provincia = p.idprovincia and l.idlocalidad in (1,3,9);

-- Ejercicio 2 --

select l.nombre || ' va antes que ' || l2.nombre AS Ordenacion
from localidades l, localidades l2
where l2.idlocalidad = l.idlocalidad+1;

-- Ejercicio 3 --

select l.nombre
from localidades l
where l.numerohabitantes > (select l4.numerohabitantes
                            from localidades l4, votantes v4
                            where v4.localidad = l4.idlocalidad and v4.fechanacimiento = (select min(v3.fechanacimiento)
                                                                                            from votantes v3
                                                                                            where v3.fechanacimiento > (select min(v2.fechanacimiento)
                                                                                                                        from votantes v2)));
                                                                                                                        
-- Ejercicio 4 --

select v.nombrecompleto, localidad, decode((SELECT 1
                                    FROM votantes
                                    WHERE dni = v.dni AND
                                    (sysdate-fechaNacimiento)/365 > 30), 1, 'mayor edad', 'menor edad')
from votantes v
where localidad in (2,4,8);

-- Ejercicio 5 --

select l.nombre, l.numerohabitantes, p.comunidad
from localidades l, provincias p
where p.idprovincia = l.provincia and l.provincia in (1,2,3) and l.numerohabitantes > (select min(l2.numerohabitantes)
                                                                                        from localidades l2
                                                                                        where l2.provincia in (4));
                                                                                        
-- Ejercicio 6 --

select v.nombrecompleto
from votantes v, consultas c
where c.votante = v.dni
having count(c.votante) < (select avg(count(c2.votante))
                            from consultas c2
                            group by c2.votante)
group by v.nombrecompleto;

-- Ejercicio 7 --

select l.nombre
from localidades l, votantes v
where l.idlocalidad = v.localidad
group by l.nombre
order by avg(decode(v.estudiossuperiores, 'Ninguno', 0, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3)) desc;

-- Ejercicio 8 --

select l.nombre
from localidades l, votantes v
where l.idlocalidad = v.localidad
having avg(decode(v.estudiossuperiores, 'Ninguno', 0, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3)) > (select max(avg(decode(v.estudiossuperiores, 'Ninguno', 0, 'Basicos', 1, 'Superiores', 2, 'Doctorado', 3)))
                                                    from votantes v, localidades l
                                                    where v.localidad = l.idlocalidad
                                                    group by l.provincia)
group by l.nombre;

-- Muestra todas las localidades y el número de votantes parados
SELECT v.localidad, (SELECT COUNT(dni)
                    FROM votantes
                    WHERE situacionLaboral = 'Parado'
                    AND localidad = v.localidad) "PARADOS"
FROM votantes v
GROUP BY v.localidad;

-- Muestra las localidades con parados y el número de parados
SELECT v.localidad, count(v.dni) "PARADOS"
FROM votantes v
WHERE v.situacionLaboral = 'Parado'
GROUP BY v.localidad;

