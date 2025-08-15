#!/bin/bash

var=$(date +%d-%m-%y)

if [ $# -lt 1 ]
then 
	echo "El uso del programa es $0 nombreFichero."
elif [ -f $1 ]
then
	cp $1 $1.bak_$var
else
	echo "El fichero no existe."
fi
