#!/bin/bash

echo ""

#CONTROL DE ARGUMENTOS
#---------------------------

if [ $# -ne 1 ]
then
	echo -e "Este programa requiere un solo argumento (0 o 1), si es 1 mostrará aquellos usuarios cuya UID es mayor a 1000, si es 0, se mostrarán todos los usuarios.\n"
	exit 1
fi

#---------------------------


#PROCESAMIENTO
#---------------------------

if [ $1 -eq 1 ] #UID MAYOR 1000
then

	cat /etc/passwd | sed -n -r -e 's/(.*):(.*):([0-9][0-9][0-9][0-9]+):(.*):(.*):(.*):(.*)/Logname: \1\n->UID \3\n->GID \4\n->gecos \5\n->Home \6\n->Shell por defecto: \7/p' 

elif [ $1 -eq 0 ] #TODOS
then

	cat /etc/passwd | sed -n -r -e 's/(.*):(.*):(.*):(.*):(.*):(.*):(.*)/Logname: \1\n->UID \3\n->GID \4\n->gecos \5\n->Home \6\n->Shell por defecto: \7/p' 

else
	echo "Tienes que introducir 1 o 0."
fi

#---------------------------

echo ""
