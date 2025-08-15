#!/bin/bash

echo ""

#CONTROL DE ARGUMENTOS
#---------------------------------

if [ $# -ne 1 ] && [ $# -ne 2 ]
then
	echo "Número de argumentos erroneo."
	exit 1
fi

ARGUMENTOS=1
#---------------------------------

if [ $# -eq 1 ]
then
	echo "$1 -> ."
	echo "No hacer copia de seguridad"

	#MOSTRAR ARGUMENTOS INTRODUCIDOS
	#---------------------------------

	#echo -e "(argumento 1): $1  \n(argumento 2): $2 "

	#---------------------------------

	#MOSTRAR NUMERO TOTAL DE FICHEROS EN LA CARPETA PASADA
	#---------------------------------

	let contador=0

	for x in $(find $1 -type f)
	do
		#echo $x
		let contador=$contador+1
	
	done

	echo "Número de archivos: $contador"

	#---------------------------------

	echo ""

	#PARA CADA FICHERO SE MUESTRA
	#---------------------------------

	echo "Tamaño+Nombre+Lineas+Tipo"
	echo "---------+-------+-----+-----"

	for x in $(find $1 -type f)
	do

		echo "$(stat -c %s $x)+$(basename $x)+$(wc -l < $x)+$(stat -c %F $x)"

	done | sort -r -n -k1 -t "+"

fi

#----------------------------------



#ARGUMENTOS=2
#----------------------------------


if [ $# -eq 2 ]
then
	echo "Carpeta -> $1"
	echo "Hacer copia de seguridad en $2"

	if [ -d $2 ]
	then
		echo "Borrando copia de seguridad"
		rm -r $2
	fi

	let contador=0

	for x in $(find $1 -type f)
	do
		#echo $x
		let contador=$contador+1
	
	done

	echo "Número de archivos: $contador"

	#---------------------------------

	echo ""

	#PARA CADA FICHERO SE MUESTRA
	#---------------------------------

	echo "Tamaño+Nombre+Lineas+Tipo"
	echo "---------+-------+-----+-----"

	for x in $(find $1 -type f)
	do

		echo "$(stat -c %s $x)+$(basename $x)+$(wc -l < $x)+$(stat -c %F $x)"

	done | sort -r -n -k1 -t "+"

mkdir $2
fi

 

	

echo "-----------------------------"

#----------------------------------

