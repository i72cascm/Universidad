#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	float practica, parcial, final, resultado; //Se definen las variables a usar
	cout<<"Introduzca nota practica y parcial"<<endl;
	cin >> practica;
	cin >> parcial;
	cout<<"Introduzca nota del examen final"<<endl;
	cin >> final;
	resultado=parcial*0.25+practica*0.25+final*0.5;//Se introducen los valores y se calcula la nota final
	cout<<"La nota final es : "<<resultado<<endl;//Se muestra la nota final
    system("pause");
}

