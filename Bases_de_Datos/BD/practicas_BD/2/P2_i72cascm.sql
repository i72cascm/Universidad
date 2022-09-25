--Ejercicio 1--

select * from votantes where nombrecompleto like '%n';
 
--Ejercicio 2--
 
select dni from votantes where dni like '%5%5%5%';
 
--Ejercicio 3--
 
select * from votantes where fechanacimiento>'01/01/90';
 
--Ejercicio 4--
 
select votantes.nombreCompleto, localidades.nombre from votantes, localidades where votantes.localidad=localidades.idlocalidad and localidades.numerohabitantes>'300000';
 
--Ejercicio 5--
 
select votantes.nombrecompleto, provincias.nombre from votantes, provincias, localidades where votantes.localidad=localidades.idlocalidad and localidades.numerohabitantes>'300000' and provincias.nombre=localidades.nombre;
 
--Ejercicio 6--
 
select partido, count(consulta) from consultas_datos group by partido;

--Ejercicio 7--

--Hay algo en el enunciado q esta mal--

--Ejercicio 8--

select nombrecompleto from consultas_datos,partidos where consultas_datos.partido=partidos.idpartido having count(consulta)>10 group by nombrecompleto;

--Ejercicio 9--

select nombrecompleto,count(consulta) from consultas_datos,partidos where consultas_datos.partido=partidos.idpartido having count(consulta)>10 group by nombrecompleto;

--Ejercicio 10--

select nombrecompleto,count(consulta) from consultas_datos,partidos where consultas_datos.partido=partidos.idpartido and respuesta='Si' and certidumbre>'0,8' group by nombrecompleto;