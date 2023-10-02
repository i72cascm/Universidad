//============================================================================
// Algoritmica
// Name        : funcionesGlobales.hpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 28/09/2022
//============================================================================

#ifndef _FUNCIONESGLOBALES_H_
#define _FUNCIONESGLOBALES_H_

#include <vector>
using namespace std;

double media(const vector<double> &vect);

void saveTotxt(const vector<double>& tiemporReales, const vector<double>& numeroElementos);

double sumatorio(const vector<double> &numeroElementos, const vector<double> &tiemposReales, int exp1, int exp2);

double calcularCoeficienteDeterminacion(const vector<double>& tiemposReales, const vector<double>& tiemposEstimados);

double varianza(const vector<double>& vect);

void rellenarMatriz(vector < vector < double > >& matrizDatos, int opRellenar);

#endif