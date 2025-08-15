#!/bin/bash

echo ""

#PREGUNTA/RESPUESTA
#-----------------------------------

read -p "¿Cuál es tu edad? " edad

#-----------------------------------


#COMPROBAR 
#-----------------------------------

if [ $edad -lt 21 ]
then
	diferencia=$((21-$edad))
	echo "No tienes permitido conducir un coche. Te faltan $diferencia año/años."
else
	diferencia=$(($edad-20))
	let conducido=0

	for ((i=0; $i<$diferencia; i=$i+1))
	do	
	random=$(($RANDOM %201))
		 	echo $random
	let conducido=$conducido+$random
	done
	echo -e "Tienes permitido conducir un coche y has conducido $conducido hasta la fecha.\n"
fi

#-----------------------------------

