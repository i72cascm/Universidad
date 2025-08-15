-- Borrar tablas --
drop table trabajador;
drop table produccionAceite;
drop table entrega;
drop table agricultor;
drop table equipoTrabajo;

--------------------------------------------------------------------------------------------------------  
--------------------------------------------------------------------------------------------------------  
--------------------------------------------------------------------------------------------------------  

-- Tabla agricultor --
create table agricultor
    (dni number(8) primary key,
    nombreCompleto varchar2(64) not null,
    fechaNacimiento DATE not null,
    telefono number(14),
    correo varchar2(32),
    direccion varchar2(64) not null,
    empresa varchar2(64) not null
);

-- Tabla entrega --
create table entrega (
    idEntrega number(10) primary key,
    fecha date not null,
    peso number(10, 2) not null,
    calidad number(5),
    tipoAceituna varchar2(50) not null,
    dniAgricultor number(8),
    constraint fk_entrega_agricultor foreign key (dniAgricultor) references agricultor(dni),
    constraint ck_tipoAceituna CHECK (tipoAceituna IN ('Picual','Hojiblanca','Royal','Cornicabra')),
    constraint ck_calidad CHECK (calidad BETWEEN 0 AND 10),
    CONSTRAINT ck_peso CHECK (peso >= 500)
);

-- Tabla equipoTrabajo --
create table equipoTrabajo (
    idEquipo number(10) primary key,
    nombreEquipo varchar2(100) not null
);

-- Tabla produccionAceite --
create table produccionAceite (
    idProduccion number(10) primary key,
    litros number(10, 2) not null,
    fecha date not null,
    rendimiento number(5, 2),
    tipoAceite varchar2(50) not null,
    idEntrega number(10),
    idEquipo number(10),
    constraint fk_produccion_entrega foreign key (idEntrega) references entrega(idEntrega),
    constraint fk_produccion_equipo foreign key (idEquipo) references equipoTrabajo(idEquipo),
    constraint ck_tipoAceite CHECK (tipoAceite IN ('Virgen','Virgen Extra','Orujo'))
);

-- Tabla trabajador --
create table trabajador
    (dni number(8) primary key,
    nombreCompleto VARCHAR2(64) not null,
    fechaNacimiento DATE not null,
    telefono number(14),
    correo varchar2(32),
    direccion varchar2(64) not null,
    puestoTrabajo varchar2(64) not null,
    idEquipoTrabajo number(10),
    constraint fk_trabajador_equipo foreign key (idEquipoTrabajo) references equipoTrabajo(idEquipo),
    constraint ck_puesto CHECK (puestoTrabajo IN ('Recepción','Limpieza','Batidora','Almacenamiento'))
);
    
--------------------------------------------------------------------------------------------------------    
--------------------------------------------------------------------------------------------------------  
--------------------------------------------------------------------------------------------------------  
    
-- Valores agricultor --
insert into agricultor values (12345678, 'Juan Pérez', TO_DATE('01-01-2001', 'DD-MM-YYYY'), 987654321, 'juan.perez@example.com', 'Calle Falsa 123', 'Aceitunas Pérez S.L.');
insert into agricultor values (23456789, 'Ana Gómez', TO_DATE('15-03-2002', 'DD-MM-YYYY'), 987654322, 'ana.gomez@example.com', 'Avenida Olivos 45', 'Olivos Gómez S.A.');
insert into agricultor values (34567890, 'Carlos López', TO_DATE('23-05-1980', 'DD-MM-YYYY'), 987654323, 'carlos.lopez@example.com', 'Plaza del Aceite 9', 'López y Aceites');
insert into agricultor values (45678901, 'Laura Martínez', TO_DATE('07-07-1995', 'DD-MM-YYYY'), 987654324, 'laura.martinez@example.com', 'Calle Nueva 67', 'Martínez Olivar');
insert into agricultor values (56789012, 'Miguel Ángel Ruiz', TO_DATE('12-12-1985', 'DD-MM-YYYY'), 987654325, 'miguel.ruiz@example.com', 'Calle Vieja 21', 'Ruiz e Hijos');
insert into agricultor values (67890123, 'Sara Jiménez', TO_DATE('30-11-1990', 'DD-MM-YYYY'), 987654326, 'sara.jimenez@example.com', 'Calle de la Paz 11', 'Jiménez Oliva');
insert into agricultor values (78901234, 'David Fernández', TO_DATE('09-09-1988', 'DD-MM-YYYY'), 987654327, 'david.fernandez@example.com', 'Avenida del Mar 3', 'Fernández y Compañía');
insert into agricultor values (89012345, 'Marta García', TO_DATE('16-06-2003', 'DD-MM-YYYY'), 987654328, 'marta.garcia@example.com', 'Calle Sol 8', 'García Aceitunas');
insert into agricultor values (90123456, 'Antonio Molina', TO_DATE('21-02-1975', 'DD-MM-YYYY'), 987654329, 'antonio.molina@example.com', 'Avenida Luna 12', 'Molina Olivos S.L.');
insert into agricultor values (12345679, 'Patricia Sánchez', TO_DATE('05-10-1999', 'DD-MM-YYYY'), 987654330, 'patricia.sanchez@example.com', 'Calle Estrella 44', 'Olivares Sánchez');
insert into agricultor values (23456780, 'Jorge Ortiz', TO_DATE('17-04-1982', 'DD-MM-YYYY'), 987654331, 'jorge.ortiz@example.com', 'Calle Jardín 56', 'Ortiz Aceites');
insert into agricultor values (34567891, 'Susana Prado', TO_DATE('29-01-2001', 'DD-MM-YYYY'), 987654332, 'susana.prado@example.com', 'Calle Rosales 78', 'Prado y Olivos');
insert into agricultor values (45678902, 'Roberto Navarro', TO_DATE('08-08-1978', 'DD-MM-YYYY'), 987654333, 'roberto.navarro@example.com', 'Avenida Bosque 23', 'Navarro Aceitunera');
insert into agricultor values (56789013, 'Luisa Moreno', TO_DATE('14-02-1992', 'DD-MM-YYYY'), 987654334, 'luisa.moreno@example.com', 'Calle Pradera 34', 'Moreno y Aceites');
insert into agricultor values (67890124, 'Manuel Casas', TO_DATE('22-11-1986', 'DD-MM-YYYY'), 987654335, 'manuel.casas@example.com', 'Calle del Lago 89', 'Casas Olivar');

-- Valores entrega --
insert into entrega values (1, TO_DATE('15-01-2023', 'DD-MM-YYYY'), 500.50, 8, 'Picual', 12345678);
insert into entrega values (2, TO_DATE('16-01-2023', 'DD-MM-YYYY'), 550.00, 7, 'Hojiblanca', 23456789);
insert into entrega values (3, TO_DATE('17-01-2023', 'DD-MM-YYYY'), 600.75, 9, 'Cornicabra', 34567890);
insert into entrega values (4, TO_DATE('18-01-2023', 'DD-MM-YYYY'), 530.20, 6, 'Royal', 45678901);
insert into entrega values (5, TO_DATE('19-01-2023', 'DD-MM-YYYY'), 770.00, 7, 'Hojiblanca', 56789012);
insert into entrega values (6, TO_DATE('20-01-2023', 'DD-MM-YYYY'), 560.50, 8, 'Royal', 67890123);
insert into entrega values (7, TO_DATE('21-01-2023', 'DD-MM-YYYY'), 890.30, 5, 'Picual', 78901234);
insert into entrega values (8, TO_DATE('22-01-2023', 'DD-MM-YYYY'), 510.00, 7, 'Cornicabra', 89012345);
insert into entrega values (9, TO_DATE('23-01-2023', 'DD-MM-YYYY'), 550.25, 8, 'Picual', 90123456);
insert into entrega values (10, TO_DATE('24-01-2023', 'DD-MM-YYYY'), 500.00, 6, 'Royal', 12345679);
insert into entrega values (11, TO_DATE('25-01-2023', 'DD-MM-YYYY'), 680.50, 7, 'Hojiblanca', 23456780);
insert into entrega values (12, TO_DATE('26-01-2023', 'DD-MM-YYYY'), 520.75, 9, 'Cornicabra', 34567891);
insert into entrega values (13, TO_DATE('27-01-2023', 'DD-MM-YYYY'), 505.20, 6, 'Picual', 45678902);
insert into entrega values (14, TO_DATE('28-01-2023', 'DD-MM-YYYY'), 1095.00, 7, 'Royal', 56789013);
insert into entrega values (15, TO_DATE('29-01-2023', 'DD-MM-YYYY'), 530.50, 8, 'Hojiblanca', 67890124);

-- Valores equipoTrabajo --
insert into equipoTrabajo values (1, 'Equipo Alfa');
insert into equipoTrabajo values (2, 'Equipo Bravo');
insert into equipoTrabajo values (3, 'Equipo Charlie');

-- Valores produccionAceite --
insert into produccionAceite values (1, 1000.00, TO_DATE('15-02-2023', 'DD-MM-YYYY'), 0.8, 'Virgen Extra', 1, 1);
insert into produccionAceite values (2, 950.50, TO_DATE('16-02-2023', 'DD-MM-YYYY'), 0.75, 'Virgen', 2, 2);
insert into produccionAceite values (3, 1100.75, TO_DATE('17-02-2023', 'DD-MM-YYYY'), 0.82, 'Orujo', 3, 3);
insert into produccionAceite values (4, 1050.25, TO_DATE('18-02-2023', 'DD-MM-YYYY'), 0.78, 'Virgen Extra', 4, 2);
insert into produccionAceite values (5, 900.00, TO_DATE('19-02-2023', 'DD-MM-YYYY'), 0.7, 'Orujo', 5, 3);
insert into produccionAceite values (6, 950.50, TO_DATE('20-02-2023', 'DD-MM-YYYY'), 0.75, 'Virgen', 6, 1);
insert into produccionAceite values (7, 1000.30, TO_DATE('21-02-2023', 'DD-MM-YYYY'), 0.8, 'Virgen Extra', 7, 2);
insert into produccionAceite values (8, 980.00, TO_DATE('22-02-2023', 'DD-MM-YYYY'), 0.77, 'Orujo', 8, 2);
insert into produccionAceite values (9, 1020.25, TO_DATE('23-02-2023', 'DD-MM-YYYY'), 0.79, 'Virgen', 9, 3);
insert into produccionAceite values (10, 1000.00, TO_DATE('24-02-2023', 'DD-MM-YYYY'), 0.8, 'Virgen Extra', 10, 3);
insert into produccionAceite values (11, 970.50, TO_DATE('25-02-2023', 'DD-MM-YYYY'), 0.76, 'Orujo', 11, 1);
insert into produccionAceite values (12, 1030.75, TO_DATE('26-02-2023', 'DD-MM-YYYY'), 0.81, 'Virgen', 12, 2);
insert into produccionAceite values (13, 1010.20, TO_DATE('27-02-2023', 'DD-MM-YYYY'), 0.79, 'Virgen Extra', 13, 1);
insert into produccionAceite values (14, 995.00, TO_DATE('28-02-2023', 'DD-MM-YYYY'), 0.78, 'Orujo', 14, 3);
insert into produccionAceite values (15, 1025.50, TO_DATE('01-03-2023', 'DD-MM-YYYY'), 0.8, 'Virgen', 15, 2);

-- Valores trabajadores --
-- Equipo 1
insert into trabajador values (12345678, 'Carlos González', TO_DATE('02-03-1985', 'DD-MM-YYYY'), 987654321, 'carlos.gonzalez@example.com', 'Calle Roble 3', 'Recepción', 1);
insert into trabajador values (23456789, 'Marta Fernández', TO_DATE('15-05-1980', 'DD-MM-YYYY'), 987654322, 'marta.fernandez@example.com', 'Avenida Pinos 8', 'Limpieza', 1);
insert into trabajador values (34567890, 'Luis Ramírez', TO_DATE('23-07-1975', 'DD-MM-YYYY'), 987654323, 'luis.ramirez@example.com', 'Calle Olivo 15', 'Batidora', 1);
insert into trabajador values (45678901, 'Sofía Morales', TO_DATE('08-11-1982', 'DD-MM-YYYY'), 987654324, 'sofia.morales@example.com', 'Plaza Central 22', 'Almacenamiento', 1);

-- Equipo 2
insert into trabajador values (56789012, 'David Jiménez', TO_DATE('04-02-1988', 'DD-MM-YYYY'), 987654325, 'david.jimenez@example.com', 'Calle Cedro 9', 'Recepción', 2);
insert into trabajador values (67890123, 'Ana López', TO_DATE('19-04-2001', 'DD-MM-YYYY'), 987654326, 'ana.lopez@example.com', 'Avenida Granada 33', 'Limpieza', 2);
insert into trabajador values (78901234, 'Manuel Torres', TO_DATE('07-09-1978', 'DD-MM-YYYY'), 987654327, 'manuel.torres@example.com', 'Calle Naranjo 27', 'Batidora', 2);
insert into trabajador values (89012345, 'Carmen Ruiz', TO_DATE('12-12-1990', 'DD-MM-YYYY'), 987654328, 'carmen.ruiz@example.com', 'Calle Sauce 12', 'Almacenamiento', 2);

-- Equipo 3
insert into trabajador values (90123456, 'Jorge Martín', TO_DATE('26-01-1980', 'DD-MM-YYYY'), 987654329, 'jorge.martin@example.com', 'Avenida Castaño 45', 'Recepción', 3);
insert into trabajador values (12345679, 'Sara Gutiérrez', TO_DATE('09-03-1985', 'DD-MM-YYYY'), 987654330, 'sara.gutierrez@example.com', 'Plaza Roble 18', 'Limpieza', 3);
insert into trabajador values (23456780, 'Antonio Serrano', TO_DATE('22-06-1975', 'DD-MM-YYYY'), 987654331, 'antonio.serrano@example.com', 'Calle Peral 21', 'Batidora', 3);
insert into trabajador values (34567891, 'Laura Vidal', TO_DATE('14-08-1984', 'DD-MM-YYYY'), 987654332, 'laura.vidal@example.com', 'Avenida Manzano 19', 'Almacenamiento', 3);

-- Trabajadores adicionales
insert into trabajador values (45678902, 'Pablo Aguirre', TO_DATE('17-10-1982', 'DD-MM-YYYY'), 987654333, 'pablo.aguirre@example.com', 'Calle Limonero 23', 'Recepción', 1);
insert into trabajador values (56789013, 'Clara Navarro', TO_DATE('25-07-1989', 'DD-MM-YYYY'), 987654334, 'clara.navarro@example.com', 'Calle Almendro 31', 'Limpieza', 2);
insert into trabajador values (67890124, 'Óscar Sánchez', TO_DATE('30-04-2000', 'DD-MM-YYYY'), 987654335, 'oscar.sanchez@example.com', 'Avenida Cerezo 28', 'Batidora', 3);
