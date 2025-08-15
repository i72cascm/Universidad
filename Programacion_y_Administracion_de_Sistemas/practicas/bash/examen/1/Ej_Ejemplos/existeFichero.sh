#!/bin/bash

if [ -f /etc/fstab ]
then
	cp /etc/fstab .
	echo "Encontrado y copiado."
else
	echo "El fichero no existe."
fi
