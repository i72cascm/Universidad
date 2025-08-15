--------------------------------
--- EJERCICIO Sueltos ANGEL ----
--------------------------------

select v.nombrecompleto, count(c.votante)
from votantes v, consultas c
where dni like '%1%0%' and v.dni = c.votante
having count(c.votante) > 3
group by v.nombrecompleto
order by 2 asc;

