CREATE TABLE "AUDIT_TABLE"("DATOS" VARCHAR2(100 BYTE), "TABLA" VARCHAR2(100 BYTE));

--Ejercicio 1:
SET serveroutput ON;
CREATE OR REPLACE TRIGGER eve
  AFTER UPDATE or INSERT ON eventos
  FOR EACH ROW
BEGIN
  INSERT INTO audit_table
  VALUES(:old.nombre ||' ' || :new.nombre, 'EVENTOS');
END;

--Ejercicio2:
SET serveroutput ON;
CREATE OR REPLACE TRIGGER habitantes_loc
  BEFORE UPDATE or INSERT ON localidades
  FOR EACH ROW
BEGIN
  IF :new.numerohabitantes > 4000000 or :new.numerohabitantes < 1
  THEN :new.numerohabitantes := :old.numerohabitantes;
  END IF;
END;

--Ejercicio 3:
SET serveroutput ON;
CREATE OR REPLACE TRIGGER vot_trigger
  BEFORE UPDATE or INSERT ON votantes
  FOR EACH ROW
DECLARE
  fecha DATE;
BEGIN
  SELECT SYSDATE INTO fecha FROM dual;
  IF :new.fechanacimiento > fecha
  THEN :new.fechanacimiento := fecha;
  END IF;
  INSERT INTO audit_table
  VALUES('Hubo cambios en la fecha, de ' || :old.fechanacimiento || ' a ' || :new.fechanacimiento, 'CONSULTAS');
END;

--Ejercicio 4:
ALTER TABLE votantes
ADD CONSTRAINT num_constraint CHECK(telefono >= 600000000 AND telefono <= 799999999);
 
--Ejercicio 6:
SET serveroutput ON;
CREATE OR REPLACE TRIGGER sit_laboral
  BEFORE UPDATE OR INSERT ON votantes
  FOR EACH ROW
DECLARE
  fecha DATE;
  edad NUMBER;
BEGIN
  SELECT SYSDATE INTO fecha FROM dual;
  edad := (fecha - :new.fechanacimiento) / 365;
  IF edad > 59 AND :new.situacionlaboral NOT LIKE 'Jubilado'
  THEN :new.situacionlaboral := 'Jubilado';
    INSERT INTO audit_table
    VALUES('Votante con DNI ' || :new.dni || 'tiene más de 59 años y no está jubilado.', 'VOTANTES');
  END IF;
END;