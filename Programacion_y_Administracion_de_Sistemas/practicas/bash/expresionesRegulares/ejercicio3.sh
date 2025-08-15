#!/bin/bash

echo ""

#ARGUMENTOS
#----------------------------------

if [ $# -ne 0 ]
then
	echo -e "Este programa no requiere argumentos.\n"
	exit 1
fi

#----------------------------------

#MOSTRAR USUARIOS Y HORA DE CONEXIÓN
#----------------------------------

usuario=$(who | grep -E -o '^[a-zA-Z0-9]*')

fechainicial=$(who | sed -r -e 's/(.*)([0-9]{4}-[0-9]*-[0-9]* [0-9][0-9]:[0-9][0-9])(.*)/\2/')
let seginicio=$(date -d "$fechainicial" +%s)
echo $seginicio
let segfin=$(date +%s)
echo $segfin

let segfin=$segfin-$seginicio
horas=$((segfin / 3600))
minutos=$((segfin%3600/60))
segundos=$((segfin%60))

echo $segfin

echo -e "El usuario $usuario lleva $horas horas, $minutos minutos $segundos segundos conectado.\n"
#----------------------------------
