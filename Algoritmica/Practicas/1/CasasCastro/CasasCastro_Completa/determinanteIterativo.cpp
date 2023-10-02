//============================================================================
// Algoritmica
// Name        : determinanteIterativo.cpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 28/09/2022
//============================================================================

//Includes
#include <iostream>
#include <bits/stdc++.h>

#include "sistemaEcuaciones.hpp"
#include "ClaseTiempo.hpp"
#include "funcionesGlobales.hpp"

using namespace std;

//****************************************************************************************************
//**********************************FUNCIONES LOCALES*************************************************
//****************************************************************************************************

void tiemposDeterminanteIterativo(int nMin, int nMax, int incremento, int opRellenar, vector<double>& tiemposReales, vector<double>& numeroElementos);
void inicializarInversa(vector < vector < double > >  &inversa);
void trianguloInferior(vector < vector < double > > &A, vector < vector < double > > &inversa);
bool eliminarCero(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x);
void hacerCerosColumna(vector < vector < double > > &A, vector < vector < double > > &inversa, unsigned int x);
void combinarFilas(vector < vector < double > > &matriz, unsigned int filaOrigen, double factor, unsigned int filaDestino);
double productoDiagonal(const vector < vector < double > > &matriz);
void ajustePolinomico(const vector <double>& numeroElementos, const vector <double>& tiemposReales, vector <double>& a);
void calcularTiemposEstimadosPolinomico(const vector<double>& numeroElementos, const vector<double>& a, vector<double>& tiemposEstimados);
void saveTotxtFinalDeterminanteIterativo(const vector<double>& tiemporReales, const vector<double>& numeroElementos, const vector<double>& tiemposEstimados);
double calcularTiempoEstimadoPolinomico(const double &n, const vector <double> &a);

//****************************************************************************************************
//****************************************************************************************************

double calcularTiempoEstimadoPolinomico(const double &n, const vector <double> &a){

    //Declaracion del resultado
    double estimacion = 0.0;

    //Calculo del tiempo estimado
    estimacion = a[0] + a[1]*n + a[2]*pow(n,2) + a[3]*pow(n,3);

    return estimacion;

}

void saveTotxtFinalDeterminanteIterativo(const vector<double>& tiemporReales, const vector<double>& numeroElementos, const vector<double>& tiemposEstimados){

    //Declarar y abrir el fichero .txt
    fstream file;
    file.open("datosFinalesDeterminanteIterativo.txt",ios_base::out);

    //Bucle para almacenar los datos
    for(int i=0;i<numeroElementos.size();i++)
    {
        file<<numeroElementos[i]<<" "<<tiemporReales[i]<<" "<<tiemposEstimados[i]<<endl;
    }

    //Cerrar fichero
    file.close();
}

void calcularTiemposEstimadosPolinomico(const vector<double>& numeroElementos, const vector<double>& a, vector<double>& tiemposEstimados){

    //Calculo de tiempos estimados
    for(int i = 0; i < numeroElementos.size(); i++){
        tiemposEstimados.push_back(a[0] + a[1]*numeroElementos[i] + a[2]*pow(numeroElementos[i],2) + a[3]*pow(numeroElementos[i],3));
    }

}

void ajustePolinomico(const vector <double>& numeroElementos, const vector <double>& tiemposReales, vector <double>& a){

    //Declaracion de variables principales
    vector < vector <double> > A(4, vector<double>(4, 0));
    vector < vector <double> > B(4, vector<double>(1, 0));
    int n = 4;
    vector < vector <double> > X(4, vector<double>(1, 0));

    //Rellenar matriz A
    A[0][0] = numeroElementos.size();
    A[0][1] = sumatorio(numeroElementos, tiemposReales, 1, 0);
    A[0][2] = sumatorio(numeroElementos, tiemposReales, 2, 0);
    A[0][3] = sumatorio(numeroElementos, tiemposReales, 3, 0);
    A[1][0] = sumatorio(numeroElementos, tiemposReales, 1, 0);
    A[1][1] = sumatorio(numeroElementos, tiemposReales, 2, 0);
    A[1][2] = sumatorio(numeroElementos, tiemposReales, 3, 0);
    A[1][3] = sumatorio(numeroElementos, tiemposReales, 4, 0);
    A[2][0] = sumatorio(numeroElementos, tiemposReales, 2, 0);
    A[2][1] = sumatorio(numeroElementos, tiemposReales, 3, 0);
    A[2][2] = sumatorio(numeroElementos, tiemposReales, 4, 0);
    A[2][3] = sumatorio(numeroElementos, tiemposReales, 5, 0);
    A[3][0] = sumatorio(numeroElementos, tiemposReales, 3, 0);
    A[3][1] = sumatorio(numeroElementos, tiemposReales, 4, 0);
    A[3][2] = sumatorio(numeroElementos, tiemposReales, 5, 0);
    A[3][3] = sumatorio(numeroElementos, tiemposReales, 6, 0);

    //Rellenar matriz B
    B[0][0] = sumatorio(numeroElementos, tiemposReales, 0, 1);
    B[1][0] = sumatorio(numeroElementos, tiemposReales, 1, 1);
    B[2][0] = sumatorio(numeroElementos, tiemposReales, 2, 1);
    B[3][0] = sumatorio(numeroElementos, tiemposReales, 3, 1);

    //Resolvemos el sistema
    resolverSistemaEcuaciones(A, B, n, X);

    //Rellenamos la matriz de coeficientes
    a[0] = X[0][0];
    a[1] = X[1][0];
    a[2] = X[2][0];
    a[3] = X[3][0];
}

void tiemposDeterminanteIterativo(int nMin, int nMax, int incremento, int opRellenar, vector<double>& tiemposReales, vector<double>& numeroElementos){

    //Variables auxiliares
    double aux = 0.0;

    //Desde minimo hasta maximo, utilizando el incremento
    for(int i = nMin; i <= nMax; i = i + incremento){
    
        //Inicializar matriz de orden n tipo double
        vector < vector < double > > matrizDatos;
        matrizDatos = vector< vector< double > >(i, vector< double >(i));
        vector < vector < double > > inversa; 
	    inversa = vector< vector< double > >(matrizDatos.size(), vector< double >(matrizDatos.size())); 
        double determinante = 0.0; 
        
        //Rellenamos la matriz
        rellenarMatriz(matrizDatos, opRellenar);

        //Clase tiempo (inicio)
        Clock time;
        time.start();
    
        //Realizar el determinante iterativo
        //Inicializamos la matriz inversa
	    inicializarInversa(inversa);

        //Se triangulariza la matriz por debajo de la diagonal
        trianguloInferior(matrizDatos, inversa);
        
        //Mostramos determinante
        determinante = productoDiagonal(matrizDatos);

        //Comprobar que el determinante esta bien
        //cout<<"Determinante: "<<determinante<<endl;

        //Clase tiempo (fin)
        if (time.isStarted()){
            time.stop();
        }

        //Guardar el tiempo transcurrido
        aux = time.elapsed();

        //Guardamos los datos en los vectores de tiemposReales y numeroElementos
        tiemposReales.push_back(aux);
        numeroElementos.push_back(i);

    }

}

void determinanteIterativo(){

    //Declaracion de variables
    int minimo = 0, maximo = 0, incremento = 0, opRellenar = 0;
    long long int years = 0, days = 0, hours = 0, minutes = 0, seconds = 0, estimacionInt = 0;
    double coeDeterminacion = 0.0, estimacionIndividual = 0.0, estimacion = 0.0;
    vector <double> tiemposReales;
    vector <double> numeroElementos;
    vector <double> a(4,0);
    vector <double> tiemposEstimados;

    //Inicializar semilla para generar numeros aleatorios
    srand(time(NULL));

    //Pedir datos al usuario
    cout<<"Introduzca el orden minimo de la matriz."<<endl;
    cout<<"Minimo: ";
    cin>>minimo;

    cout<<"Introduzca el orden maximo de la matriz."<<endl;
    cout<<"Maximo: ";
    cin>>maximo;

    if (minimo > maximo){
        cout<<"Error: El valor minimo no puede ser mayor que maximo."<<endl;
        exit(EXIT_FAILURE);
    }

    cout<<"Introduzca el incremento del orden de la matriz."<<endl;
    cout<<"Incremento: ";
    cin>>incremento;

    do{    
        cout<<"¿Desea rellenar las matrices a mano?"<<endl;
        cout<<"1- NO"<<endl;
        cout<<"2- SI"<<endl;
        cout<<"Opcion: ";
        cin>>opRellenar;
    }while((opRellenar < 1) || (opRellenar > 2));

    //Calcular los tiempos y guardarlos
    tiemposDeterminanteIterativo(minimo, maximo, incremento, opRellenar, tiemposReales, numeroElementos);

    //Guardar los valores de los vectores en un fichero .txt
    saveTotxt(tiemposReales, numeroElementos);

    //Calcular los coeficientes
    ajustePolinomico(numeroElementos, tiemposReales, a);
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"Función ajustada: t(n) = "<<a[0]<<" + "<<a[1]<<"*n + "<<a[2]<<"*n^2 + "<<a[3]<<"*n^3"<<endl;
    cout<<"----------------------------------------------------------"<<endl;

    //Calcular tiempos estimados
    calcularTiemposEstimadosPolinomico(numeroElementos, a, tiemposEstimados);

    //Calcular coeficiente de determinacion
    coeDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"Coeficiente de determinacion: "<<coeDeterminacion<<endl;
    cout<<"----------------------------------------------------------"<<endl;

    //Guardar los valores a un txt
    saveTotxtFinalDeterminanteIterativo(tiemposReales, numeroElementos, tiemposEstimados);

    //Llamada al script gnuplot para calcular la grafica
    system("./determinanteIterativo_gnuplot.sh");

    //Pedir si se desea introducir tiempos estimados
    do{

        cout<<"Si desea obtener la estimacion del tiempo de un determinado tamaño de n, por favor introduzcalo."<<endl;
        cout<<"En caso de querer abandonar el programa, pulse 0."<<endl;
        cout<<"Valor: ";
        cin>>estimacionIndividual;

        if (estimacionIndividual > 0){

        estimacion = calcularTiempoEstimadoPolinomico(estimacionIndividual, a);

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