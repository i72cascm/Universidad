---------------------------
------ Práctica 5.2 -------
---------------------------

-- Ejercicio 1 --
set serveroutput on;
drop table votantesAntiguos2;

create table votantesAntiguos2(
dni number(8) primary key,
nombreCompleto varchar2(64),
estudiosSuperiores varchar2(64) not null,
situacionLaboral varchar2(64) not null,
email varchar2(32) not null,
localidad number(3) not null,
fechaNacimiento date not null,
telefono number(14),
sueldo number(32)
);

DECLARE
    cursor c is select * from votantes v where v.fechanacimiento < '01/01/80';
    cont number := 0;
BEGIN
    for num_row in c loop
        if num_row.situacionLaboral = 'Activo' then
            insert into votantesAntiguos2 values (num_row.dni, num_row.nombreCompleto, num_row.estudiosSuperiores, num_row.situacionLaboral, num_row.email, num_row.localidad, num_row.fechaNacimiento, num_row.telefono, 1500);
            dbms_output.put_line('Votante ' || num_row.nombreCompleto || ' introducido.');
            cont := cont + 1;
        else
            insert into votantesAntiguos2 values (num_row.dni, num_row.nombreCompleto, num_row.estudiosSuperiores, num_row.situacionLaboral, num_row.email, num_row.localidad, num_row.fechaNacimiento, num_row.telefono, 0);
            dbms_output.put_line('Votante ' || num_row.nombreCompleto || ' introducido.');
            cont := cont + 1;
        end if;
    end loop;
    dbms_output.put_line('Se ha introducido un total de ' || cont || ' votantes.');
END;    

-- Ejercicio 2 --
set serveroutput on;

DECLARE
    cursor c is select * from votantesAntiguos2;
BEGIN
    for num_row in c loop
        if num_row.situacionLaboral = 'Jubilado' then
            update votantesAntiguos2 set sueldo = 1000 where dni = num_row.dni;
        else
            if num_row.estudiosSuperiores = 'Ninguno' then
                update votantesAntiguos2 set sueldo = (sueldo + 100) where dni = num_row.dni;
            elsif num_row.estudiosSuperiores = 'Basicos' then
                update votantesAntiguos2 set sueldo = (sueldo + 200) where dni = num_row.dni;
            elsif num_row.estudiosSuperiores = 'Superiores' then
                update votantesAntiguos2 set sueldo = (sueldo + 300) where dni = num_row.dni;
            else
                update votantesAntiguos2 set sueldo = (sueldo + 1000) where dni = num_row.dni;
            end if;
        end if;
    end loop;
END;

-- Ejercicio 3 --
set serveroutput on;

DECLARE
    cursor c is select * from votantesAntiguos2;
BEGIN
    for num_row in c loop
        if num_row.situacionLaboral = 'Jubilado' then
            update votantesAntiguos2 set sueldo = (sueldo*1.05) where dni = num_row.dni;
        else
            update votantesAntiguos2 set sueldo = (sueldo*1.02) where dni = num_row.dni;
        end if;
    end loop;
END;

-- Ejercicio 4 --
set serveroutput on;

DECLARE
    cursor c is select * from votantesAntiguos2;
    minimo number := 0;
    actual number := 0;
BEGIN
    select min(count(c.votante)) into minimo
    from votantesAntiguos2 v, consultas c
    where v.dni = c.votante
    group by v.dni;

    for num_row in c loop
        
        select count(c.votante) into actual
        from votantesAntiguos2 v, consultas c
        where v.dni = c.votante and v.dni = num_row.dni
        group by v.dni;
    
        if actual = minimo then
            delete from votantesAntiguos2 where dni = num_row.dni;
        end if;
    end loop;
END;

-- Ejercicio 5 --
set serveroutput on;

INSERT INTO partidos
VALUES (6, 'Partido Ejemplo', 'PE', 'c/ Ejemplo 123', 'Barcelona', 'Juan Pérez', '01/01/1980', 0);

DECLARE
    cursor c is select * from partidos;
    nuevoPresupuesto number := 0;
    cont number := 0;
BEGIN
    for num_row in c loop
        nuevoPresupuesto := nuevoPresupuesto + num_row.presupuesto;
        cont := cont + 1;
    end loop;
    nuevoPresupuesto := (nuevoPresupuesto/cont);
    for num_row in c loop
        update partidos set presupuesto = nuevoPresupuesto where idpartido = num_row.idpartido;
    end loop;
END;