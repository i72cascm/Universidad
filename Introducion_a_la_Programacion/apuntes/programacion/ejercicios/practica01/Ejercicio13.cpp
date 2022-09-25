#include <iostream>
#include <cstdio>
using namespace std;

int main(){

 int n; //se define la variable numero
	cout<<"Introduzca un numero"<<endl;
	cin >> n;
	if (n%2==0) { //averiguamos si es par o impar y se muestra el resultado
	cout<<"El numero es par."<<endl;
	}
	else {
	cout<<"El numero es impar."<<endl;
	}
cin.ignore();
cin.get();
}