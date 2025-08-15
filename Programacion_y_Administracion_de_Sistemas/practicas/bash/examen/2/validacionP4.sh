#!/bin/bash

echo ""

#CONTROLARGUMENTOS
#--------------------------------------

if [ $# -ne 1 ]
then
	echo "El programa solo tiene un argumento que es el archivo.txt."
	exit 1
fi

#--------------------------------------

#PRIMER EJ
#--------------------------------------
echo "--------------------------------"
echo "Primera parte del ejercicio"

cat $1 |  sed -r -e  '/======*/d' | sed -e '/^$/d' | sed -r -e 's/Reparto: (.*)/|-> Reparto: \1/g'  | sed -r -e 's/(\(..\/..\/....\)) (.*)/|-> Fecha estreno: \1/g' | sed -r -e 's/Dirigida por (.*)/|-> Director: \1/g' | sed -r -e 's/([0-9]h [0-9][0-9]min)/|-> Duración: \1/' | sed -r -e 's/(^ +)/|-> Sinopsis: \1/'| sed -r -e 's/(^[^\|])/Título: \1/' > temporalpeliculas.txt

cat temporalpeliculas.txt

#--------------------------------------

echo ""

#SEGUNDO EJ
#---------------------------------------

echo "-----------------------------------"
echo "Segunda parte del ejercicio"
cat temporalpeliculas.txt | grep -E --colour "((t|T)(a|e|i|o|u|A|E|I|O|U)( |m))" 



rm temporalpeliculas.txt

#---------------------------------------

