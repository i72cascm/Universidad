#!/bin/bash

echo ""

#CONTROL ARGUMENTOS
#----------------------------------------

if [ $# -ne 0 ]
then
	echo -e "El número de argumentos requeridos para este programa es 0.\n"
	exit 1
fi

#----------------------------------------


#PROCESAMIENTO /PROC/CPUINFO
#----------------------------------------

cat /proc/cpuinfo | sed -n -r -e 's/model name[[:blank:]]*: (.*)/Modelo del procesador: \1/p' | head -1

cat /proc/cpuinfo | sed -n -r -e 's/cpu MHz[[:blank:]]*: (.*)/Megahercios: \1/p' | head -1

cat /proc/cpuinfo | sed -n -r -e 's/cache size[[:blank:]]*: (.*)/Tamaño de caché: \1/p' |head -1

cat /proc/cpuinfo |sed -n -r -e 's/vendor_id[[:blank:]]*: (.*)/ID vendedor: \1/p' | head -1 

echo "Número de hilos de ejecución: $(cat /proc/cpuinfo | grep -E 'processor[[:blank:]]*: .+' | wc -l)"

#----------------------------------------

echo ""

#PROCESAMIENTO /PROC/PARTITIONS
#----------------------------------------

echo "Particiones y número de bloques: "
cat /proc/partitions | sed -e '1,2d' | sed -r -e 's/([0-9]*[[:blank:]]*[0-9]*[[:blank:]]*)([0-9]*)([[:blank:]]*)([[:alnum:]]*)$/-> Partición: \4, Número Bloques: \2/' | sort -r -k2

#----------------------------------------

echo ""
