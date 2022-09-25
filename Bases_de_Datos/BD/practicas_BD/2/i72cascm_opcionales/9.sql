--Ejercicio 9--

select distinct nombrecompleto, nombre 
from votantes, localidades, consultas 
where localidades.idlocalidad=votantes.localidad and localidades.numerohabitantes>300000 and consultas.votante=votantes.dni;