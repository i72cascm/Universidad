--------------------------------
------ EJERCICIO 2 ANGEL -------
--------------------------------

select l.nombre as "nombreLocalidad", 
    (select count(v2.dni)
    from votantes v2
    where length(substr(v2.nombrecompleto,1,instr(v2.nombrecompleto,' ')-1)) < v2.localidad and l.idlocalidad = v2.localidad) as "total",
    (select (max(v2.fechanacimiento) - min(v2.fechanacimiento))/365
    from votantes v2
    where v2.localidad = l.idlocalidad) as "diferencia"
from localidades l
order by l.nombre asc;



-- SOL ANGEL

select l.nombre nombrelocalidad,
        (select count(dni)
        from votantes
        where length(substr(nombrecompleto,1,instr(nombrecompleto,' ')-1)) < localidad 
                and localidad=l.idlocalidad) total,
        (select trunc((max(fechanacimiento) - min(fechanacimiento))/365,0)
        from votantes
        where localidad=l.idlocalidad) diferencia
from localidades l
order by l.nombre;