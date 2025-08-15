#!/bin/bash

echo ""


#CONTADOR DE ARGUMENTOS
#-----------------------------------

if [ $# -eq 0 ]
then
	echo -e "Necesitas pasar al menos un argumento para realizar la copia de seguridad.\n"
	exit 1
fi

#-----------------------------------


#BORRAR ARCHIVOS DE HACE MAS DE 200s
#-----------------------------------

if [ -d $HOME/Copia ]
then
	find $HOME/Copia/ -type f | while read x
	do
		seg=$(date +%s)
		modif=$(stat -c "%Y" $x)
		diferencia=$(($seg - $modif))

		if [ $diferencia -gt 200 ]
		then
			rm $x
			echo -e "Se ha eliminado $x, llevaba $diferencia segundos sin modificarse.\n"
		fi
	done
fi

#-----------------------------------


# ARCHIVOS VALIDOS
#-----------------------------------

nExist=0
	#Si se elimina "in ..." se itera sobre los argumentos
for x
do
	if [ -e $x ]
	then
		fecha=$(date +%s)
		Array[$nExist]="$x"
		let nExist=$nExist+1
	else
		echo "El argumento <$x> no existe."
	fi
done

if [ $nExist -eq 0 ]
then
	echo "No se han pasado argumentos validos."
	exit 1
fi

#-----------------------------------


#COMPRIMIR Y MOVER A LA CARPETA COPIA
#-----------------------------------

tar -czf copia-$USER-$fecha.tar.gz ${Array[*]}
echo "Comprimiendo..."

if [ ! -e $HOME/Copia ]
then
	echo "Creando la carpeta de copia..."
	mkdir $HOME/Copia
fi

mv copia-$USER-$fecha.tar.gz $HOME/Copia/

echo "La copia se ha realizado correctamente."


#-----------------------------------

echo ""
