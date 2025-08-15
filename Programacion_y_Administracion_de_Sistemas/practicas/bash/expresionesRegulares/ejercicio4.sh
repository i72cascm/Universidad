#!/bin/bash

#CONTROL
if [ ! $# -eq 2 ]
then
    echo "El uso del programa es $0 nombreArchivo numeroSegundos"
fi



leido=$(mktemp)
respuesta=$(mktemp)
noRespuesta=$(mktemp)


while read -r f  #> /dev/null 2>&1 para no ver output de ping  #segundosinicio=date -d $a +%s #segundosactuales=date -d $b +%s
do
ping $f -c 1 -w $2 > $leido
rc=$?

if [[ $rc -eq 0 ]]
then
    cat $leido | sed -n -r -e 's/(.+from )(.+)(:.+ )(time=)(.+)( ms)/La IP \2 ha tardado \5 milisegundos/p' >> $respuesta
else
    echo "La IP $f no respondio tras $2 segundos" >> $noRespuesta
fi
done < $1 
cat $respuesta | sort -n -k6
cat $noRespuesta

rm $leido
rm $respuesta
rm $noRespuesta