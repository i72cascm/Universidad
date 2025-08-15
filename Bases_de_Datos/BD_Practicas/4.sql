--------------------------
------ Práctica 4 --------
--------------------------

-- Ejercicio 1 --
set serveroutput on;

BEGIN
    DBMS_OUTPUT.PUT_LINE('Hola Mundo, hoy es '|| sysdate);
END;

-- Ejercicio 2 --
set serveroutput on;

DECLARE
    nombreCompleto votantes.nombrecompleto%TYPE;
    correo votantes.email%TYPE;
BEGIN
    select v.nombrecompleto, v.email INTO nombreCompleto, correo
    from votantes v
    where v.dni = 30983712;
    DBMS_OUTPUT.PUT_LINE(nombrecompleto || ' con correo: ' || correo);
END;

-- Ejercicio 3 --
set serveroutput on;

DECLARE
    nombre votantes.nombrecompleto%TYPE;
    correo votantes.email%TYPE;
begin
    select v.nombrecompleto, v.email INTO nombre, correo
    from votantes v
    where v.dni = 30983712;
    
    nombre := substr(nombre,1,instr(nombre,' ')-1);
    DBMS_OUTPUT.PUT_LINE(nombre || ' con correo: ' || correo);
END;

-- Ejercicio 4 --
set serveroutput on;

DECLARE
    apellidos votantes.nombrecompleto%TYPE;
    nombre votantes.nombrecompleto%type := 'Pepe';
BEGIN
    select v.nombrecompleto INTO apellidos
    from votantes v
    where v.dni = 30983712;
    
    apellidos := substr(apellidos,instr(apellidos,' '));
    DBMS_OUTPUT.PUT_LINE(nombre || Apellidos);
END;

-- Ejercicio 5 --
set serveroutput on;

DECLARE
    myNombre votantes.nombrecompleto%type;
    myDni votantes.dni%type;
BEGIN
    select v.nombrecompleto, v.dni INTO myNombre, myDni
    from votantes v
    where v.fechanacimiento = (select min(v2.fechanacimiento)
                                from votantes v2);
    
    DBMS_OUTPUT.PUT_LINE('El señor ' || myNombre || ' con dni ' || myDni || ' es el votante mas longevo.');
END;

-- Ejercicio 6 --
set serveroutput on;

DECLARE
    nombreViejo votantes.nombreCompleto%type;
    nombreNuevo votantes.nombreCompleto%type;
    correoViejo votantes.email%type;
    correoNuevo votantes.email%type;
BEGIN
    select v.nombrecompleto, v.email INTO nombreViejo, correoViejo
    from votantes v
    where v.fechanacimiento = (select min(v2.fechanacimiento)
                                from votantes v2);
    
    select v.nombrecompleto, v.email INTO nombreNuevo, correoNuevo
    from votantes v
    where v.fechanacimiento = (select max(v2.fechanacimiento)
                                from votantes v2);
                                
    correoViejo := substr(correoViejo,1,instr(correoViejo,'@')) || 'uco.es';
    correoNuevo := substr(correoNuevo,1,instr(correoNuevo,'@')) || 'uco.es';
                                
    DBMS_OUTPUT.PUT_LINE( nombreViejo || ' -- Email: ' || correoViejo);
    DBMS_OUTPUT.PUT_LINE( nombreNuevo || ' -- Email: ' || correoNuevo);
END;


-- Ejercicio 7 --
set serveroutput on;

DECLARE
    nombreViejo votantes.nombreCompleto%type;
    nombreNuevo votantes.nombreCompleto%type;
BEGIN
    select v.nombrecompleto into nombreNuevo
    from votantes v
    where fechanacimiento =(select max(v2.fechanacimiento)
                            from votantes v2);
                   
    select v.nombrecompleto into nombreViejo
    from votantes v
    where fechanacimiento = (select max(v3.fechanacimiento)
                                from votantes v3
                                where v3.fechanacimiento < (select max(v2.fechanacimiento)
                                                            from votantes v2));
                                                            
    nombrenuevo := substr(nombrenuevo,instr(nombrenuevo,' ')+1);
    nombrenuevo := substr(nombrenuevo,1,instr(nombrenuevo,' '));
    nombreviejo := substr(nombreviejo,instr(nombreviejo,' ')+1);
    nombreviejo := substr(nombreviejo,1,instr(nombreviejo,' '));
                                                            
    DBMS_OUTPUT.PUT_LINE('El hijo de llama: Juan ' || nombreViejo || nombreNuevo);
END;

-- Ejercicio 8 --
set serveroutput on;

DECLARE
    idLocalidad1 localidades.idLocalidad%TYPE;
    idLocalidad2 localidades.idLocalidad%TYPE;
    habitantesLocalidad1 localidades.numeroHabitantes%TYPE;
    habitantesLocalidad2 localidades.numeroHabitantes%TYPE;
  
    habitantesSuma localidades.numeroHabitantes%TYPE;
    numeroLocalidades INT;
BEGIN
    select min(l.idlocalidad) into idLocalidad1
    from localidades l;
    
    select min(l.idlocalidad) into idLocalidad2
    from localidades l
    where l.idlocalidad > idLocalidad1;
    
    select l.numerohabitantes into habitantesLocalidad1
    from localidades l
    where l.idlocalidad = idLocalidad1;
    
    select l.numerohabitantes into habitantesLocalidad2
    from localidades l
    where l.idlocalidad = idLocalidad2;

    habitantesSuma := habitantesLocalidad1 + habitantesLocalidad2;
    
    SELECT COUNT(*) INTO numeroLocalidades FROM localidades
    WHERE numeroHabitantes > habitantesSuma;

    dbms_output.put_line('Hay ' || numeroLocalidades || ' ciudades con mas de ' || habitantesSuma || ' habitantes, que es la suma de las dos localidades con IDs mas pequeños');
END;
