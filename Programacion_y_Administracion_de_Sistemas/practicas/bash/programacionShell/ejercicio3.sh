#!/bin/bash

echo ""


#CONTROL DE ARGUMENTOS
#------------------------------------------

if [ $# -lt 1 ] || [ $# -gt 3 ]
then 
	echo -e "Para este ejercicio necesitas pasar un argumento obligatorio (directorio) y dos opcionales (pequeños y grandes).\nSi los opcionales no se introducen se ponen por defecto a 4.\n"
	exit 1

elif [ $# -eq 1 ]
then
	let tamp=4
	let tamg=4

elif [ $# -eq 2 ]
then
	let tamp=$2
	let tamg=4
else
	let tamp=$2
	let tamg=$3
fi

#------------------------------------------

#CONTAR NÚMERO DE FICHEROS EN EL DIRECTORIO
#------------------------------------------

let contador=0
for x in $(find $1 -maxdepth 1 -type f )
do
	let "contador=$contador+1"
done

let "tamm=$contador-$tamp-$tamg"

if [ $tamm -lt 0 ]
then
	echo "Error al copiar..."
	exit 1
fi

#------------------------------------------


#ELIMINAR CARPETAS
#------------------------------------------
	
cd $1
if [ $(find -name "pequeno") ] || [ $(find -name "mediano") ] || [ $(find -name "grande") ] 
then
	echo -e "Borrando directorios (pequeno,mediano y grande)...\n"
	
	rm -r pequeno/
	rm -r mediano/
	rm -r grande/
fi

	
#------------------------------------------



#CREAR CARPETAS / COPIAR FICHEROS A DIRECTORIOS CORRESPONDIENTES
#------------------------------------------

ls -Sr > ../ficheroTemporal.txt

echo -e "Creando carpetas...\n"
mkdir grande/
mkdir mediano/
mkdir pequeno/

echo "Copiando ficheros..."

while read -r line
do

	if [ $tamp -gt 0 ]
	then
		cp $line pequeno
		tamp=$(($tamp-1))
	elif [ $tamm -gt 0 ]
	then
		cp $line mediano
		tamm=$(($tamm-1))
	elif [ $tamg -gt 0 ]
	then
		cp $line grande
		tamg=$(($tamg-1))
	
	fi

done < ../ficheroTemporal.txt

rm ../ficheroTemporal.txt

#------------------------------------------

echo ""
