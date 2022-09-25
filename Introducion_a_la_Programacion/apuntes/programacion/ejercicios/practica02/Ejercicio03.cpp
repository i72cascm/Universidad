#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int contador, resultado=1; //se definen las variables
	cout<<"Introduzca un valor"<<endl;
	cin>>contador;
	if (contador<=0){ //se crea un error si el numero es 0 o menor que 0
		cout<<"Introduzca valores positivos."<<endl;
		}
	else {
	while (contador>0){ //se multiplica el numero por su anterior susecivamete hasta llegar a 0 (sin incluirlo)
		resultado=resultado*contador;
		contador=contador-1;
			}	
		cout<<"El resultado es: "<<resultado<<endl; //se muestra el resultado
	}	
    system("pause");
}

