#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int n,resultado=0; // se define la variable que indicara hasta que numero llegara el programa+
	cout<<"Introduze numero"<<endl;
	cin>>n;
	if (n<=0) { //se crea un error en pantalla si el usuario introduce 0 o valores mas pequeños a este.
		cout<<"Introduzca valores positivos mayores que 0."<<endl;
		}
	else {
		while (n>0){ //se suman los numeros que no sean pares hasta llegar a 0
			if (n%2==!0) {
				resultado=resultado+n;
			}
		n=n-1;
		}
		cout<<"El resultado es: "<<resultado<<endl; //se muestra el resultado
	}

    system("pause");
}

