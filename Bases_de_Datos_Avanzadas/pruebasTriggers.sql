-- Ejercicio 1 --

-- Updates para comprobar funcionalidad entrega
-- Update 1
UPDATE entrega
SET fecha = TO_DATE('30-01-2050', 'DD-MM-YYYY')
WHERE idEntrega = 14;
-- Update 2
UPDATE entrega
SET fecha = TO_DATE('25-02-2030', 'DD-MM-YYYY')
WHERE idEntrega = 14;
-- Update 3
UPDATE entrega
SET fecha = TO_DATE('24-01-2023', 'DD-MM-YYYY'),
dniAgricultor = 12345679
WHERE idEntrega = 10;
-- Update 4
UPDATE entrega
SET fecha = TO_DATE('24-01-2023', 'DD-MM-YYYY'),
dniAgricultor = 78901234
WHERE idEntrega = 10;

-- Updates para comprobar funcionalidad trabajadores
-- Update 1
UPDATE trabajador
SET correo = 'pablo.aguire_new@example.com',
    telefono = 987655555
WHERE dni = 45678902;
-- Update 2
UPDATE trabajador
SET puestoTrabajo = 'Limpieza',
    direccion = 'Avenida Principal'
WHERE dni = 56789013;
-- Update 3
UPDATE trabajador
SET direccion = 'Calle Secunda 78',
    nombreCompleto = 'Óscar Sánchez Gómez'
WHERE dni = 67890124;

-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------

-- Ejercicio 2 --
-- Insert para comprobar que no se insertan datos en entrega los sabados y domingos (es importante que la fecha del sistema se encuentre en alguno de estos dos días)
insert into entrega values (16, TO_DATE('28-01-2024', 'DD-MM-YYYY'), 49.00, 7, 'Royal', 56789013);
insert into entrega values (17, TO_DATE('29-01-2025', 'DD-MM-YYYY'), 50.50, 8, 'Hojiblanca', 67890124);
-- Insert para comprobar que no se insertan datos en produccion los sabados y domingos (es importante que la fecha del sistema se encuentre en alguno de estos dos días)
insert into produccionAceite values (16, 995.00, TO_DATE('28-02-2023', 'DD-MM-YYYY'), 0.78, 'Orujo', 14, 3);
insert into produccionAceite values (17, 1025.50, TO_DATE('01-03-2023', 'DD-MM-YYYY'), 0.8, 'Virgen', 15, 2);

-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------

-- Ejercicio 3 --
-- Modificaro añadir algun trabajador/a con edad menor a 18 años
UPDATE trabajador
SET fechaNacimiento = TO_DATE('30-04-2010', 'DD-MM-YYYY')
WHERE dni = 67890124;
UPDATE trabajador
SET fechaNacimiento = TO_DATE('30-12-1980', 'DD-MM-YYYY')
WHERE dni = 67890124;
insert into trabajador values (56789045, 'Clara Navarra', TO_DATE('25-07-1940', 'DD-MM-YYYY'), 987654334, 'cla.navarro@example.com', 'Calle Almendro 31', 'Limpieza', 2);
insert into trabajador values (67890123, 'Juan Sánchez', TO_DATE('30-04-2015', 'DD-MM-YYYY'), 987654335, 'juan.sanchez@example.com', 'Avenida Cerezo 28', 'Batidora', 3);

-- Modificaro añadir algun agricultor/a con edad menor a 18 años
UPDATE agricultor
SET fechaNacimiento = TO_DATE('30-04-2009', 'DD-MM-YYYY')
WHERE dni = 56789012;
UPDATE agricultor
SET fechaNacimiento = TO_DATE('30-12-2001', 'DD-MM-YYYY')
WHERE dni = 56789012;
insert into agricultor values (45644444, 'Roberto Navarro', TO_DATE('08-08-2030', 'DD-MM-YYYY'), 987654333, 'roberto.navarro@example.com', 'Avenida Bosque 23', 'Navarro Aceitunera');
insert into agricultor values (56789044, 'Luisa Moreno', TO_DATE('14-02-1992', 'DD-MM-YYYY'), 987654334, 'luisa.moreno@example.com', 'Calle Pradera 34', 'Moreno y Aceites');

-- Si se inserta o modifica una entrega de menos de 500kg, se coloca a 500kg
insert into entrega values (16, TO_DATE('22-01-2023', 'DD-MM-YYYY'), 200.00, 7, 'Royal', 56789013);
insert into entrega values (17, TO_DATE('24-01-2023', 'DD-MM-YYYY'), 430.50, 8, 'Hojiblanca', 67890124);
UPDATE entrega
SET peso = 0
WHERE idEntrega = 9;
UPDATE entrega
SET peso = 499.99
WHERE idEntrega = 14;

-- Que no sea posible insertar agricultores con teléfono nulo
insert into agricultor values (45678111, 'Roberto Navarro', TO_DATE('08-08-1978', 'DD-MM-YYYY'), '', 'roberto.navarro@example.com', 'Avenida Bosque 23', 'Navarro Aceitunera');
insert into agricultor values (56789222, 'Luisa Moreno', TO_DATE('14-02-1992', 'DD-MM-YYYY'), 987654444, 'luisa.moreno@example.com', 'Calle Pradera 34', 'Moreno y Aceites');

-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------

-- Ejercicio 4 --
-- Inserciones para comprobar el trigger de restricción de integridad referencial entre equipoTrabajo y produccionAceite
insert into produccionAceite values (16, 1030.75, TO_DATE('26-02-2023', 'DD-MM-YYYY'), 0.81, 'Virgen', 12, 4);
insert into produccionAceite values (17, 1010.20, TO_DATE('27-02-2023', 'DD-MM-YYYY'), 0.79, 'Virgen Extra', 13, 5);
insert into produccionAceite values (18, 995.00, TO_DATE('28-02-2023', 'DD-MM-YYYY'), 0.78, 'Orujo', 14, 6);
insert into produccionAceite values (19, 1025.50, TO_DATE('01-03-2023', 'DD-MM-YYYY'), 0.8, 'Virgen', 15, 2);

-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------

-- Ejercicio 5 --
-- Insercciones de un mismo agricultor para varificar que no pueda realzar más de 3 entregas al año
-- 2024
insert into entrega values (30, TO_DATE('26-01-2024', 'DD-MM-YYYY'), 520.75, 4, 'Cornicabra', 34567891);
insert into entrega values (31, TO_DATE('27-01-2024', 'DD-MM-YYYY'), 526.75, 5, 'Picual', 34567891);
insert into entrega values (32, TO_DATE('28-01-2024', 'DD-MM-YYYY'), 820.75, 6, 'Cornicabra', 34567891);
insert into entrega values (33, TO_DATE('29-01-2024', 'DD-MM-YYYY'), 580.75, 8, 'Picual', 34567891);
-- 2025
insert into entrega values (34, TO_DATE('30-01-2025', 'DD-MM-YYYY'), 620.75, 6, 'Cornicabra', 34567891);
insert into entrega values (36, TO_DATE('26-01-2025', 'DD-MM-YYYY'), 100.75, 9, 'Cornicabra', 34567891);
insert into entrega values (37, TO_DATE('26-01-2025', 'DD-MM-YYYY'), 102.75, 9, 'Picual', 34567891);
insert into entrega values (38, TO_DATE('26-01-2025', 'DD-MM-YYYY'), 20.75, 9, 'Cornicabra', 34567891);