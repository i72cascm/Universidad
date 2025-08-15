--------------------------------
------ EJERCICIO 1 ANGEL -------
--------------------------------

select v.estudiossuperiores, count(v.dni) as "total", 
    (select count(v2.dni)
    from votantes v2
    where v2.situacionLaboral = 'Parado' and v2.estudiossuperiores = v.estudiossuperiores) as "parado",
    (select count(v2.dni)
    from votantes v2
    where v2.situacionLaboral = 'Activo' and v2.estudiossuperiores = v.estudiossuperiores) as "activo",
    (select count(v2.dni)
    from votantes v2
    where v2.situacionLaboral = 'Estudiante' and v2.estudiossuperiores = v.estudiossuperiores) as "estudiante",
    (select count(v2.dni)
    from votantes v2
    where v2.situacionLaboral = 'Jubilado' and v2.estudiossuperiores = v.estudiossuperiores) as "jubilado"
from votantes v
group by v.estudiossuperiores;


-- SOL ANGEL 1

select v.estudiossuperiores, count(v.estudiossuperiores) as "TOTAL", sum(decode(v.situacionlaboral,'Parado',1,0)) as "Parado", sum(decode(v.situacionlaboral,'Activo',1,0)) as "Activo", sum(decode(v.situacionlaboral,'Estudiante',1,0)) as "Estudiante", sum(decode(v.situacionlaboral,'Jubilado',1,0)) as "Jubilado"
  from votantes v
  group by v.estudiossuperiores
  order by count(v.estudiossuperiores) desc;
  
-- SOL ANGEL 2
  
  select v.estudiossuperiores,count(dni) total,
       (select count(dni)
            from votantes
            where situacionlaboral='Parado' and estudiossuperiores=v.estudiossuperiores) parado,
        (select count(dni)
            from votantes
            where situacionlaboral='Activo' and estudiossuperiores=v.estudiossuperiores) activo,
        (select count(dni)
            from votantes
            where situacionlaboral='Estudiante' and estudiossuperiores=v.estudiossuperiores) estudiante,
        (select count(dni)
            from votantes
            where situacionlaboral='Jubilado' and estudiossuperiores=v.estudiossuperiores) jubilado
from votantes v
group by v.estudiossuperiores;