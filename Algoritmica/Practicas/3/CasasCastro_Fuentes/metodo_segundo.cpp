//============================================================================
// Algoritmica
// Name        : metodo_segundo.cpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 25/10/2022
//============================================================================

//Includes
#include <iostream>
#include <fstream>
#include <vector>
#include "serietemporal.hpp"
#include <iterator>

using namespace std;

//****************************************************************************************************
//**********************************FUNCIONES LOCALES*************************************************
//****************************************************************************************************

void metodo_segundo();
void rellenarVectorPosiciones(SerieTemporal STemporal,vector<int> &posiciones);
void rellenarVectorErrores(SerieTemporal STemporal,vector<long double> &errores, int aux);
void eliminarRecalcularPuntos(int npuntos, SerieTemporal &STemporal, vector < long double > &errores, vector < int > &posiciones, int aux);

//****************************************************************************************************
//****************************************************************************************************

void eliminarRecalcularPuntos(int npuntos, SerieTemporal &STemporal, vector < int > &posiciones, vector < long double > &errores, int aux){

    while(posiciones.size() > npuntos){

        //Iterator
        vector < long double >::iterator it = min_element(begin(errores), end(errores));
        int index = distance(begin(errores), it);

        //Borrado de la posicion de menor error
        posiciones.erase(posiciones.begin() + index);
        errores.erase(errores.begin() + index);

        //Recalcular errores
        if(index == 1){
            
            //Caso de segunda posicion
            errores[index] = STemporal.calcularEmaxEntreDosPuntos(posiciones[index-1], posiciones[index+1],aux);

        }else if(index == errores.size()-1){

            //Caso de penultima posicion
            errores[index-1] = STemporal.calcularEmaxEntreDosPuntos(posiciones[index-2], posiciones[index],aux);

        }else{

            //Caso de posiciones comprendidas entre la segunda posicion y la penultima
            errores[index] = STemporal.calcularEmaxEntreDosPuntos(posiciones[index-1], posiciones[index+1],aux);
            errores[index-1] = STemporal.calcularEmaxEntreDosPuntos(posiciones[index-2], posiciones[index],aux);

        }
    }

}

//Funcion que rellena el vector de errores 
void rellenarVectorErrores(SerieTemporal STemporal,vector<long double> &errores, int aux){

    for(int i = 1; i < STemporal.numeroPuntosSerieTemporal()-1; i++){

        errores[i] = STemporal.calcularEmaxEntreDosPuntos(i-1, i+1, aux);

    }
    errores[0] = 99999999999;
    errores[STemporal.numeroPuntosSerieTemporal()-1] = 99999999999;
}

//Funcion que rellena el vector de dominantes con todas las posiciones del problemas (todos los puntos comienzan como dominantes)
void rellenarVectorPosiciones(SerieTemporal STemporal,vector<int> &posiciones){

    for(int i = 0; i < STemporal.numeroPuntosSerieTemporal(); i++){

        posiciones[i] = i;

    }

}

//Funcion principal
void metodo_segundo(){

    //Declaración de variables
    char fichero[100];
    int npuntos = 0;
    long double sumaErrorCuadrado = 0.0, errorPuntoMax = 0.0;
    int puntoMaxError = 0;
    char save_normal[100] = "segundoMetodo_normal.txt";
    char save_dominante[100] = "segundoMetodo_dominante.txt";
    int aux = 0;

    //Obtener los datos del usuario
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"Introduzca un fichero .txt para obtener la segmentacion."<<endl;
    cout<<"Fichero: ";
    cin>>fichero;

    //Llamada al constructor
    SerieTemporal STemporal(fichero);

    cout<<"Introduzca el nº de puntos que deben quedar."<<endl;
    cout<<"Nº de puntos: ";
    cin>>npuntos;

    //Control de errores    
    if(npuntos < 0){
        cout<<"No se pueden introducir valores negativos para el error."<<endl;
        exit(EXIT_FAILURE);
    }
    
    //Declaracion de vectores auxiliares
    vector < long double > errores(STemporal.numeroPuntosSerieTemporal(),0);
    vector < int > posiciones(STemporal.numeroPuntosSerieTemporal(),0);

    //Rellenar vectores auxiliares
    rellenarVectorPosiciones(STemporal,posiciones);
    rellenarVectorErrores(STemporal,errores, aux);

    //Funcion encargada de eliminar los puntos de manera iterativa hasta quedar con los puntos indicados
    eliminarRecalcularPuntos(npuntos, STemporal, posiciones, errores, aux);

    //Pasar a la clase temporal aquellos puntos que quedan como dominante
    for(int i = 0; i < posiciones.size(); i++){
        STemporal.dominantePunto(posiciones[i],true);
    }
    
    //Calcular valores requeridos
    STemporal.erroresSegmentacion(sumaErrorCuadrado, errorPuntoMax, puntoMaxError); 

    //Imprimir valores por pantalla
    cout<<"Numero de puntos dominantes: "<<STemporal.contarPuntosDominantes()<<endl;
    cout<<"ISE: "<<sumaErrorCuadrado<<endl;
    cout<<"Error maximo: "<<errorPuntoMax<<endl;
    cout<<"Punto error maximo: "<<puntoMaxError<<endl;

    //Guardar los datos en .txt
    STemporal.guardarSerieTemporal(save_normal);
    STemporal.guardarSegmentacion(save_dominante);

    //GNU plot para representar las gráficas
    system("./segundoMetodo.sh");
}