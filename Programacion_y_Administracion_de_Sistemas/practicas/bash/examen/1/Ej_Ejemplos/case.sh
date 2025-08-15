#!/bin/bash
read -p "Introduze un número (1<=x<10): " num

case $num in
	1) echo "Se ha introducido el valor 1. Es correcto.";;
	2) echo "Se ha introducido el valor 2. Es correcto.";;
	3 | 4 | 5 | 6 | 7 | 8 | 9) echo "Es correcto";;
	0)echo "Error.";;
	10)echo "Error.";;
	*)echo "Atiende a las instrucciones.";;
esac
