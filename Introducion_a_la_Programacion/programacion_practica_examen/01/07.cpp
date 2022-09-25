#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	float practica,parcial,final,resultado;
	cout<<"Introduzca nota de practicas"<<endl;
	cin>>practica;
	cout<<"Introduzca nota parcial"<<endl;
	cin>>parcial;
	cout<<"Introduzca la nota del examen final"<<endl;
	cin>>final;
	resultado=(practica*0.25)+(parcial*0.25)+(final*0.5);
	cout<<"La nota final es: "<<resultado<<endl;
cin.ignore();
cin.get();
}

