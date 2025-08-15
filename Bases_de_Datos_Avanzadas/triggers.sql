-- Sentencia para habilitar salidas en la consola --
set serveroutput on;

-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------

-- Ejercicio 1 --

-- Trigger que notifica cuando en la tabla entrega se han modificado los atributos fecha o dniAgricultor de alguna tupla
CREATE OR REPLACE TRIGGER auditoria_entrega
AFTER UPDATE OF fecha, dniAgricultor ON entrega
FOR EACH ROW
BEGIN
    IF :NEW.fecha != :OLD.fecha OR :NEW.dniAgricultor != :OLD.dniAgricultor THEN
        DBMS_OUTPUT.PUT_LINE('Se ha modificado la entrega con ID ' || :OLD.idEntrega || 
                             '. Cambios: Fecha de ' || :OLD.fecha || ' a ' || :NEW.fecha ||
                             ', DNI Agricultor de ' || :OLD.dniAgricultor || ' a ' || :NEW.dniAgricultor);
    END IF;
END;
/

-- Triger que notifica si ha sido modificado cualquier valor de la tabla trabajador
CREATE OR REPLACE TRIGGER auditoria_trabajador
AFTER UPDATE ON trabajador
FOR EACH ROW
BEGIN
    DBMS_OUTPUT.PUT_LINE('El trabajador con DNI ' || :OLD.dni || ' ha sido actualizado con éxito.');
END;
/

-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------

-- Ejercicio 2 --

-- Trigger que impide insertar datos en la tabla de entregas en sábados y domingos
CREATE OR REPLACE TRIGGER fechas_laborales_entrega
BEFORE INSERT ON entrega
BEGIN
    IF(TO_CHAR(SYSDATE, 'DY') IN ('SÁB', 'DOM'))
        THEN RAISE_APPLICATION_ERROR(-20500, 'ERROR: No se encuentra en un día laboral.');
    END IF;
END;
/

-- Trigger que impide insertar datos en la tabla de produccion en sábados y domingos
CREATE OR REPLACE TRIGGER fechas_laborales_produccion
BEFORE INSERT ON produccionaceite
BEGIN
    IF(TO_CHAR(SYSDATE, 'DY') IN ('SÁB', 'DOM'))
        THEN RAISE_APPLICATION_ERROR(-20500, 'ERROR: No se encuentra en un día laboral.');
    END IF;
END;
/

-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------

-- Ejercicio 3 --

-- Trigger para comprobar que el trabajador/a es mayor de edad
CREATE OR REPLACE TRIGGER trabajadores_mayor_edad
BEFORE INSERT OR UPDATE ON trabajador
FOR EACH ROW
BEGIN
    IF :NEW.fechaNacimiento >  add_months(sysdate , -12*18)  then
       RAISE_APPLICATION_ERROR(-20001, 'El trabajador/a no puede ser menor de edad.');
    END IF;
END;
/

-- Trigger para comprobar que el agricultor/a es mayor de edad
CREATE OR REPLACE TRIGGER agricultores_mayor_edad
BEFORE INSERT OR UPDATE ON agricultor
FOR EACH ROW
BEGIN
    IF :NEW.fechaNacimiento >  add_months(sysdate , -12*18)  then
       RAISE_APPLICATION_ERROR(-20001, 'El agricultor/a no puede ser menor de edad.');
    END IF;
END;
/

-- Trigger para hacer que el peso mínimo de entrega sea de 500kg mínimo
CREATE OR REPLACE TRIGGER cambiar_peso_entrega
BEFORE INSERT OR UPDATE ON entrega
FOR EACH ROW
BEGIN
    IF :NEW.peso < 500 THEN
        :NEW.peso := 500;
    END IF;
END;
/

-- Trigger para hacer que el campo teléfono en agricultor no pueda ser nulo
CREATE OR REPLACE TRIGGER telefono_agricultor_not_null
BEFORE INSERT OR UPDATE ON agricultor
FOR EACH ROW
BEGIN
    IF :NEW.telefono IS null THEN
        RAISE_APPLICATION_ERROR(-20001, 'El campo teléfono no puede ser nulo.');
    END IF;
END;
/

-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------

-- Ejercicio 4 --

-- En primer lugar es necesario eliminar de clave foránea
ALTER TABLE produccionaceite drop CONSTRAINT fk_produccion_equipo;
/

-- Trigger que sustituye la restricción de integridad referencial entre las tablas equipoTrabajo y produccionAceite
CREATE OR REPLACE TRIGGER relacion_equipo_produccion
BEFORE INSERT OR UPDATE ON produccionaceite
FOR EACH ROW
DECLARE
    i number;
BEGIN
    SELECT count(*)
    INTO i
    FROM equipotrabajo
    WHERE idequipo = :NEW.idequipo;
    IF i = 0 THEN
        RAISE_APPLICATION_ERROR(-20001, 'Equipo de Trabajo inexistente.');
    END IF;
END;
/

-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------

-- Ejercicio 5 --

-- Trigger para que un agricultor no pueda realizar más de 3 entregas el mismo año
CREATE OR REPLACE TRIGGER limitar_entregas_agricultor
BEFORE INSERT ON entrega
FOR EACH ROW
DECLARE
    i number;
BEGIN
    SELECT count(*)
    INTO i
    FROM entrega
    WHERE dniagricultor = :NEW.dniagricultor AND (extract(year FROM fecha) = extract(year FROM :NEW.fecha));
    IF i >= 3 THEN
        RAISE_APPLICATION_ERROR(-20001, 'Un agricultor no puede realizar más de 3 entregas el mismo año.');
    END IF;
END;
/

-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------

-- Deshabilitar triggers --
ALTER TRIGGER auditoria_entrega DISABLE;
ALTER TRIGGER auditoria_trabajador DISABLE;
ALTER TRIGGER fechas_laborales_entrega DISABLE;
ALTER TRIGGER fechas_laborales_produccion DISABLE;
ALTER TRIGGER trabajadores_mayor_edad DISABLE;
ALTER TRIGGER agricultores_mayor_edad DISABLE;
ALTER TRIGGER cambiar_peso_entrega DISABLE;
ALTER TRIGGER telefono_agricultor_not_null DISABLE;
ALTER TRIGGER relacion_equipo_produccion DISABLE;
ALTER TRIGGER limitar_entregas_agricultor DISABLE;

-- Habilitar triggers --
ALTER TRIGGER auditoria_entrega ENABLE;
ALTER TRIGGER auditoria_trabajador ENABLE;
ALTER TRIGGER fechas_laborales_entrega ENABLE;
ALTER TRIGGER fechas_laborales_produccion ENABLE;
ALTER TRIGGER trabajadores_mayor_edad ENABLE;
ALTER TRIGGER agricultores_mayor_edad ENABLE;
ALTER TRIGGER cambiar_peso_entrega ENABLE;
ALTER TRIGGER telefono_agricultor_not_null ENABLE;
ALTER TRIGGER relacion_equipo_produccion ENABLE;
ALTER TRIGGER limitar_entregas_agricultor ENABLE;