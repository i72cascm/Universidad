#!/bin/bash

read -p "Introduzca nombre de usuario: " nombre

if [ $nombre == $LOGNAME ]
then	
	echo "Bienvenido $nombre"
else
	echo "Eso es mentira"
fi
