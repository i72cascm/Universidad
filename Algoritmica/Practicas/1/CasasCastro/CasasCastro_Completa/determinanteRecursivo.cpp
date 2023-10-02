//============================================================================
// Algoritmica
// Name        : main.cpp
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

void tiemposDeterminanteRecursivo(int nMin, int nMax, int incremento, int opRellenar, vector<double>& tiemposReales, vector<double>& numeroElementos);
double calculoDeterminanteRecursivo(vector < vector < double > >& matrizDatos, int n);
void getCofactor(vector < vector < double > >& matrizDatos, vector < vector < double > >& temp, int p, int q, int n);
void ajusteFactorial(const vector <double>& numeroElementos, const vector <double>& tiemposReales, vector <double>& a);
long double factorial(double n);
void calcularTiemposEstimadosFactorial(const vector<double>& numeroElementos, const vector<double>& a, vector<double>& tiemposEstimados);
void saveTotxtFinalDeterminanteRecursivo(const vector<double>& tiemporReales, const vector<double>& numeroElementos, const vector<double>& tiemposEstimados);
long double calcularTiempoEstimadoFactorial(const double &n, const vector <double> &a);

//****************************************************************************************************
//****************************************************************************************************

long double calcularTiempoEstimadoFactorial(const double &n, const vector <double> &a){

    //Declaracion del resultado
    long double estimacion = 0.0;
    long double primerCoef = (long double)a[0];
    long double segundoCoef = (long double)a[1];

    //Calculo del tiempo estimado
    estimacion = primerCoef + segundoCoef*factorial(n);

    return estimacion;

}

void saveTotxtFinalDeterminanteRecursivo(const vector<double>& tiemporReales, const vector<double>& numeroElementos, const vector<double>& tiemposEstimados){

    //Declarar y abrir el fichero .txt
    fstream file;
    file.open("datosFinalesDeterminanteRecursivo.txt",ios_base::out);

    //Bucle para almacenar los datos
    for(int i=0;i<numeroElementos.size();i++)
    {
        file<<numeroElementos[i]<<" "<<tiemporReales[i]<<" "<<tiemposEstimados[i]<<endl;
    }

    //Cerrar fichero
    file.close();
}

void calcularTiemposEstimadosFactorial(const vector<double>& numeroElementos, const vector<double>& a, vector<double>& tiemposEstimados){

    //Calculo de tiempos estimados
    for(int i = 0; i < numeroElementos.size(); i++){
        tiemposEstimados.push_back(a[0] + a[1]*factorial(numeroElementos[i]));
    }

}

long double factorial(double n){

    //Declaracion de variables
    long long int fact = 1;

    for(int i = 1; i <= n; i++){
        fact = fact*i;
    }

    long double result = (long double)fact;

    return result;

}

void ajusteFactorial(const vector <double>& numeroElementos, const vector <double>& tiemposReales, vector <double>& a){

   //Declaracion de variables principales
    vector < vector <double> > A(2, vector<double>(2, 0));
    vector < vector <double> > B(2, vector<double>(1, 0));
    int n = 2;
    vector < vector <double> > X(2, vector<double>(1, 0));

    //Declaracion de variables auxiliares
    vector<double> cambioVariable(numeroElementos.size(),0);

    //Cambio de variable
    for(int i = 0; i < numeroElementos.size(); i++){
        cambioVariable[i] = factorial(numeroElementos[i]);
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

void getCofactor(vector < vector < double > >& matrizDatos, vector < vector < double > >& temp, int p, int q, int n){
    int i = 0, j = 0;
 
    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those
            //  element which are not in given row and
            //  column
            if (row != p && col != q)
            {
                temp[i][j++] = matrizDatos[row][col];
 
                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double calculoDeterminanteRecursivo(vector < vector < double > >& matrizDatos, int n){
    
    //Algoritmo sacado del foro geeksforgeeks
    float D = 0.0; // Initialize result
 
    //  Base case : if matrix contains single element
    if (n == 1)
        return matrizDatos[0][0];
 
    vector < vector < double > > temp;
    temp = vector< vector< double > >(n, vector< double >(n));
    //int temp[n][n]; // To store cofactors
 
    int sign = 1; // To store sign multiplier
 
    // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of mat[0][f]
        getCofactor(matrizDatos, temp, 0, f, n);
        D += sign * matrizDatos[0][f] * calculoDeterminanteRecursivo(temp, n - 1);
 
        // terms are to be added with alternate sign
        sign = -sign;
    }
 
    return D;
}

void tiemposDeterminanteRecursivo(int nMin, int nMax, int incremento, int opRellenar, vector<double>& tiemposReales, vector<double>& numeroElementos){

    //Variables auxiliares
    double aux = 0.0;

    //Desde minimo hasta maximo, utilizando el incremento
    for(int i = nMin; i <= nMax; i = i + incremento){
    
        //Inicializar matriz de orden n tipo double
        vector < vector < double > > matrizDatos;
        matrizDatos = vector< vector< double > >(i, vector< double >(i));
        double determinante = 0.0; 
        
        //Rellenamos la matriz
        rellenarMatriz(matrizDatos, opRellenar);
        
        //Clase tiempo (inicio)
        Clock time;
        time.start();
    
        //Calcular determinante a partir 
        determinante = calculoDeterminanteRecursivo(matrizDatos, matrizDatos.size());

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

void determinanteRecursivo(){
    
    //Declaracion de variables
    int minimo = 0, maximo = 0, incremento = 0, opRellenar = 0;
    long long int years = 0, days = 0, hours = 0, minutes = 0, seconds = 0, estimacionInt = 0;
    double coeDeterminacion = 0.0;
    long double estimacionIndividual = 0.0, estimacion = 0.0;
    vector <double> tiemposReales;
    vector <double> numeroElementos;
    vector <double> a(2,0);
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
    tiemposDeterminanteRecursivo(minimo, maximo, incremento, opRellenar, tiemposReales, numeroElementos);

    //Guardar los valores de los vectores en un fichero .txt
    saveTotxt(tiemposReales, numeroElementos);

    //Calcular los coeficientes
    ajusteFactorial(numeroElementos, tiemposReales, a);
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"Función ajustada: t(n) = "<<a[0]<<" + "<<a[1]<<"*n!"<<endl;
    cout<<"----------------------------------------------------------"<<endl;

    //Calcular tiempos estimados
    calcularTiemposEstimadosFactorial(numeroElementos, a, tiemposEstimados);

    //Calcular coeficiente de determinacion
    coeDeterminacion = calcularCoeficienteDeterminacion(tiemposReales, tiemposEstimados);
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"Coeficiente de determinacion: "<<coeDeterminacion<<endl;
    cout<<"----------------------------------------------------------"<<endl;

    //Guardar los valores de los vectores en un fichero .txt
    saveTotxtFinalDeterminanteRecursivo(tiemposReales, numeroElementos, tiemposEstimados);

    //Llamada al script gnuplot para calcular la grafica
    system("./determinanteRecursivo_gnuplot.sh");

    //Pedir si se desea introducir tiempos estimados
    do{

        cout<<"Si desea obtener la estimacion del tiempo de un determinado tamaño de n, por favor introduzcalo."<<endl;
        cout<<"En caso de querer abandonar el programa, pulse 0."<<endl;
        cout<<"Valor: ";
        cin>>estimacionIndividual;

        if (estimacionIndividual > 0){

        estimacion = calcularTiempoEstimadoFactorial(estimacionIndividual, a);

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