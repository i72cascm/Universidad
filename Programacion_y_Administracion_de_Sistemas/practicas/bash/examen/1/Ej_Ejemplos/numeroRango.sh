#!/bin/bash

read -p "Introduzca un número (1<=x<=10): " num

if [ $num -ge 1 ]
then
	if [ $num -le 10 ]
	then
		echo "El número $num es correcto."
	else
		echo "Fuera de rango mayor de 10."
	fi
else
	echo "Fuera de rango menor de 1."
fi
