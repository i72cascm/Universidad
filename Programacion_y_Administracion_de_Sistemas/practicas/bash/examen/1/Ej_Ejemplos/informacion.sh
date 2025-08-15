#!/bin/bash

informacion="Bienvenido $USER, tu identificador es $UID.\n Esta es la shell número $SHLVL, que lleva $SECONDS segundos arrancada. \n La arquitectura de esta máquina es $MACHTYPE y el cliente de terminal es $TERM."

echo -e $informacion
