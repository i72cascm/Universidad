#!/bin/bash

echo ""

function recorrerDir (){
	echo $1
	find "$1" -maxdepth 1 | while read x
	do
		if [ ! -d "$x" ]
		then
		
			echo -n "<li>$x</li>" >> "$nombreDocumento"
			

		else
			if [ "$1" != "$x" ]
			then
				echo "<ul>" >> "$nombreDocumento"
				echo "<li><strong>$x</strong></li>" >> "$nombreDocumento"
				recorrerDir "$x"

				echo "</ul>" >> "$nombreDocumento"

			fi
		fi
	done
}

#CONTROL DE ARGUMENTOS
#-----------------------------------

if [ $# -ne 1 ] || [ ! -d $1 ]
then 
	echo -e "Nº de argumentos erroneo o el argumento no es un directorio.\nNecesitas introducir un directorio para generar el documento .html.\n"
	exit 1
fi

#-----------------------------------


#ESCRIBIR BASE FICHERO HTML
#-----------------------------------


nombreDocumento=$(basename $1)".html"

cat > "$nombreDocumento" << endl
<html>
<head>
<title>Listado del directorio $1</title>
</head>
<body>
<style type="text/css">
body { font-family: sans-serif;}
</style>
<h1>Listado del directorio $1</h1>
endl


recorrerDir $1

cat >> "$nombreDocumento" << endl
</body>
</html>
endl

#-----------------------------------

echo ""

