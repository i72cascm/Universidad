# Ejercicio 6

#!/bin/bash
echo -e "\n"

function recorrerDirectorio ()
{
	find "$1" -maxdepth 1 | while read f
	do
		if [ ! -d "$f" ]
		then
			echo -n "<ul>" >> "$FicheroHTML"
			echo -n "<li>$f</li>" >> "$FicheroHTML"
			echo "</ul>" >> "$FicheroHTML"

		else
			if [ "$1" != "$f" ]
			then
				echo "<ul>" >> "$FicheroHTML"
				echo "<li><strong>$f</strong></li>" >> "$FicheroHTML"
				recorrerDirectorio "$f"

				echo "</ul>" >> "$FicheroHTML"

			fi
		fi
	done
}




# CONTADOR DE ARGUMENTOS
# -----------------------

if [ $# -ne 1 ]
then
	echo "ERROR: Debe introducir $0 <nombre_directorio>"
	echo -e "\n"
	exit 1
fi

if [ ! -d "$1" ]
then
	echo "El argumento <$1> no es un directorio"
	echo -e "\n"
	exit 1
fi



# PROCESAMIENTO
#--------------

Fichero=$(readlink -f "$1")



FicheroHTML="$(basename "$Fichero").html"


echo "Generando el listado de la carpeta &(basename "$Fichero") sobre el fichero $FicheroHTML..."




cat > "$FicheroHTML" << EOF
<html>
<head>
<title>Listado del directorio $(basename "$Fichero")</title>
</head>
<body>
<h1>Listado del directorio $(basename "$Fichero")</h1>
EOF



recorrerDirectorio "$Fichero"



cat >> "$FicheroHTML" << EOF
</body>
</html>
EOF

echo "Terminado!"
echo -e "\n"
