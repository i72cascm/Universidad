--Ejercicio 12--

select nombrecompleto, avg(certidumbre)
from votantes, consultas, consultas_datos
where votantes.dni=consultas.votante and consultas.idconsulta=consultas_datos.consulta and consultas_datos.respuesta='Si'
having avg(certidumbre)>'0,5' and avg(certidumbre)<'0,8'
group by nombrecompleto;