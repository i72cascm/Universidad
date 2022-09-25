#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

int main(){
	float a, b, c, d, resultado; //se definen las variables de posicion y el resultado
	cout<<"Intoduzca primera coordenada"<<endl; //Se pide que el usuario introduzca las coordenadas
	cin >> a;
	cin >>c;
	cout<<"Intduzca la segunda coordenada"<<endl;
	cin >> b;
	cin >> d;
	b=b-a; //se calcula la distancia de un punto a otro.
	d=d-c;
	resultado=sqrt(pow(b,2)+pow(d,2));
	cout<<"El resultado es: "<<resultado<<endl; //se muestra el resultado

    system("pause");
}

