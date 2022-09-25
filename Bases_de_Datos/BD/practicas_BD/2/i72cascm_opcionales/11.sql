--Ejercicio 11--

select nombrecompleto, avg(certidumbre)
from votantes, consultas_datos, consultas
where votantes.dni=consultas.votante and consultas.idconsulta=consultas_datos.consulta and consultas_datos.respuesta='Si'
group by nombrecompleto;