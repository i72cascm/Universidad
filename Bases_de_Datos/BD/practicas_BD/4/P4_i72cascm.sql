--Ejercicio 1-- 

set serveroutput on;
BEGIN
   DBMS_OUTPUT.PUT_LINE('Hola mundo, hoy es '||sysdate);
END;

--Ejercicio 2--

set serveroutput on;
DECLARE
    mydni NUMBER := 30983712;
    nombre votantes.nombrecompleto%type;
    correo votantes.email%type;
BEGIN
    select nombrecompleto, email into nombre, correo
    from votantes
    where dni = mydni;
    
    DBMS_OUTPUT.PUT_LINE(nombre || ' con correo: ' || correo);
END;

--Ejercicio 3--

set serveroutput on;
declare
    mydni NUMBER := 30983712;
    correo votantes.email%type;
    nombre votantes.nombrecompleto%type;
begin
    select substr(nombrecompleto,1,instr(nombrecompleto,' ')), email into nombre, correo
    from votantes
    where dni = mydni;
    
    DBMS_OUTPUT.PUT_LINE(nombre || ' con correo: ' || correo);
end;

--Ejercicio 4--

set serveroutput on;
declare
    mydni NUMBER := 30983712;
    nombre votantes.nombrecompleto%type;
begin
    select substr(nombrecompleto,instr(nombrecompleto,' '),length(nombrecompleto)) into nombre
    from votantes
    where dni = mydni;
    
    DBMS_OUTPUT.PUT_LINE('Pepe' || nombre);
end;

--Ejercicio 5--

set serveroutput on;
declare
    nombre votantes.nombrecompleto%type;
    mydni votantes.dni%type;
begin
    select nombrecompleto, dni into nombre, mydni
    from votantes
    where fechanacimiento = 
        (select min(fechanacimiento)
        from votantes);
    
    DBMS_OUTPUT.PUT_LINE('El señor ' || nombre || ' con dni ' || mydni || ' es el votante mas longevo.');
end;

--Ejercicio 6--

set serveroutput on;
declare
    nombre1 votantes.nombrecompleto%type;
    nombre2 votantes.nombrecompleto%type;
    correo1 votantes.email%type;
    correo2 votantes.email%type;
begin
    select nombrecompleto, substr(email,1,instr(email,'@')) into nombre1, correo1
    from votantes
    where fechanacimiento =
        (select min(fechanacimiento)
        from votantes);
        
    select nombrecompleto, substr(email,1,instr(email,'@')) into nombre2, correo2
    from votantes
    where fechanacimiento =
        (select max(fechanacimiento)
        from votantes); 
    DBMS_OUTPUT.PUT_LINE(nombre1 || ' -- Email: ' || correo1 || 'uco.es');
    DBMS_OUTPUT.PUT_LINE(nombre2 || ' -- Email: ' || correo2 || 'uco.es');
end;

--Ejercicio 7--

set serveroutput on;
declare
    apellido1 votantes.nombrecompleto%type;
    apellido2 votantes.nombrecompleto%type;
begin
    select substr(substr(nombrecompleto,instr(nombrecompleto,' ')+1,length(nombrecompleto)),1,instr(substr(nombrecompleto,instr(nombrecompleto,' ')+1,length(nombrecompleto)),' ')) into apellido2
    from votantes
    where fechanacimiento =
        (select max(fechanacimiento)
        from votantes);
        
    select substr(substr(nombrecompleto,instr(nombrecompleto,' ')+1,length(nombrecompleto)),1,instr(substr(nombrecompleto,instr(nombrecompleto,' ')+1,length(nombrecompleto)),' ')) into apellido1
    from votantes
    where fechanacimiento =
        (select max(fechanacimiento)
        from votantes
        where fechanacimiento < (select max(fechanacimiento) from votantes));
        
    DBMS_OUTPUT.PUT_LINE('El hijo se llama Juan ' || apellido1 || apellido2);
end;

--Ejercicio 8--

set serveroutput on;
declare
    nhabitantes localidades.numerohabitantes%type;
    contador NUMBER := 1;
    sumtotal NUMBER := 0;
    
    contadorciudades NUMBER := 0;
    contador2 NUMBER := 1;
begin
    loop
        select numerohabitantes into nhabitantes
        from localidades
        where idlocalidad = contador;
        
        sumtotal := nhabitantes + sumtotal;
        contador := contador + 1;
        exit when contador = 3;
    end loop;        
    
    loop
        select numerohabitantes into nhabitantes
        from localidades
        where idlocalidad = contador2;
        
        if nhabitantes > sumtotal then
            contadorciudades := contadorciudades + 1;
        end if;
        contador2 := contador2 + 1;
        exit when contador2 = 17;
    end loop;  
    
    DBMS_OUTPUT.PUT_LINE('Hay ' || contadorciudades || ' ciudades con mas habitantes de ' || sumtotal || ' habitantes, que es la suma de las dos localidades con IDs mas pequeños.');
end;