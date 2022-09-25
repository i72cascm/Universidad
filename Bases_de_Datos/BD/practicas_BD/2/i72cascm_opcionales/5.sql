--Ejercicio 5--

select nombrecompleto 
from votantes 
where (nombrecompleto 
like '%s%' or nombrecompleto like '%S%') and fechanacimiento<'12/02/90';