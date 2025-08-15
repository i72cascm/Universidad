import oracledb

####################################################################################
## CONEXION
####################################################################################

# Conexión con la base de datos
def conectar_a_oracle():
    try:
        cnx = oracledb.connect(user="system", password="Ora1234", dsn="localhost/free")
        return cnx
    except oracledb.DatabaseError as e:
        print("Error al conectarse a la base de datos:", e)
        return None
    
####################################################################################
## CONSULTAS
####################################################################################

# Consultar tabla entregas
def consultar_entregas(cnx):
    cursor = cnx.cursor()
    cursor.execute("SELECT * FROM entrega") 
    registros = cursor.fetchall()
    cursor.close()
    if not registros:
        print("No hay registros en la tabla de entregas.")
    else:
        for x in registros:
            print(x)

# Consultar tabla lotes
def consultar_lotes(cnx):
    cursor = cnx.cursor()
    cursor.execute("SELECT * FROM produccionaceite") 
    registros = cursor.fetchall()
    cursor.close()
    if not registros:
        print("No hay registros en la tabla de lotes.")
    else:
        for x in registros:
            print(x)

####################################################################################
## INSERCIONES
####################################################################################

# Insertar en tabla entrega
def insercion_entrega(cnx):
    id_entrega = input("Introduzca el ID de la entrega: ")
    fecha = input("Introduzca la fecha en el formato DD-MM-YYYY: ")
    peso = input("Introduzca el peso de la entrega en kilogramos: ")
    calidad = input("Introduzca la calidad de la entrega (0-10): ")
    tipo = input("Introduzca el tipo de aceituna (Picual, Hojiblanca, Royal, Cornicabra): ")
    dni = input("Introduzca el DNI del agricultor: ")

    SQL = '''INSERT INTO entrega (idEntrega, fecha, peso, calidad, tipoAceituna, dniAgricultor)
             VALUES (:id_entrega, TO_DATE(:fecha, 'DD-MM-YYYY'), :peso, :calidad, :tipo_aceituna, :dni_agricultor)'''
    
    try:
        cursor = cnx.cursor()
        cursor.execute(SQL, [id_entrega, fecha, peso, calidad, tipo, dni])
        cnx.commit()
        print("Entrega insertada con éxito.")
    except oracledb.DatabaseError as e:
        print("Error al insertar en la base de datos:", e)
    finally:
        cursor.close()

# Insertar en tabla produccionAceite
def insercion_lote(cnx):
    id_produccion = input("Introduzca el ID del lote: ")
    litros = input("Ingrese la cantidad de litros: ")
    fecha = input("Introduzca la fecha en el formato DD-MM-YYYY: ")
    rendimiento = input("Ingrese el rendimiento: ")
    tipo_aceite = input("Ingrese el tipo de aceite (Virgen, Virgen Extra, Orujo): ")
    id_entrega = input("Ingrese el ID de la entrega: ")
    id_equipo = input("Ingrese el ID del equipo de trabajo: ")

    SQL = '''INSERT INTO produccionAceite (idProduccion, litros, fecha, rendimiento, tipoAceite, idEntrega, idEquipo)
             VALUES (:id_produccion, :litros, TO_DATE(:fecha, 'DD-MM-YYYY'), :rendimiento, :tipo_aceite, :id_entrega, :id_equipo)'''
    
    try:
        cursor = cnx.cursor()
        cursor.execute(SQL, [id_produccion, litros, fecha, rendimiento, tipo_aceite, id_entrega, id_equipo])
        cnx.commit()
        print("Lote entregado con éxito.")
    except oracledb.DatabaseError as e:
        print("Error al insertar en la base de datos:", e)
    finally:
        cursor.close()

####################################################################################
## MODIFICACIONES
####################################################################################
            
# Modificar tupla de la tabla entrega
def modificar_entrega(cnx):
    id_entrega = input("Introduca la ID de la entrega que desea modificar: ")
    print("Los valores que no sean modificados deben dejarse en blanco.")
    nueva_fecha = input("Introduzca la nueva fecha en el formato DD-MM-YYYY: ")
    nuevo_peso = input("Introduzca el nuevo peso: ")
    nueva_calidad = input("Introduzca la nueva calidad (0-10): ")
    nuevo_tipo_aceituna = input("Introduzca el nuevo tipo de aceituna (Picual, Hojiblanca, Royal, Cornicabra): ")
    nuevo_dni_agricultor = input("Introduzca el nuevo DNI del agricultor: ")

    SQL = """
    UPDATE entrega
    SET fecha = NVL(TO_DATE(:nueva_fecha, 'DD-MM-YYYY'), fecha), 
        peso = NVL(:nuevo_peso, peso),
        calidad = NVL(:nueva_calidad, calidad),
        tipoAceituna = NVL(:nuevo_tipo_aceituna, tipoAceituna),
        dniAgricultor = NVL(:nuevo_dni_agricultor, dniAgricultor)
    WHERE idEntrega = :id_entrega
    """

    try:
        cursor = cnx.cursor()
        cursor.execute(SQL, [nueva_fecha if nueva_fecha else None, 
                                nuevo_peso if nuevo_peso else None, 
                                nueva_calidad if nueva_calidad else None, 
                                nuevo_tipo_aceituna if nuevo_tipo_aceituna else None, 
                                nuevo_dni_agricultor if nuevo_dni_agricultor else None, 
                                id_entrega])
        cnx.commit()
        if cursor.rowcount > 0:
            print("Entrega modificada con éxito.")
        else:
            print("No se encontró una entrega con el ID proporcionado.")
    except oracledb.DatabaseError as e:
        print("Error al modificar en la base de datos:", e)
    finally:
        cursor.close()

# Modificar tupla de la tabla produccionAceite
def modificar_lote(cnx):
    id_produccion = input("Introduzca la ID del lote que desea modificar: ")
    print("Los valores que no sean modificados deben dejarse en blanco.")
    nuevos_litros = input("Introduzca los nuevos litros: ")
    nueva_fecha = input("Introduzca la nueva fecha en el formato DD-MM-YYYY: ")
    nuevo_rendimiento = input("Introduzca el nuevo rendimiento: ")
    nuevo_tipoAceite = input("Introduzca el nuevo tipo de aceite (Virgen, Virgen Extra, Orujo): ")
    nuevo_idEntrega = input("Introduzca el nuevo ID de entrega: ")
    nuevo_idEquipo = input("Introduzca el nuevo ID de equipo: ")

    SQL = """
    UPDATE produccionAceite
    SET litros = NVL(:nuevos_litros, litros),
        fecha = NVL(TO_DATE(:nueva_fecha, 'DD-MM-YYYY'), fecha),
        rendimiento = NVL(:nuevo_rendimiento, rendimiento),
        tipoAceite = NVL(:nuevo_tipoAceite, tipoAceite),
        idEntrega = NVL(:nuevo_idEntrega, idEntrega),
        idEquipo = NVL(:nuevo_idEquipo, idEquipo)
    WHERE idProduccion = :id_produccion
    """

    try:
        cursor = cnx.cursor()
        cursor.execute(SQL, [nuevos_litros if nuevos_litros else None, 
                             nueva_fecha if nueva_fecha else None,
                             nuevo_rendimiento if nuevo_rendimiento else None, 
                             nuevo_tipoAceite if nuevo_tipoAceite else None, 
                             nuevo_idEntrega if nuevo_idEntrega else None,
                             nuevo_idEquipo if nuevo_idEquipo else None, 
                             id_produccion])
        cnx.commit()
        if cursor.rowcount > 0:
            print("Producción modificada con éxito.")
        else:
            print("No se encontró una producción con el ID proporcionado.")
    except Exception as e:
        print("Error al modificar en la base de datos:", e)
    finally:
        cursor.close()

####################################################################################
## BORRADOS
####################################################################################

# Borrar tupla de la tabla entrega
def borrar_entrega(cnx):
    id_entrega = input("Introduzca la ID de la entrega que desea eliminar: ")

    SQL = '''DELETE FROM entrega WHERE idEntrega = :id_entrega'''

    try:
        cursor = cnx.cursor()
        cursor.execute(SQL, [id_entrega])
        cnx.commit()
        if cursor.rowcount > 0:
            print("Entrega borrada con éxito.")
        else:
            print("No se encontró una entrega con ese ID, cancelando borrado.")
    except oracledb.DatabaseError as e:
        print("Error al borrar en la base de datos:", e)
    finally:
        cursor.close()

# Borrar tupla de la tabla lote
def borrar_lote(cnx):
    id_lote = input("Introduzca la ID de la entrega que desea eliminar: ")

    SQL = '''DELETE FROM produccionaceite WHERE idProduccion = :id_lote'''

    try:
        cursor = cnx.cursor()
        cursor.execute(SQL, [id_lote])
        cnx.commit()
        if cursor.rowcount > 0:
            print("Lote borrado con éxito.")
        else:
            print("No se encontró un lote con ese ID, cancelando borrado.")
    except oracledb.DatabaseError as e:
        print("Error al borrar en la base de datos:", e)
    finally:
        cursor.close()

####################################################################################
## SUBMENUS
####################################################################################
            
# Submenu de la tabla entregas
def submenu_entregas(cnx):
    while True:
        print("\nSubmenú - Datos de Entregas")
        print("1. Consultar tabla de datos de entregas")
        print("2. Insertar dato")
        print("3. Modificar dato")
        print("4. Borrar dato")
        print("5. Salir del submenú")
        opcion = input("Ingrese su opción: ")

        if opcion == '1':
            consultar_entregas(cnx)
            break  
        elif opcion == '2':
            insercion_entrega(cnx)
            break
        elif opcion == '3':
            modificar_entrega(cnx)
            break
        elif opcion == '4':
            borrar_entrega(cnx)
            break
        elif opcion == '5':
            print("Regresando al menú principal...")
            break
        else:
            print("ERROR: Esa opción no es válida, intentelo nuevamente.")

# Submenu de la tabla lotes (produccionAcetite)
def submenu_lotes(cnx):
    while True:
        print("\nSubmenú - Datos de Lotes")
        print("1. Consultar tabla de datos de lotes")
        print("2. Insertar dato")
        print("3. Modificar dato")
        print("4. Borrar dato")
        print("5. Salir del submenú")
        opc = input("Ingrese su opción: ")

        if opc == '1':
            consultar_lotes(cnx)
            break  
        elif opc == '2':
            insercion_lote(cnx)
            break
        elif opc == '3':
            modificar_lote(cnx)
            break
        elif opc == '4':
            borrar_lote(cnx)
            break
        elif opc == '5':
            print("Regresando al menú principal...")
            break
        else:
            print("ERROR: Esa opción no es válida, intentelo nuevamente.")

####################################################################################
## MENU PRINCIPAL
####################################################################################

# Menu principal del programa
def main():
    cnx = conectar_a_oracle()
    if cnx is not None:
        while True:
            print("1. Ir a los datos de entregas")
            print("2. Ir a los datos de lotes")
            print("3. Salir")
            opc = input("Ingrese su opción: ")
            if opc == '1':
                opc = submenu_entregas(cnx)
            elif opc == '2':
                submenu_lotes(cnx)
            elif opc == '3':
                print("Saliendo del programa.")
                break
            else:
                print("ERROR: Esa opción no es válida, intentelo nuevamente.")

        cnx.close()


if __name__ == "__main__":
    main()
