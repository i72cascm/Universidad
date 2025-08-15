#!/bin/bash

echo ""

# CONTROLADOR DE ARGUMENTOS INTRODUCIDOS
#---------------------------------------

if [ $# -ne 1 ]
then
	echo -e "Debe introducir un solo argumento que debe ser un directorio.\n"
	exit 1
fi

#---------------------------------------


# BUSCAR FICHEROS.C E IMPRIMIRLOS EN ORDEN
#---------------------------------------

for x in $(find -name "*.c")
do
	echo "El fichero $x tiene $(cat $x | wc -m) caracteres y $(cat $x | wc -l) lineas." >> ficherotemp.txt
done 

cat ficherotemp.txt | sort -nr -k8
rm ficherotemp.txt

#---------------------------------------

echo ""

