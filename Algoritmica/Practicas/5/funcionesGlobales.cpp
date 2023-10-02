//============================================================================
// Algoritmica
// Name        : funcionesGlobales.cpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 10/12/2022
//============================================================================

//Includes
#include "funcionesGlobales.hpp"
#include <stdlib.h>

using namespace std;

//Funcion para comprobar si la reina actual amenaza a otras 
bool Lugar(int k, vector < int > X){
    for(int i = 0; i < k; i++){

        if((X[i] == X[k]) || (abs(X[i] - X[k]) == abs(i - k))){ //Comprueba que las reinas no se amenacen en cruz (vertical y horizontal) y diagonal
            return false;
        }

        //Los siguientes if comprueban que la reina no pueda atacar a otras reinas que esten en etapas anteriores mediante los movimientos del caballo
        if((X[k] == X[i] + 2) && (k == i + 1)){
            return false;
        }

        if((X[k] == X[i] - 2) && (k == i + 1)){
            return false;
        }
        
        if((X[k] == X[i] + 1) && (k == i + 2)){
            return false;
        }

        if((X[k] == X[i] - 1) && (k == i + 2)){
            return false;
        }

    }
    return true;
}