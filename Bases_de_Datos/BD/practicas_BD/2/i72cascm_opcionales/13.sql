--Ejercicio 13--

select nombrecompleto, avg(certidumbre)
from partidos, consultas_datos
where partidos.idpartido=consultas_datos.partido and respuesta='No' and certidumbre>'0,6'
group by nombrecompleto;