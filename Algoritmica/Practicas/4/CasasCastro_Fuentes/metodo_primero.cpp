//============================================================================
// Algoritmica
// Name        : metodo_primero.cpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 8/11/2022
//============================================================================

//Includes
#include <iostream>
#include "serietemporal.hpp"
#include "ClaseTiempo.hpp"

using namespace std;

//****************************************************************************************************
//**********************************FUNCIONES LOCALES*************************************************
//****************************************************************************************************

void rellenarErrores(SerieTemporal STemporal, vector < vector < double > > &Errores);
void programacionDinamica(SerieTemporal STemporal, vector < vector < double > > &Errores, vector < vector < int > > &Padres, int npuntos);
void puntosDominantes(SerieTemporal &STemporal, int npuntos, vector < vector < int > > Padres);

//****************************************************************************************************
//****************************************************************************************************

//Algoritmo set dominantes intermedios
void puntosDominantes(SerieTemporal &STemporal, int npuntos, vector < vector < int > > Padres){
    
    //Declaracion de variables
    int rows = STemporal.numeroPuntosSerieTemporal()-1;
    int cols = npuntos - 1;

    for(cols; cols >= 0; cols --){

        STemporal.dominantePunto(Padres[rows][cols], true);
        rows = Padres[rows][cols];

    }

}

//Algoritmo de programacion dinamica
void programacionDinamica(SerieTemporal STemporal, vector < vector < double > > &Errores, vector < vector < int > > &Padres, int npuntos){

    //Declaracion de variable auxiliar
    double aux = 0.0;

    //Algoritmo
    for(int m = 1; m < npuntos; m++){
        for(int n = m; n < STemporal.numeroPuntosSerieTemporal(); n++){
            //aux con limite superior
            aux = 99999999999;
            for(int j = m - 1; j < n; j++){
                if((Errores[j][m-1] + STemporal.calcularIseEntreDosPuntos(j,n)) < aux){
                    aux = Errores[j][m-1] + STemporal.calcularIseEntreDosPuntos(j,n);
                    Padres[n][m] = j;
                    Errores[n][m] = aux;
                }
            }
        }
    }
}

//Funcion que rellena la matriz de errores
void rellenarErrores(SerieTemporal STemporal, vector < vector < double > > &Errores){

    for(int i = 1; i < STemporal.numeroPuntosSerieTemporal(); i++){
        Errores[i][0] = 99999999999;
    }

    Errores[0][0] = 0;

}

//Funcion principal
void metodo_primero(){

    //Declaración de variables
    char fichero[100];
    int npuntos = 0;
    long double sumaErrorCuadrado = 0.0, errorPuntoMax = 0.0, tiempo = 0.0;
    int puntoMaxError = 0;
    char save_normal[100] = "primerMetodo_normal.txt";
    char save_dominante[100] = "primerMetodo_dominante.txt";

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

    //Crear matriz Errores y Padres + variables post-constructor
    vector < vector <double> > Errores(STemporal.numeroPuntosSerieTemporal(), vector<double>(npuntos, 0));
    vector < vector <int> > Padres(STemporal.numeroPuntosSerieTemporal(), vector<int>(npuntos, 0));

    //Rellenar errores
    rellenarErrores(STemporal, Errores);

    //Clase tiempo (inicio)
    Clock time;
    time.start();

    //Algoritmo programacion dinamica
    programacionDinamica(STemporal, Errores, Padres, npuntos);

    //Clase tiempo (fin)
    if (time.isStarted()){
        time.stop();
    }

    //Guardar el tiempo transcurrido en el vector auxiliar
    tiempo = time.elapsed();
    tiempo = tiempo / 1000;

    //Set punto inicial y final como dominantes
    STemporal.dominantePunto(0, true);
    STemporal.dominantePunto(STemporal.numeroPuntosSerieTemporal()-1, true);

    //Set puntos dominantes calculados
    puntosDominantes(STemporal, npuntos, Padres);

    //Calcular errores
    STemporal.erroresSegmentacion(sumaErrorCuadrado, errorPuntoMax, puntoMaxError); 

    //Imprimir valores por pantalla
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"Numero de puntos dominantes: "<<STemporal.contarPuntosDominantes()<<endl;
    cout<<"ISE: "<<sumaErrorCuadrado<<endl;
    cout<<"Error maximo: "<<errorPuntoMax<<endl;
    cout<<"Punto error maximo: "<<puntoMaxError<<endl;
    cout<<"Tiempo transcurrido: "<<tiempo<<" milisegundos"<<endl;

    //Guardar los datos en .txt
    STemporal.guardarSerieTemporal(save_normal);
    STemporal.guardarSegmentacion(save_dominante);

    //GNU plot para representar las gráficas
    system("./primerMetodo.sh");
}