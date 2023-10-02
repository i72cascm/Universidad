//============================================================================
// Algoritmica
// Name        : funcionesGlobales.cpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 28/09/2022
//============================================================================

//Includes
#include <fstream>
#include <iostream>
#include <math.h>
#include "funcionesGlobales.hpp"

using namespace std;

void rellenarMatriz(vector < vector < double > >& matrizDatos, int opRellenar){

    //Declaracion de variables
    int orden = 0;
    float aux = 0.0;

    //Obtencion del orden de la matriz
    orden = matrizDatos.size();

    //Rellenar matriz dependiendo de la opcion elegida 
    if(opRellenar == 1){
       
        //Valores aleatorios
        for(int i = 0; i < orden; i++){
            for(int j = 0; j < orden; j++){
                matrizDatos[i][j] = 0.95 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.05-0.95)));
            }
        }

    }else{
            
        //A mano
        for(int i = 0; i < orden; i++){
            for(int j = 0; j < orden; j++){
                cout<<"Introduzca posicion ["<<i<<"]["<<j<<"]: "<<endl;
                cin>>aux;
                matrizDatos[i][j] = aux;
            }
        }

    }

    //Print matrix
    //for(int i = 0; i < orden; i++){
    //    for(int j = 0; j < orden; j++){
    //        cout<<"Posicion["<<i<<"]["<<j<<"]: "<<matrizDatos[i][j]<<endl;;
    //    }
    //}

}

double media(const vector<double> &vect){

    double result = 0.0; 

    for(int i = 0; i < vect.size(); i++){
        result += vect[i];
    }

    result = result / vect.size();

    return result;

}

double varianza(const vector<double>& vect){

    //Declaracion de varianza
    double result = 0.0;
    double mean = media(vect);

    //Calculo de varianza
    for(int i = 0; i < vect.size(); i++){
        result += ((vect[i]-mean)*(vect[i]-mean));
    }

    result = result / vect.size();

    return result;

}

double calcularCoeficienteDeterminacion(const vector<double>& tiemposReales, const vector<double>& tiemposEstimados){

    //Declaracion de variables
    double varTiemposReales = 0.0;
    double varTiemposEstimados = 0.0;
    double result = 0.0;
    
    //Calculo de varianzas
    varTiemposReales = varianza(tiemposReales);
    varTiemposEstimados = varianza(tiemposEstimados);
    result = varTiemposEstimados / varTiemposReales;

    return result;
    
}

double sumatorio(const vector<double> &numeroElementos, const vector<double> &tiemposReales, int exp1, int exp2){

    //Declaracion del sumatorio
    double result = 0;

    //Sumatorio
	for(int i=0; i<numeroElementos.size();i++){
		result += (pow(numeroElementos[i],exp1)*pow(tiemposReales[i],exp2));
	}

	return result;

}

void saveTotxt(const vector<double>& tiemporReales, const vector<double>& numeroElementos){

    //Declarar y abrir el fichero .txt
    fstream file;
    file.open("tiempoReales.txt",ios_base::out);

    //Bucle para almacenar los datos
    for(int i=0;i<numeroElementos.size();i++)
    {
        file<<numeroElementos[i]<<": "<<tiemporReales[i]<<endl;
    }

    //Cerrar fichero
    file.close();
}