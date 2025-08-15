---------------------------
------ Práctica 5.1 -------
---------------------------

-- Ejercicio 1 --
set serveroutput on;

DECLARE
    cursor c is select * from votantes v where dni like '%' || (v.localidad+1);     
    cont number := 0;
BEGIN
    for num_row in c loop
        cont := cont + 1;
        DBMS_OUTPUT.PUT_LINE(num_row.nombrecompleto);
    end loop;
    DBMS_OUTPUT.PUT_LINE('Hay un total de ' || cont || ' votantes.');
END;

-- Ejercicio 2 --
set serveroutput on;

DECLARE
    cursor c is select * from votantes v where dni like '%' || (v.localidad+1);
    votantesData votantes%ROWTYPE;
    cont number := 0;
BEGIN
    open c;
    LOOP
        fetch c into votantesData;
        exit when c%notfound;
        dbms_output.put_line(votantesData.nombreCompleto);
        cont := cont + 1;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Hay un total de ' || cont || ' votantes.');
END;

-- Ejercicio 3 --
set serveroutput on;

DECLARE
    cursor c is select * from votantes v where v.dni like '%' || (v.localidad+1);
    votantes_data votantes%rowtype;
    num number := 0;
BEGIN
    open c;
    fetch c into votantes_data;
    
    while c%found loop
        dbms_output.put_line(votantes_data.nombreCompleto);
        num := num + 1;
        fetch c into votantes_data;   
    end loop;
    
    dbms_output.put_line('Hay un total de ' || num || ' votantes.');
END;

-- Ejercicio 4 --
set serveroutput on;

DECLARE
    cursor c is select * from votantes;
    localidad localidades.nombre%type;
    cont number := 0;
BEGIN
    for num_row in c loop
    
        select l.nombre into localidad
        from localidades l
        where l.idlocalidad = num_row.localidad;
        
        if num_row.localidad in (1,2,3) then
        localidad := 'Madrid';
        end if;
        
        if localidad = 'Madrid' then
        cont := cont + 1;
        end if;
        
        DBMS_OUTPUT.PUT_LINE(num_row.nombrecompleto || 'es de ' || localidad);
    end loop;
    DBMS_OUTPUT.PUT_LINE('Hay un total de ' || cont || ' votantes en Madrid.');
END;

-- Ejercicio 5 --
set serveroutput on;

DECLARE
    cursor c is select * from votantes order by votantes.dni desc;
    minDni votantes.dni%type;
    nextDni votantes.dni%type;
BEGIN
    select min(v.dni) into minDni from votantes v;
    for num_row in c loop
        if num_row.dni > minDni then
            select max(v.dni) into nextDni
            from votantes v
            where v.dni < num_row.dni;
            dbms_output.put_line(num_row.dni || ' va antes que ' || nextDni);
        else
            dbms_output.put_line(num_row.dni || ' es el menor.');
        end if;
    end loop;
END;


-- Ejercicio 6 --
set serveroutput on;

DECLARE
cursor c is select c.votante, count(c.votante) as conteo
            from consultas c
            having count(c.votante) > (select avg(count(c2.votante))
                                    from consultas c2
                                    group by c2.votante)
            group by c.votante
            order by 2 desc;
BEGIN
    for num_row in c loop
        dbms_output.put_line(num_row.votante || ' ha participado ' || num_row.conteo || ' veces.');
    end loop;
END;

-- Ejercicio 7 --
drop table votantesAntiguos;

create table votantesAntiguos
(dni varchar2(64) primary key,
nombreCompleto varchar2(64) not null,
email varchar2(64) not null,
fechaNacimiento date not null,
sueldo number(20) not null);

set serveroutput on;

DECLARE
    cursor c is select dni, nombreCompleto, email, fechaNacimiento, situacionLaboral from votantes where fechaNacimiento < '01/01/80';
    cont number := 0;
BEGIN
    for num_row in c loop
        if num_row.situacionLaboral = 'Activo' then
            insert into votantesAntiguos values (num_row.dni, num_row.nombreCompleto, num_row.email, num_row.fechaNacimiento, 1500);
            dbms_output.put_line('Se ha insertado a ' || num_row.nombrecompleto);
            cont := cont + 1;
        else
            insert into votantesAntiguos values (num_row.dni, num_row.nombreCompleto, num_row.email, num_row.fechaNacimiento, 0);
            dbms_output.put_line('Se ha insertado a ' || num_row.nombrecompleto);
            cont := cont + 1;
        end if;
    end loop;
    dbms_output.put_line('Se ha insertado un total de ' || cont || ' votantes.');
END;

-- Ejercicio 8 --
set serveroutput on;

DECLARE
    cursor c is select nombreCompleto from votantesAntiguos;
    nombreActual votantesAntiguos.nombreCompleto%type;
    contActual number := 0;
    contTotal number := 0;
BEGIN
    for num_row in c loop
        nombreActual := substr(num_row.nombreCompleto,1,instr(num_row.nombreCompleto,' ')-1);
        contActual := length(nombreActual);
        dbms_output.put_line(nombreActual || ' tiene '|| contActual || ' letras.');
        contTotal := contTotal + contActual;
    end loop;
    dbms_output.put_line('En total hay ' || contTotal || ' letras.');
END;

-- Ejercicio 9 --
set serveroutput on;

DECLARE
    cursor c is select * from votantesAntiguos order by fechaNacimiento ASC;
    cursor c2 is select * from votantesAntiguos order by fechaNacimiento ASC;
    nombreActual votantesAntiguos.nombrecompleto%type;
    nombreAux votantesAntiguos.nombrecompleto%type;
    contActual number := 0;
    contAux number := 0;
    flagNinguno number := 0;
BEGIN
    for num_row in c loop
        nombreActual := substr(num_row.nombrecompleto,1,instr(num_row.nombrecompleto,' ')-1);
        contActual := length(nombreActual);
        flagNinguno := 0;
        dbms_output.put_line(num_row.nombrecompleto || ' tiene mas letras (nombre sin apellidos) que los siguientes mas jovenes: ');
        for num_row2 in c2 loop
            nombreAux := substr(num_row2.nombrecompleto,1,instr(num_row2.nombrecompleto,' ')-1);
            contAux := length(nombreAux);
            if contAux < contActual then
                dbms_output.put_line(num_row2.nombrecompleto);
                flagNinguno := 1;
            end if;
        end loop;
        if flagNinguno = 0 then
            dbms_output.put_line('Nadie cumple esta condicion.');
        end if;
    end loop;
END;