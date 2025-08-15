#!/bin/bash

echo -n "Introduzca nombre de fichero a borrar: "
read fichero
rm -i $fichero #-i pide confirmacion
echo "Fichero $fichero borrado!"
