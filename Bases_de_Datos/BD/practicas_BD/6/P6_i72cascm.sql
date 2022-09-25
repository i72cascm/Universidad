--Creacion tabla--

CREATE TABLE "AUDIT_TABLE"("DATOS" VARCHAR2(100 BYTE), "TABLA" VARCHAR2(100 BYTE));

--Ejercicio 1--

set serveroutput on;
create or replace trigger eve
    after update or insert on eventos
    for each row
begin
    insert into audit_table
    values(:old.nombre ||' ' || :new.nombre, 'EVENTOS');
end;

--Update valor para ej 1--

update eventos set nombre='Madrid 2020'
where idevento=10;

--Ejercicio 2--

SET serveroutput ON;
CREATE OR REPLACE TRIGGER habitantes_loc
  BEFORE UPDATE or INSERT ON localidades
  FOR EACH ROW
BEGIN
  IF :new.numerohabitantes > 4000000 or :new.numerohabitantes < 1
  THEN :new.numerohabitantes := :old.numerohabitantes;
  END IF;
END;