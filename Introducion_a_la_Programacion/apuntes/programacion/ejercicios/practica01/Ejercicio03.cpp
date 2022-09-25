#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;

int main(){
	float a,resultado; //Se definen las variables
	cout<<"Introduzca un valor"<<endl;
	cin >> a;
	if (a>=0) { //Para numeros mayores que 0 incluyendo a este
		resultado=sqrt(a);
		cout<<"El resultado es :"<< resultado<<endl;
	}
else { //Error para la raiz cuadrada de un numero negativo
	cout<<"No se puede realizar la raiz cuadrada de un numero negativo."<<endl;
	}
    system("pause");
}

