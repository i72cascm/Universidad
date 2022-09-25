--Ejercicio 10--

select nombrecompleto, max(certidumbre)
from partidos, consultas_datos
where partidos.idpartido=consultas_datos.partido
group by nombrecompleto;