#ejercicio 2

#!/bin/bash
echo -e  "\n"


# CONTADOR ARGUMENTOS
#--------------------

if [ $# -eq 0 ] || [ $# -ge 3 ];
then
  echo "Introduzca $0  <Directorio> y opcionalmetne, una cantidad de bytes"
  echo -e "\n"
  exit 1
else
  if [ $# -eq 1 ];
  then
    tam=0
  else
    tam=$2
  fi

#MOSTRAR DATOS
#-------------

flag=0
for x in $(find $1 -size "$tam"c -or -size +"$tam"c)
do
  if [ "$flag" -eq 0 ]
  then
      echo -e "\n"
      echo "Nombre; LonguitudUsuario; FechaModificacion; FechaAcceso; Tamaño; Bloques; Permisos; Ejecutable"
      flag=1
  fi

if [ -x $x ];
then
    ejecutable=1
else
    ejecutable=0
fi

nombre=$(basename $x)
let longuitudUsuario=$(stat -c "%U" $x | wc -m)-1
fechaModificacion=$(stat -c "%y" $x)
fechaAcceso=$(stat -c "%x" $x)
tamano=$(stat -c "%s" $x)
bloques=$(stat -c "%b" $x)
permisos=$(stat -c "%A" $x)

echo "$nombre; $longuitudUsuario; $fechaModificacion; $fechaAcceso; $tamano; $bloques; $permisos; $ejecutable"
done | sort -n -k5 -t ";"
fi
echo -e "\n"
