//============================================================================
// Algoritmica
// Name        : metodo_segudo.cpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 11/10/2022
//============================================================================

//Includes
#include <iostream>
#include <fstream>
#include "serietemporal.hpp"

using namespace std;

//****************************************************************************************************
//**********************************FUNCIONES LOCALES*************************************************
//****************************************************************************************************

void metodo_segundo();
void calculoRecursivoDos(int inicial, int final, double error, SerieTemporal &STemporal);

//****************************************************************************************************
//****************************************************************************************************

void calculoRecursivoDos(int inicial, int final, double error, SerieTemporal &STemporal){

    //Declaracion de variables
    double errorCalculado = 0.0;
    int posicion = 0, final_izq = 0, inicial_drch = 0;

    //Funcion para calcular error, obtener el punto y setearlo como dominante
    errorCalculado = STemporal.calcularEmaxEntreDosPuntos(inicial, final, posicion);

    //Si el error es mayor que el error maximo, marcar como dominante y repetir el con esos intervalos
    if(errorCalculado > error){

        posicion = (inicial + final) / 2;

        //Set dominante
        STemporal.dominantePunto(posicion, true);

        //Recursividad izq-drch
        final_izq = posicion;
        calculoRecursivoDos(inicial, final_izq, error, STemporal);

        inicial_drch = posicion;
        calculoRecursivoDos(inicial_drch, final, error, STemporal);

    //En caso contrario, el intervalo es solucion
    }else{

        return;

    } 
}

void metodo_segundo(){

    //Declaracion de variables
    char fichero[100];
    char save_normal[100] = "segundoMetodo_normal.txt";
    char save_dominante[100] = "segundoMetodo_dominante.txt";
    double errorMax = 0.0; 
    long double sumaErrorCuadrado = 0.0, errorPuntoMax = 0.0;
    int puntoMaxError = 0;

    //Obtener los datos del usuario
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"Introduzca un fichero .txt para obtener la segmentacion."<<endl;
    cout<<"Fichero: ";
    cin>>fichero;

    //Llamada al constructor
    SerieTemporal STemporal(fichero);

    //Obtener los datos del usuario
    cout<<"Introduzca el error maximo permitido."<<endl;
    cout<<"Error maximo: ";
    cin>>errorMax;
    cout<<"----------------------------------------------------------"<<endl;

    //Control de errores
    if(errorMax < 0){
        cout<<"No se pueden introducir valores negativos para el error."<<endl;
        exit(EXIT_FAILURE);
    }

    //Marcar primer y ultimo punto como dominanate
    STemporal.dominantePunto(0, true);
    STemporal.dominantePunto(STemporal.numeroPuntosSerieTemporal()-1, true);
    
    //Comprobante de puntos dominantes bien seteados
    //STemporal.mostrarPuntosDominantes();

    //Realizar pasos recursivamente
    calculoRecursivoDos(0, STemporal.numeroPuntosSerieTemporal()-1, errorMax, STemporal);
    
    //Calcular ISE
    STemporal.erroresSegmentacion(sumaErrorCuadrado, errorPuntoMax, puntoMaxError);

    //Imprimir resultados por consola
    cout<<"Numero de puntos dominantes: "<<STemporal.contarPuntosDominantes()<<endl;
    cout<<"ISE: "<<sumaErrorCuadrado<<endl;
    cout<<"Error maximo: "<<errorPuntoMax<<endl;
    cout<<"Punto error maximo: "<<puntoMaxError<<endl;

    //Guardar los datos en .txt
    STemporal.guardarSerieTemporal(save_normal);
    STemporal.guardarSegmentacion(save_dominante);

    system("./segundoMetodo.sh");

}