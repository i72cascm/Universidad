--Ejercicio 6--

select distinct dni 
from votantes, consultas 
where consultas.votante=votantes.dni
order by dni ASC;