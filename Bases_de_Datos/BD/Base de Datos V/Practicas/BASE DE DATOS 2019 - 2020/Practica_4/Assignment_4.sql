--Ejercicio 1:
SET serveroutput ON;
DECLARE
  fecha DATE;
BEGIN
  SELECT SYSDATE INTO fecha FROM dual;
  dbms_output.put_line('Hola mundo, es ' || fecha);
END;

--Ejercicio 2:
SET serveroutput ON;
DECLARE
  apellido votantes.nombrecompleto%type;
  mydni votantes.dni%type;
BEGIN
  SELECT SUBSTR(votantes.nombrecompleto, instr(votantes.nombrecompleto, ' '), instr(substr(votantes.nombrecompleto, instr(votantes.nombrecompleto, ' ')+1), ' ')) INTO apellido 
  FROM votantes 
  WHERE votantes.fechanacimiento = (SELECT MIN(votantes.fechanacimiento) FROM votantes);
  SELECT votantes.dni INTO mydni
  FROM votantes
  WHERE votantes.fechanacimiento = (SELECT MIN(votantes.fechanacimiento) FROM votantes);
  dbms_output.put_line(apellido || ', con DNI ' || mydni || ' es el/la votante con más años.');
END;

--Ejercicio 3:
SET serveroutput ON;
DECLARE
  v_nombre votantes.nombrecompleto%type;
  v_email votantes.email%type;
  mydni NUMBER := 30983712;
BEGIN
  SELECT votantes.nombrecompleto INTO v_nombre FROM votantes WHERE votantes.dni = mydni;
  SELECT votantes.email INTO v_email FROM votantes WHERE votantes.dni = mydni;
  dbms_output.put_line(v_nombre || ' con correo: ' || v_email);
END;

--Ejercicio 4:
SET serveroutput ON;
DECLARE
  v_nombre votantes.nombrecompleto%type;
  v_dni votantes.dni%type;
  mydni NUMBER := 30983712;
BEGIN
  SELECT SUBSTR(votantes.nombrecompleto, 6, 11) INTO v_nombre FROM votantes WHERE votantes.dni = mydni;
  dbms_output.put_line('Pepe ' || v_nombre);
END;

--Ejercicio 5:  NOTA: ROUND(<número>) para redondear.
SET serveroutput ON;
DECLARE
  v_fecha_maxima votantes.fechanacimiento%type;
  v_fecha_minima votantes.fechanacimiento%type;
BEGIN
  SELECT MAX(votantes.fechanacimiento) INTO v_fecha_maxima FROM votantes;
  SELECT MIN(votantes.fechanacimiento) INTO v_fecha_minima FROM votantes;
  dbms_output.put_line(v_fecha_minima);
  dbms_output.put_line(v_fecha_maxima);
  dbms_output.put_line(ROUND((v_fecha_maxima - v_fecha_minima) / 365));
END;

--Ejercicio 6:
SET serveroutput ON;
DECLARE
  CURSOR c IS SELECT partidos.nombrecompleto, consultas_datos.certidumbre, consultas_datos.respuesta FROM partidos, consultas_datos WHERE partidos.idpartido = consultas_datos.partido ORDER BY consultas_datos.certidumbre DESC;
  sumatorio NUMBER := 0;
  contador NUMBER := 0;
  media_certidumbre NUMBER;
  c_certidumbre consultas_datos.certidumbre%type;
BEGIN
  FOR num_row IN c
    LOOP
      sumatorio := num_row.certidumbre + sumatorio;
      contador := contador + 1;
    END LOOP;
    media_certidumbre := sumatorio / contador;
    dbms_output.put_line('La media de la certidumbre es: ' || ROUND(media_certidumbre, 3));
  FOR num_row IN c
    LOOP
      IF num_row.certidumbre > media_certidumbre AND num_row.respuesta LIKE 'Si' THEN c_certidumbre := num_row.certidumbre;
      END IF;
      dbms_output.put_line(num_row.nombrecompleto || ' ' || c_certidumbre);
    END LOOP;
END;