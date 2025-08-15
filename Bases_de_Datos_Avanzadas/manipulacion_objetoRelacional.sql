-- Script de manipulación de datos del modelo Objero-Relacional --

-- ALTA DE DATOS -- 
-- Agricultores --
INSERT INTO agricultor VALUES (
    12345678, 
    'Juan Pérez', 
    TO_DATE('1980-01-15', 'YYYY-MM-DD'), 
    987654321, 
    lista_correo_t('juan.perez@example.com', 'perez.juan@example.com'),
    direccion_t('Cordoba', 'Calle 1', 123, 100), 
    'Aceitunas Pérez S.L.'
);

INSERT INTO agricultor VALUES (
    12345738, 
    'Luis Pepe', 
    TO_DATE('2000-01-15', 'YYYY-MM-DD'), 
    987654321, 
    lista_correo_t('luis.pepe@example.com', 'pepe.luis@example.com'),
    direccion_t('Sevilla', 'Costa', 123, 1030), 
    'Olivos Pepe S.A.'
);

INSERT INTO agricultor VALUES (
    23456789, 
    'Ana Gómez', 
    TO_DATE('1975-05-22', 'YYYY-MM-DD'), 
    987654322, 
    lista_correo_t('ana.gomez@example.com', 'gomez.ana@example.com'),
    direccion_t('Granada', 'Avenida 2', 45, 1050), 
    'Gómez Agricultura'
);

INSERT INTO agricultor VALUES (
    34567890, 
    'Carlos Martín', 
    TO_DATE('1988-08-30', 'YYYY-MM-DD'), 
    987654333, 
    lista_correo_t('carlos.martin@example.com', 'martin.carlos@example.com'),
    direccion_t('Malaga', 'Plaza 3', 78, 1015), 
    'Martín Olivareros'
);

INSERT INTO agricultor VALUES (
    45678901, 
    'Sara López', 
    TO_DATE('1990-12-12', 'YYYY-MM-DD'), 
    987654334, 
    lista_correo_t('sara.lopez@example.com', 'lopez.sara@example.com'),
    direccion_t('Jaen', 'Calle Olivo', 90, 1022), 
    'López Aceitunas S.L.'
);

-- Entregas --
INSERT INTO entrega VALUES (
    1001, 
    TO_DATE('2023-01-10', 'YYYY-MM-DD'), 
    1200, 
    8, 
    'Picual',
    (SELECT REF(a) FROM agricultor a WHERE a.dni = 12345678)
);

INSERT INTO entrega VALUES (
    1002, 
    TO_DATE('2023-02-15', 'YYYY-MM-DD'), 
    950, 
    7, 
    'Hojiblanca',
    (SELECT REF(a) FROM agricultor a WHERE a.dni = 12345738)
);

INSERT INTO entrega VALUES (
    1003, 
    TO_DATE('2023-03-20', 'YYYY-MM-DD'), 
    1100, 
    9, 
    'Royal',
    (SELECT REF(a) FROM agricultor a WHERE a.dni = 23456789)
);

INSERT INTO entrega VALUES (
    1004, 
    TO_DATE('2023-04-25', 'YYYY-MM-DD'), 
    1050, 
    6, 
    'Cornicabra',
    (SELECT REF(a) FROM agricultor a WHERE a.dni = 34567890)
);

INSERT INTO entrega VALUES (
    1005, 
    TO_DATE('2023-05-30', 'YYYY-MM-DD'), 
    1250, 
    8, 
    'Picual',
    (SELECT REF(a) FROM agricultor a WHERE a.dni = 45678901)
);

-- Equipo Trabajo --
INSERT INTO equipoTrabajo (idEquipo, nombreEquipo) VALUES (
    1, 
    'Equipo Alfa'
);

INSERT INTO equipoTrabajo (idEquipo, nombreEquipo) VALUES (
    2, 
    'Equipo Bravo'
);

-- Produccion Aceite --
INSERT INTO produccionAceite VALUES (
    1, 
    500.00, 
    TO_DATE('2023-06-01', 'YYYY-MM-DD'), 
    0.80, 
    'Virgen Extra', 
    (SELECT REF(e) FROM entrega e WHERE e.idEntrega = 1001),
    (SELECT REF(et) FROM equipoTrabajo et WHERE et.idEquipo = 1)
);

INSERT INTO produccionAceite VALUES (
    2, 
    600.00, 
    TO_DATE('2023-06-02', 'YYYY-MM-DD'), 
    0.85, 
    'Virgen', 
    (SELECT REF(e) FROM entrega e WHERE e.idEntrega = 1002),
    (SELECT REF(et) FROM equipoTrabajo et WHERE et.idEquipo = 1)
);

INSERT INTO produccionAceite VALUES (
    3, 
    700.00, 
    TO_DATE('2023-06-03', 'YYYY-MM-DD'), 
    0.75, 
    'Orujo', 
    (SELECT REF(e) FROM entrega e WHERE e.idEntrega = 1003),
    (SELECT REF(et) FROM equipoTrabajo et WHERE et.idEquipo = 2)
);

INSERT INTO produccionAceite VALUES (
    4, 
    800.00, 
    TO_DATE('2023-06-04', 'YYYY-MM-DD'), 
    0.77, 
    'Virgen Extra', 
    (SELECT REF(e) FROM entrega e WHERE e.idEntrega = 1004),
    (SELECT REF(et) FROM equipoTrabajo et WHERE et.idEquipo = 2)
);

INSERT INTO produccionAceite VALUES (
    5, 
    900.00, 
    TO_DATE('2023-06-05', 'YYYY-MM-DD'), 
    0.78, 
    'Virgen', 
    (SELECT REF(e) FROM entrega e WHERE e.idEntrega = 1005),
    (SELECT REF(et) FROM equipoTrabajo et WHERE et.idEquipo = 1)
);


-- Trabajador --
INSERT INTO trabajador VALUES (
    87654321, 
    'Pedro García', 
    TO_DATE('1985-02-15', 'YYYY-MM-DD'), 
    987654345, 
    lista_correo_t('pedro.garcia@example.com'), 
    direccion_t('Sevilla', 'Calle 4', 124, 2001), 
    'Recepción', 
    (SELECT REF(e) FROM equipoTrabajo e WHERE e.idEquipo = 1)
);

INSERT INTO trabajador VALUES (
    87654322, 
    'María Rodríguez', 
    TO_DATE('1990-03-20', 'YYYY-MM-DD'), 
    987654346, 
    lista_correo_t('maria.rodriguez@example.com'), 
    direccion_t('Córdoba', 'Avenida 5', 50, 2002), 
    'Limpieza', 
    (SELECT REF(e) FROM equipoTrabajo e WHERE e.idEquipo = 2)
);

INSERT INTO trabajador VALUES (
    87654323, 
    'José López', 
    TO_DATE('1988-04-25', 'YYYY-MM-DD'), 
    987654347, 
    lista_correo_t('jose.lopez@example.com'), 
    direccion_t('Granada', 'Plaza 6', 79, 2003), 
    'Batidora', 
    (SELECT REF(e) FROM equipoTrabajo e WHERE e.idEquipo = 1)
);

INSERT INTO trabajador VALUES (
    87654324, 
    'Ana Torres', 
    TO_DATE('1992-05-30', 'YYYY-MM-DD'), 
    987654348, 
    lista_correo_t('ana.torres@example.com'), 
    direccion_t('Málaga', 'Calle Olivo', 91, 2004), 
    'Almacenamiento', 
    (SELECT REF(e) FROM equipoTrabajo e WHERE e.idEquipo = 1)
);

INSERT INTO trabajador VALUES (
    87654325, 
    'Carlos Sánchez', 
    TO_DATE('1995-06-05', 'YYYY-MM-DD'), 
    987654349, 
    lista_correo_t('carlos.sanchez@example.com'), 
    direccion_t('Jaén', 'Calle 7', 92, 2005), 
    'Recepción', 
    (SELECT REF(e) FROM equipoTrabajo e WHERE e.idEquipo = 2)
);



-- MODIFICAR DATOS --
-- Agricultor --
UPDATE agricultor
SET 
    nombreCompleto = 'Luis Luis',
    empresa = 'Olivos Luis'
WHERE dni = 12345678;

-- Entrega --
UPDATE entrega
SET peso = 2000
WHERE idEntrega = 1003;

-- Equipo Trabajo --
UPDATE equipoTrabajo
SET 
    idEquipo = 3,
    nombreEquipo = 'Equipo Charlie'
WHERE idEquipo = 2;

-- Producion aceite --
UPDATE produccionAceite
SET 
    litros = 700,
    rf_equipoTrabajo = (SELECT REF(et) FROM equipoTrabajo et WHERE et.idEquipo = 1)
WHERE idProduccion = 4;

-- Trabajador --
UPDATE trabajador
SET 
    direccion = direccion_t('Cordoba', 'Calle Juderia', 45, 14005)
WHERE dni = 87654321;


-- Usar función miembro --
SELECT p.idProduccion, p.litros, p.clasificarProduccion() AS Clasificacion
FROM produccionAceite p;

-- CONSULTAR DATOS --
SELECT * FROM agricultor;
SELECT * FROM entrega;
SELECT * FROM equipoTrabajo;
SELECT * FROM produccionAceite;
SELECT * FROM trabajador;



-- BORRAR DATOS --
-- Agricultor --
DELETE FROM agricultor
WHERE dni = 23456789;
-- Entrega --
DELETE FROM entrega
WHERE idEntrega = 1004;
-- Equipo trabajo --
DELETE FROM equipoTrabajo
WHERE idEquipo = 1;
-- Produccion aceite --
DELETE FROM produccionAceite
WHERE idProduccion = 4;
-- Trabajador --
DELETE FROM trabajador
WHERE dni = 87654323;