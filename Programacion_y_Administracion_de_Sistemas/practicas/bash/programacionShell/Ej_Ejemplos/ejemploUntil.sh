#!/bin/bash

read -p "Introduzca un numero: " num

sum=$[0]
i=$((1))

until [ $i -gt $num ]
do
	let "sum=$sum+$i"
	i=$[$i+1]
done

echo "La suma de los primeros $num números es $sum."
