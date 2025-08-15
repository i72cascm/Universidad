#!/bin/bash

echo ""

#CONTROL DE ARGUMENTOS
#---------------------------------

if [ $# -ne 1 ]
then
	echo -e "El número de argumento es 1 (peliculas.txt).\n"
	exit 1
fi

#---------------------------------


#SED
#---------------------------------

cat $1 | sed -e '/^$/d' | sed -r -e  '/====+/d' | sed -r -e 's/(\(..\/..\/....\)) (.*)/|-> Fecha estreno: \1/g' | sed -r -e 's/Dirigida por (.*)/|-> Director: \1/g' | sed -r -e 's/Reparto: (.*)/|-> Reparto: \1/g' | sed -r -e 's/([0-9]h [0-9][0-9]min)/|-> Duración: \1/' | sed -e '/^ .*/d' | sed -r -e 's/(^[^\|])/Título: \1/'

#---------------------------------
