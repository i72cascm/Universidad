--Ejercicio 7--

select votante 
from consultas 
having count(votante)>3 
group by votante;