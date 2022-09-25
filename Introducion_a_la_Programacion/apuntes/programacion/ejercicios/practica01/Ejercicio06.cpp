#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	float a,b,c,d,resultado; //Se definen 4 variables para introducir numeros y otra que mostrara el resultado
	cout<<"Introduzca 4 numeros para realizar media"<<endl;
	cin >> a;
	cin >> b;
	cin >> c;
	cin >> d;
	resultado=(a+b+c+d)/4; //Se define el operador que mostrara el resultado
	cout<<"El resultado es: "<<resultado<<endl; //Se muestra el resultado
	
    system("pause");
}

