#!/bin/bash 

echo ""

#CONTROLADOR DE ARGUMENTOS
#----------------------------------

if [ $# -lt 1 ] || [ $# -gt 2 ]
then
	echo -e "Para el programa solo se puede introducir o un argumento (directorio y bytes=0) o dos argumentos (directorio y bytes).\n"
	exit 1
fi

#----------------------------------

#ASIGNACION DE TAMAÑO DE BYTES
#----------------------------------

if [ $# -eq 1 ]
then 
	let tamano=0
else
	let tamano=$2
fi

#----------------------------------


#BUSCAR FICHEROS DEL DIRECTORIO CON LOS BYTES INDICADOS + IMPRIMIR INFO POR PANTALLA
#----------------------------------

echo -e "Nombre,Longitud,UID,UsuarioID,UsuarioNombre,NumeroEnlaces,FechaCreacion,Permisos,Ejecutable\n"

for x in $(find $1 -type f -size "$tamano"c -or -type f -size +"$tamano"c)
do

	if [ -x $x ]
	then
		ejecutable=1
	else
		ejecutable=0
	fi


	nombre=${x%.*}
	nombresolo=$(basename $nombre)
	longitudNombre=${#nombresolo}
	uid=$(stat -c %u $x)
	user=$(stat -c %U $x)
	enlaces=$(stat -c %h $x)
	modificacion=$(stat -c %s $x)
	permisos=$(stat -c %Y $x)

echo "$nombresolo,$longitudNombre,$uid,$user,$enlaces,$modificacion,$permisos,$ejecutable"


done | sort -n -k2 -t "," #ordena numericamente por la columna 2 con los separadores ","

#---------------------------------- 

echo ""
