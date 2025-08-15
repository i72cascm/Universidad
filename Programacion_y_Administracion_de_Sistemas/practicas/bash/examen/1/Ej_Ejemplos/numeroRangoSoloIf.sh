#!/bin/bash

read -p "Introduzca un número (1<=x<=10): " num

if [ $num -ge 1 ] && [ $num -lt 10 ]
then 
	echo "Correcto"
else
	echo "Fuera de rango"
fi
