--Ejercicio 1:
SET serveroutput ON;
DECLARE
  CURSOR c IS SELECT partidos.presidente FROM partidos;
  p_presidente partidos.presidente%type;
BEGIN
  FOR num_row IN c
  LOOP
    IF num_row.presidente LIKE '%o %o %o' THEN p_presidente := num_row.presidente;
    dbms_output.put_line(p_presidente);
    END IF;
  END LOOP;
END;

--Ejercicio 2: Hashmap
SET serveroutput ON;
  DECLARE
    type hash map is table of FLOAT index by varchar2(100);
    CURSOR c IS SELECT partidos.nombrecompleto, eventos_resultados.resultado FROM partidos, eventos_resultados WHERE eventos_resultados.partido = partidos.idpartido;
    my_hmap hash_map;
    key partidos.nombrecompleto%type;
  BEGIN
    FOR num_row IN c
    LOOP
      
    END LOOP;
  END;

--Ejercicio 3:
SET serveroutput ON;
DECLARE
  CURSOR c IS SELECT votantes.nombrecompleto FROM votantes WHERE votantes.dni LIKE CONCAT('%', (votantes.localidad + 1));
  contador NUMBER := 0;
BEGIN
  FOR num_row IN c
  LOOP
    dbms_output.put_line(num_row.nombrecompleto);
    contador := contador + 1;
  END LOOP;
  dbms_output.put_line('Hay un total de ' || contador || ' votantes.');
END;

--Ejercicio 4:
SET serveroutput ON;
DECLARE 
CURSOR c IS SELECT votantes.dni FROM votantes ORDER BY votantes.dni DESC;
  v_dni votantes.dni%type;
  v_dni1 votantes.dni%type;
BEGIN
  OPEN c;
  FETCH c INTO v_dni;
  FETCH c INTO v_dni1;
  LOOP
  EXIT WHEN c%NOTFOUND;
    dbms_output.put_line(v_dni || ' va antes que ' || v_dni1);
    v_dni:= v_dni1;
  FETCH C INTO v_dni1;
  END LOOP;
  dbms_output.put_line('el menor es ' || v_dni);
END;