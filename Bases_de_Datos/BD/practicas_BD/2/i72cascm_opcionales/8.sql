--Ejercicio 8--

select nombrecompleto, count(votante) 
from votantes,consultas
where votantes.dni=consultas.votante
having count(votante)>3 
group by nombrecompleto
order by count(votante) ASC;