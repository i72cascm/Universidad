# Ejercicio 4

#!/bin/bash
echo -e "\n"

# CONTADOR DE ARGUMENTOS
#-----------------------

if [ $# -ne 0 ];
then
	echo "NO INTRODUZCA ARGUMENTOS"
	echo -e "\n"
	exit 1
fi

#CONTADOR ARCHIVOS
#-----------------
for x in `ls -l`
do
  if [[ -f $x ]]
  then
    let nArchivos+=1
  fi
done

echo "Número de archivos: "$nArchivos""
echo

#USUARIOS LOGEADOS
#-----------------

echo "Lista de usuarios logeados en este instante: "
who | awk '{print $1}' | sort -k1 | uniq
echo

#CONTADOR DE CARACTERES
#----------------------

echo "Introduzca caracter a contar."
read -t5 caracter

if [[ -z $caracter ]]
then
  caracter=a
fi

for x in `ls -R`
do
  if [[ $x =~ $caracter ]]
  then
    let nCaracter+=1
  fi
done

echo "El caracter '$caracter' aparece $nCaracter veces en los ficheros o carpetas del directorio actual."

echo -e "\n"
