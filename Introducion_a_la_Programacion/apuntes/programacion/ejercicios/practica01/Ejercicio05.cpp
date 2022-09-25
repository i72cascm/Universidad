#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int n; //Se define la variable para situar el valor numerico
	cout<<"Introduce valor numerico entero"<<endl;
	cin >> n;
	if (n>0) {cout<<"El numero es mayor que 0"<<endl; }//Se asigna una respuesta en funcion del valor aportado a la variable
	else {
		if (n==0) {cout<<"El numero es 0"<<endl; }
		else {cout<<"El numero es menor que 0 "; }
		}

    system("pause");
}

