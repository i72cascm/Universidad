#!/bin/bash -v
read -p "Introduzca un numero: " num

sum=$[0]
i=$[1]
while [ $i -le $num ]
do 
	let "sum=$sum+$i"
	i=$[$i+1]

done

echo "La suma de los primeros $num es $sum."
