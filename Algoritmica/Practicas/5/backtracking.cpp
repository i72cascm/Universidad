//============================================================================
// Algoritmica
// Name        : backtracking.cpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 22/11/2022
//============================================================================

//Includes
#include "ClaseTiempo.hpp"
#include "funcionesGlobales.hpp"

using namespace std;

//****************************************************************************************************
//**********************************FUNCIONES LOCALES*************************************************
//****************************************************************************************************

void algoritmoNReinas(int n, vector < vector < int > > &soluciones, bool solUnica);
void imprimirSoluciones(vector < vector < int > > soluciones);

//****************************************************************************************************
//****************************************************************************************************

//Imprimir soluciones
void imprimirSoluciones(vector < vector < int > > soluciones){
    for(int i = 0; i < soluciones.size(); i++){
        cout<<"Solucion ["<<i<<"]: ";
        for(int j = 0; j < soluciones[i].size(); j++){
            cout<<soluciones[i][j]<<" ";
        }
        cout<<endl;
    }
}

//Algoritmo de backtracking para n-Reinas
void algoritmoNReinas(int n, vector < vector < int > > &soluciones, bool solUnica){

    //Declaracion de variables locales
    int k = 0; //Variable que indica la etapa actual
    vector < int > X(n,0); //Almacena en cada momento los candidaros que forman parte de la rama del arbol que esta siendo explorado

    //Algoritmo n - reinas:
    X[0] = 0; //Colocar la primera reina en la columna 0 (fila 1)
    k = 0; 
    while(k >= 0){ //mientras no se tengan todas las soluciones hacer
        X[k] = X[k] + 1; //desplazar reina a la siguiente columna
        while((X[k] <= n) && (Lugar(k,X) == false)){ //mientras no salga del tablero y sea amenazada por una anterior hacer
            X[k] = X[k] + 1; //Desplazar reina a la siguiente columna
        }
        if(X[k] <= n){ //Si una posicion correcta ha sido encontrada
            if(k == n-1){ //Si es la ultima reina, se tiene una solucion
                soluciones.push_back(X); //Escribir la solucion
                if(solUnica == true){break; } //Salida del algoritmo en caso de que sea la segunda opcion
            }else{ //No es la ultima reina y hay que probar la siguiente
                k = k + 1; //Pasar a probar la siguiente reina ubicandola en columna
                X[k] = 0;
            }
        }else{ //La reina no se puede ubicar
            k = k - 1;
        }
    }
}

//Funcion principal
void nReinas(bool solUnica){

    //Declaración de variables
    int n = 0; //Variable que indica el tamaño del tablero nxn y el nº de reinas
    vector < vector < int > > soluciones; //Vector que guarda las tuplas soluciones
    long double tiempo = 0.0; //Para la clase tiempo
    Clock time; //Inicializar clase tiempo

    //Pedir valor de las reinas al usuario y control 
    do{

        cout<<"Introduzca el nº de reinas y tamaño del tablero (nxn) para resolver el problema mediante backtracking (el valor introducido debe ser 1 o superior)."<<endl;
        cout<<"Nº reinas: ";
        cin>>n;
        cout<<endl;
        
       
    }while(n <= 0);

    //Opcion 2: Inicializar contador
    if(solUnica == true){

        //Clase tiempo (inicio)
        time.start();

    }
    
    //Algoritmo de backtracking
    algoritmoNReinas(n, soluciones, solUnica);

    //Opcion 2: Mostrar tiempo solo si existe alguna solucion
    if(solUnica == true && !soluciones.empty()){

        //Clase tiempo (fin)
        if (time.isStarted()){
            time.stop();
        }

        //Guardar el tiempo transcurrido en el vector auxiliar
        tiempo = time.elapsed();
        tiempo = tiempo / 1000;

        cout<<"Tiempo transcurrido para encontrar una única solución: "<<tiempo<<" milisegundos"<<endl;

    }

    //imprimir soluciones por pantalla
    imprimirSoluciones(soluciones);

}