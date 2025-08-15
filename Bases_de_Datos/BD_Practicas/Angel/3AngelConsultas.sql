--------------------------------
------ EJERCICIO 3 ANGEL -------
--------------------------------

select v.estudiossuperiores,
    100*(select count(v2.dni)
    from votantes v2
    where v2.situacionlaboral = 'Parado' and v2.estudiossuperiores = v.estudiossuperiores and v2.dni in (select distinct v3.dni
                                                                                                            from votantes v3, consultas c3
                                                                                                            where v3.dni = c3.votante
                                                                                                            having count(c3.votante) = (select min(count(c4.votante))
                                                                                                                                        from consultas c4
                                                                                                                                        group by c4.votante)
                                                                                                            group by v3.dni)) as "sueldosparados",
    1500*(select count(v2.dni)
    from votantes v2
    where v2.situacionlaboral = 'Activo' and v2.estudiossuperiores = v.estudiossuperiores and v2.dni in (select distinct v3.dni
                                                                                                            from votantes v3, consultas c3
                                                                                                            where v3.dni = c3.votante
                                                                                                            having count(c3.votante) = (select min(count(c4.votante))
                                                                                                                                        from consultas c4
                                                                                                                                        group by c4.votante)
                                                                                                            group by v3.dni)) as "sueldosactivos",
    100*(select count(v2.dni)
    from votantes v2
    where v2.situacionlaboral = 'Estudiante' and v2.estudiossuperiores = v.estudiossuperiores and v2.dni in (select distinct v3.dni
                                                                                                            from votantes v3, consultas c3
                                                                                                            where v3.dni = c3.votante
                                                                                                            having count(c3.votante) = (select min(count(c4.votante))
                                                                                                                                        from consultas c4
                                                                                                                                        group by c4.votante)
                                                                                                            group by v3.dni)) as "sueldosestudiantes",
    1500*(select count(v2.dni)
    from votantes v2
    where v2.situacionlaboral = 'Jubilado' and v2.estudiossuperiores = v.estudiossuperiores and v2.dni in (select distinct v3.dni
                                                                                                            from votantes v3, consultas c3
                                                                                                            where v3.dni = c3.votante
                                                                                                            having count(c3.votante) = (select min(count(c4.votante))
                                                                                                                                        from consultas c4
                                                                                                                                        group by c4.votante)
                                                                                                            group by v3.dni)) as "sueldosjubilado"
from votantes v
group by v.estudiossuperiores;


select distinct v3.dni
from votantes v3, consultas c3
where v3.dni = c3.votante
having count(c3.votante) = (select min(count(c4.votante))
                            from consultas c4
                            group by c4.votante)
group by v3.dni;

select min(count(c4.votante))
from consultas c4
group by c4.votante;






select v.estudiossuperiores,
        (select count(situacionlaboral)*100
        from votantes
        where dni in (select votante
                        from consultas
                        group by votante
                        having count(votante) = (select min(count(votante))
                        from consultas
                        group by votante))
            and estudiossuperiores=v.estudiossuperiores and situacionlaboral='Parado') sueldosparados,
        (select count(situacionlaboral)*1500
        from votantes
        where dni in (select votante
                        from consultas
                        group by votante
                        having count(votante) = (select min(count(votante))
                        from consultas
                        group by votante))
            and estudiossuperiores=v.estudiossuperiores and situacionlaboral='Activo') sueldosactivos,
        (select count(situacionlaboral)*100
        from votantes
        where dni in (select votante
                        from consultas
                        group by votante
                        having count(votante) = (select min(count(votante))
                        from consultas
                        group by votante))
            and estudiossuperiores=v.estudiossuperiores and situacionlaboral='Estudiante') sueldosestudiantes,
        (select count(situacionlaboral)*1500
        from votantes
        where dni in (select votante
                        from consultas
                        group by votante
                        having count(votante) = (select min(count(votante))
                        from consultas
                        group by votante))
            and estudiossuperiores=v.estudiossuperiores and situacionlaboral='Jubilado') sueldosjubilados
from votantes v
group by v.estudiossuperiores;