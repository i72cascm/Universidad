#!/bin/bash

#OJO: adaptar las leyendas a los nombres de las variables. En el eje Y se miden tiempos y en el eje X es el tamaño del ejemplar.
cat << _end_ | gnuplot
set terminal postscript eps color
set output "graficoDeterminanteIterativo.eps"
set key right bottom
set xlabel "Orden de la matriz"
set ylabel "Tiempo en microsegundos"
plot 'datosFinalesDeterminanteIterativo.txt' using 1:2 t "Tiempo Real", 'datosFinalesDeterminanteIterativo.txt' using 1:3 t "Tiempo Estimado" w l
_end_
