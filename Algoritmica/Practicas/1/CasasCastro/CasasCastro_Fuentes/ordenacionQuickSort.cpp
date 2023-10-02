//============================================================================
// Algoritmica
// Name        : ordenacionQuickSort.cpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 26/09/2022
//============================================================================

//Includes
#include <bits/stdc++.h>

#include "sistemaEcuaciones.hpp"
#include "ClaseTiempo.hpp"
#include "funcionesGlobales.hpp"

using namespace std;

//****************************************************************************************************
//**********************************FUNCIONES LOCALES*************************************************
//****************************************************************************************************
void ordenacionQuickSort();
void tiemposOrdenacionQuickSort(int nMin, int nMax, int incremento, int repeticiones, vector<double>& tiemposReales, vector<double>& numeroElementos);
void rellenarVector(vector<int>&v);
void rellenarVector(vector<int>& v);
//bool estaOrdenado(const vector<int>& v);
void ajusteNlogN(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<double>& a);
double sumatorio(const vector<double> &numeroElementos, const vector<double> &tiemposReales, int exp1, int exp2);
double media(const vector<double> &vect);
void calcularTiemposEstimadosNlogN(const vector<double>& numeroElementos, const vector<double>& a, vector<double>& tiemposEstimados);
double varianza(const vector<double>& vect);
void saveTotxtFinalQuickSort(const vector<double>& tiemporReales, const vector<double>& numeroElementos, const vector<double>& tiemposEstimados);
double calcularTiempoEstimadoNlogN(const double &n, const vector <double> &a);
//****************************************************************************************************
//****************************************************************************************************



double calcularTiempoEstimadoNlogN(const double &n, const vector <double> &a){

    //Declaracion del resultado
    double estimacion = 0.0;

    //Calculo del tiempo estimado
    estimacion = a[0] + a[1]*n*log(n);

    return estimacion;

}

void saveTotxtFinalQuickSort(const vector<double>& tiemporReales, const vector<double>& numeroElementos, const vector<double>& tiemposEstimados){

    //Declarar y abrir el fichero .txt
    fstream file;
    file.open("datosFinalesQuickSort.txt",ios_base::out);

    //Bucle para almacenar los datos
    for(int i=0;i<numeroElementos.size();i++)
    {
        file<<numeroElementos[i]<<" "<<tiemporReales[i]<<" "<<tiemposEstimados[i]<<endl;
    }

    //Cerrar fichero
    file.close();
}

void calcularTiemposEstimadosNlogN(const vector<double>& numeroElementos, const vector<double>& a, vector<double>& tiemposEstimados){

    //Calculo de tiempos estimados
    for(int i = 0; i < numeroElementos.size(); i++){
        tiemposEstimados.push_back(a[0] + a[1]*numeroElementos[i]*log(numeroElementos[i]));
    }

}

void ajusteNlogN(const vector<double> &numeroElementos, const vector<double> &tiemposReales, vector<double>& a){

    //Declaracion de variables principales
    vector < vector <double> > A(2, vector<double>(2, 0));
    vector < vector <double> > B(2, vector<double>(1, 0));
    int n = 2;
    vector < vector <double> > X(2, vector<double>(1, 0));

    //Declaracion de variables auxiliares
    vector<double> cambioVariable(numeroElementos.size(),0);

    //Cambio de variable
    for(int i = 0; i < numeroElementos.size(); i++){
        cambioVariable[i] = numeroElementos[i]*log(numeroElementos[i]);
    }

    //Rellenar matriz A
    A[0][0] = numeroElementos.size();
    A[0][1] = sumatorio(cambioVariable, tiemposReales, 1, 0);
    A[1][0] = sumatorio(cambioVariable, tiemposReales, 1, 0);
    A[1][1] = sumatorio(cambioVariable, tiemposReales, 2, 0);

    //Rellenar matriz B
    B[0][0] = sumatorio(cambioVariable, tiemposReales, 0, 1);
    B[1][0] = sumatorio(cambioVariable, tiemposReales, 1, 1);

    //Resolver sistema
    resolverSistemaEcuaciones(A, B, n, X);

    //Rellenamos la matriz de coeficientes
    a[0] = X[0][0];
    a[1] = X[1][0];

}

//bool estaOrdenado(const vector<int>& v){
//
//    for(int i = 0; i < v.size()-1; i++){
//        if(v[i] > v[i+1]){
//            return false;
//        }
//    }
//    return true;
//}

void rellenarVector(vector<int>& v){
    
    
    //Rellenar vector
    for (int i = 0; i < v.size(); i++){
        v[i] = rand() % 9999999;
    }

    //Comprobacion
    //for(int i = 0; i < v.size(); i++){
    //    cout<<v[i]<<endl;
    //}
}

void tiemposOrdenacionQuickSort(int nMin, int nMax, int incremento, int repeticiones, vector<double>& tiemposReales, vector<double>& numeroElementos){

    //Desde minimo hasta maximo, utilizando el incremento
    for(int i = nMin; i <= nMax; i = i + incremento){
        
        //Declaracion de vector auxiliar para guardar tiempos y hacer media
        vector<double> tiemposAux(repeticiones, 0);

        //Repeticiones por cada valor de n
        for(int j = 0; j < repeticiones; j++){

            //Inicializar vector de n elementos con valores a 0
            vector<int> vect(i, 0);

            //Rellenar vector con valores aleatorios entre 0 y 9999999
            rellenarVector(vect);

            //Clase tiempo (inicio)
            Clock time;
            time.start();

            //Ordenar el vector con la funcion sort de la STL
            sort(vect.begin(), vect.end());

            //Clase tiempo (fin)
            if (time.isStarted()){
                time.stop();
            }

            //Guardar el tiempo transcurrido en el vector auxiliar
            tiemposAux[j] = time.elapsed();

            //Comprobar si el vector esta bien ordenado
            //bool sorted = estaOrdenado(vect);
            //if(sorted){
            //    cout<<"Esta ordenado."<<endl;
            //}else{
            //    cout<<"No esta ordenado."<<endl;
            //}
        }

        //Realizamos la media de los tiempos obtenidos para el valor de n
        double mean = media(tiemposAux);

        //Guardamos los datos en los vectores de tiemposReales y numeroElementos
        tiemposReales.push_back(mean);
        numeroElementos.push_back(i);

    }

    //Comprobar que los vectores tienen los datos bien guardados
    //for(int i = 0; i < tiemposReales.size(); i++){
    //    cout<<"Para el valor de "<<numeroElementos[i]<<" elementos, el tiempo medio es: "<<tiemposReales[i]<<"."<<endl;
    //}
}

void ordenacionQuickSort(){
    
    //Declaracion de variables
    int minimo = 0, maximo = 0, incremento = 0, repeticiones = 0;
    long long int years = 0, days = 0, hours = 0, minutes = 0, seconds = 0, estimacionInt = 0; 
    double coeDeterminacion = 0.0, estimacionIndividual = 0.0, estimacion = 0.0;
    vector <double> tiemposReales;
    vector <double> numeroElementos;
    vector <double> a(2,0);
    vector <double> tiemposEstimados;

    //Inicializar semilla para generar numeros aleatorios
    srand(time(NULL));

    //Pedir datos al usuario
    cout<<"Introduzca el valor minimo del numero de elementos del vector."<<endl;
    cout<<"Minimo: ";
    cin>>minimo;

    cout<<"Introduzca el valor maximo del numero de elementos del vector."<<endl;
    cout<<"Maximo: ";
    cin>>maximo;

    if (minimo > maximo){
        cout<<"Error: El valor minimo no puede ser mayor que maximo."<<endl;
        exit(EXIT_FAILURE);
    }

    cout<<"Introduzca el incremento del valor del numero de elementos."<<endl;
    cout<<"Incremento: ";
    cin>>incremento;

    cout<<"Introduzca el numero de veces que se repetira la ordenacion para cada valor del numero de elementos."<<endl;
    cout<<"Repeticiones: ";
    cin>>repeticiones;

    //Calcular los tiempos y guardarlos en vectores con su respectivo numero de elementos
    tiemposOrdenacionQuickSort(minimo, maximo, incremento, repeticiones, tiemposReales, numeroElementos);

    //Guardar los valores de los vectores en un fichero .txt
    saveTotxt(tiemposReales, numeroElementos);

    //Calcular los coeficientes y generar la funcion ajustada
    ajusteNlogN(numeroElementos, tiemposReales, a);
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"Función ajustada: t(n) = "<<a[0]<<" + "<<a[1]<<"*nlog(n)"<<endl;
    cout<<"----------------------------------------------------------"<<endl;

    //Calcular tiempos estimados
    calcularTiemposEstimadosNlogN(numeroElementos, a, tiemposEstimados);

    //Calcular coeficiente de determinacion
    coeDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"Coeficiente de determinacion: "<<coeDeterminacion<<endl;
    cout<<"----------------------------------------------------------"<<endl;

    //Guardar los valores de los vectores en un fichero .txt
    saveTotxtFinalQuickSort(tiemposReales, numeroElementos, tiemposEstimados);

    //Llamada al script gnuplot para calcular la grafica
    system("./quicksort_gnuplot.sh");

    //Pedir si se desea introducir tiempos estimados
    do{

        cout<<"Si desea obtener la estimacion del tiempo de un determinado tamaño de n, por favor introduzcalo."<<endl;
        cout<<"En caso de querer abandonar el programa, pulse 0."<<endl;
        cout<<"Valor: ";
        cin>>estimacionIndividual;

        if (estimacionIndividual > 0){

        estimacion = calcularTiempoEstimadoNlogN(estimacionIndividual, a);

            estimacionInt = (long long int)estimacion;
            years = estimacionInt / (365LL*24LL*60LL*60LL*1000000LL);
            days = (estimacionInt / (24LL*60LL*60LL*1000000LL)) % 365LL;
            hours = (estimacionInt / (60LL*60LL*1000000LL)) % 24LL;
            minutes = (estimacionInt / (60LL*1000000LL)) % 60LL;
            seconds = (estimacionInt / 1000000LL) % 60LL;


            cout<<"----------------------------------------------------------"<<endl;
            cout<<"Para un vector de "<<estimacionIndividual<<" elementos, el tiempo estimado seria: "<<years<<" años, "<<days<<" dias, "<<hours<<" horas, "<<minutes<<" minutos y "<<seconds<<" segundos."<<endl;
            cout<<"----------------------------------------------------------"<<endl;
        }

    }while(estimacionIndividual > 0);

}