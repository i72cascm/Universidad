#!/bin/bash

function check() {
	if [ -e "$1" ]
	then
		return 0
	else
		return 1
	fi
}

echo -n "Introduzca el nombre del archivo: "
read fichero
if check $fichero
then
	echo "El fichero $fichero existe."
else
	echo "El fichero $fichero no existe."
fi
