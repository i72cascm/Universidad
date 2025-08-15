#!/bin/bash
echo "Introduzca número 1:"
read -p "Número 1:" num1
echo "Introduzca número 2:"
read -p "Número 2:" num2

echo "Suma: $[$num1+$num2]"

echo "Resta: $(($num1-$num2))"

let multi=$num1*$num2
echo "Multiplicación: $multi"

echo "División: $[$num1/$num2]"

echo "Potencia: $[$num1**$num2]"

echo "Módulo: $[$num1%$num2]"

