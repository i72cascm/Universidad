//============================================================================
// Algoritmica
// Name        : vegas.cpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 09/12/2022
//============================================================================

//Includes
#include "ClaseTiempo.hpp"
#include "funcionesGlobales.hpp"

using namespace std;

//****************************************************************************************************
//**********************************FUNCIONES LOCALES*************************************************
//****************************************************************************************************

int repetirLasVegas(int n, vector < int > &sol);
bool nReinasLasVegas(int n, vector < int > &sol);
void imprimirSoluciones(int intentos, vector < int > sol);

//****************************************************************************************************
//****************************************************************************************************

//Funcion para imprimir resultados
void imprimirSoluciones(int intentos, vector < int > sol){

    cout<<"Nº de intentos: "<<intentos<<endl;
    //cout<<endl;
    cout<<"Solucion: ";
    for(int i = 0; i < sol.size(); i++){
        cout<<sol[i]<<" ";
    }
    cout<<endl;

}

//Algoritmo de las Vegas
bool nReinasLasVegas(int n, vector < int > &sol){

    
    vector < int > ok(n); //Vector OK
    
    int contador = 0; //Contador
    int col = 0; //Columna
    int aux = 0;

    for(int k = 0; k < n; k++){ //Se han colocado k-1 reinas y se buscan todas las posiciones
        contador = 0;
        for(int j = 0; j < n; j++){ //Almacena todas las posiciones posibles la reina k en el vector ok
            sol[k] = j + 1; //Probamos la reina k en la columna j
            if((Lugar(k,sol) == true)){ //Se puede colocar en la columna
                
                if(contador + 1 < n){
                    contador++;
                    ok[contador] = j + 1; //Guardamos la posicion disponible
                }
                
            }
        }
        if(contador == 0){ //No se ha encontrado posicion para la reina
            break;
        }
        
        aux = rand()%contador + 1;
        //cout<<"Random: "<<aux<<endl;
        col = ok[aux]; //Se puede colocar la reina k y se selecciona una posicion aleatoria
        sol[k] = col;
    }

    //cout<<"Salida"<<endl;
    if(contador == 0){
        return false; //No hay solucion
    }else{
        return true; //Hay solucion
    }
    

}

//Funcion que repite el algoritmo de las vegas hasta encontrar solucion
int repetirLasVegas(int n, vector < int > &sol){

    //Declarar variables locales
    int intentos = 0;
    bool exito = false;

    //Llamamos al algoritmo de las Vegas hasta que nos de una solucion
    do{

        intentos++;
        exito = nReinasLasVegas(n,sol);

    }while(exito == false);

    //Devolvermos contador con el nº de intentos
    return intentos;

}

//Funcion principal
void algVegas(){

    //Declaración de variables
    int n = 0, intentos = 0; //Variable que indica el tamaño del tablero nxn y el nº de reinas y nº de intentos
    long double tiempo = 0.0; //Para la clase tiempo
    Clock time; //Inicializar clase tiempo

    //Pedir valor de las reinas al usuario y control 
    do{

        cout<<"Introduzca el nº de reinas y tamaño del tablero (nxn) para resolver el problema mediante algoritmo de las Vegas (el valor introducido debe ser 10 o superior)."<<endl;
        cout<<"Nº reinas: ";
        cin>>n;
        cout<<endl;
        
       
    }while(n <= 9);

    //Inicializar solucion
    vector < int > sol(n,0);

    //Clase tiempo (inicio)
    time.start();

    //Algoritmo de las Vegas
    intentos = repetirLasVegas(n,sol);

    //Clase tiempo (fin)
    if (time.isStarted()){
        time.stop();
    }

    //Guardar el tiempo transcurrido en el vector auxiliar
    tiempo = time.elapsed();
    tiempo = tiempo / 1000;

    cout<<"Tiempo transcurrido para encontrar una única solución: "<<tiempo<<" milisegundos"<<endl;

    //imprimir soluciones por pantalla
    imprimirSoluciones(intentos, sol);
    
}