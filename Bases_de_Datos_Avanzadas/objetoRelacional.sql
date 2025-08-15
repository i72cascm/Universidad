DROP TABLE agricultor;
DROP TABLE entrega;
DROP TABLE equipoTrabajo;
DROP TABLE produccionAceite;
DROP TABLE trabajador;
DROP TYPE entregasList force;
DROP TYPE trabajador_t;
DROP TYPE produccionAceite_t;
DROP TYPE entrega_t;
DROP TYPE agricultor_t;
DROP TYPE equipoTrabajo_t;
DROP TYPE direccion_t;
DROP TYPE lista_correo_t;


-- Ejercicio 1 --
CREATE TYPE direccion_t AS OBJECT(
    ciudad varchar2(64),
    calle varchar2(64),
    numero number(20),
    codigoPostal number(20)
);
/
-----------------

-- Ejercicio 3 
CREATE TYPE lista_correo_t AS VARRAY(10) OF VARCHAR2(64);
/
-----------------

-- Creación de la base de datos de Almazara en modelo objeto-relacional --
CREATE TYPE agricultor_t AS OBJECT (
    dni number(8),
    nombreCompleto varchar2(64),
    fechaNacimiento date,
    telefono number(14),
    correo lista_correo_t,
    direccion direccion_t,
    empresa varchar2(64)
);
/

CREATE TABLE agricultor OF agricultor_t(
    dni primary key,
    nombreCompleto CONSTRAINT nn_agricultor_nombreCompleto NOT NULL,
    fechaNacimiento CONSTRAINT nn_agricultor_fechaNacimiento NOT NULL,
    empresa CONSTRAINT nn_agricultor_empresa NOT NULL
);
/

CREATE TYPE entrega_t AS OBJECT (
    idEntrega number(10),
    fecha date,
    peso number(10, 2),
    calidad number(5),
    tipoAceituna varchar2(50),
    rf_agricultor REF agricultor_t
);
/

CREATE TABLE entrega OF entrega_t(
    idEntrega primary key,
    fecha CONSTRAINT nn_entrega_fecha NOT NULL,
    peso CONSTRAINT ck_entrega_peso CHECK (peso >= 500) NOT NULL,
    calidad CONSTRAINT ck_entrega_calidad CHECK (calidad BETWEEN 0 AND 10),
    tipoAceituna CONSTRAINT ck_entrega_tipoAceituna CHECK (tipoAceituna IN ('Picual', 'Hojiblanca', 'Royal', 'Cornicabra')) NOT NULL,
    rf_agricultor SCOPE IS agricultor
);
/

-- Ejercicio 2 --
CREATE TYPE entregasList AS TABLE OF REF entrega_t;
/

CREATE TYPE equipoTrabajo_t AS OBJECT(
    idEquipo number(10),
    nombreEquipo varchar2(100),
    entregas EntregasList
);
/

CREATE TABLE equipoTrabajo OF equipoTrabajo_t (
    idEquipo PRIMARY KEY,
    nombreEquipo CONSTRAINT nn_equipoTrabajo_nombreEquipo NOT NULL
) NESTED TABLE entregas STORE AS nestedEntregas 
/
-----------------

-- Ejercicio 4 --

CREATE TYPE produccionAceite_t AS OBJECT (
    idProduccion number(10),
    litros number(10, 2),
    fecha date,
    rendimiento number(5, 2),
    tipoAceite varchar2(50),
    rf_entrega REF entrega_t,
    rf_equipoTrabajo REF equipoTrabajo_t,
    MEMBER FUNCTION clasificarProduccion return varchar2
);
/

CREATE OR REPLACE TYPE BODY produccionAceite_t AS 
    MEMBER FUNCTION clasificarProduccion return varchar2 IS
    BEGIN
        IF litros < 600 THEN
            return 'Pequeña';
        ELSIF litros between 600 and 700 then
            return 'Mediana';
        ELSE
            return 'Grande';
        END IF;
    END;
END;
/

CREATE TABLE produccionAceite OF produccionAceite_t (
    idProduccion primary key,
    litros CONSTRAINT nn_produccionAceite_litros NOT NULL,
    fecha CONSTRAINT nn_produccionAceite_fecha NOT NULL,
    tipoAceite CONSTRAINT ck_produccionAceite_tipoAceite CHECK (tipoAceite IN ('Virgen', 'Virgen Extra', 'Orujo')) NOT NULL,
    rf_entrega SCOPE IS entrega,
    rf_equipoTrabajo SCOPE IS equipoTrabajo
);
/

-----------------

CREATE TYPE trabajador_t AS OBJECT (
    dni number(8),
    nombreCompleto VARCHAR2(64),
    fechaNacimiento DATE,
    telefono number(14),
    correo lista_correo_t,
    direccion direccion_t,
    puestoTrabajo varchar2(64),
    rf_equipoTrabajo REF equipoTrabajo_t
);
/

CREATE TABLE trabajador OF trabajador_t (
    dni primary key,
    nombreCompleto CONSTRAINT nn_trabajador_nombreCompleto NOT NULL,
    fechaNacimiento CONSTRAINT nn_trabajador_fechaNacimiento NOT NULL,
    puestoTrabajo CONSTRAINT ck_trabajador_puestoTrabajo CHECK (puestoTrabajo IN ('Recepción', 'Limpieza', 'Batidora', 'Almacenamiento')) NOT NULL,
    rf_equipoTrabajo SCOPE IS equipoTrabajo
);