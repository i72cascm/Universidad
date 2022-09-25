#include <iostream>
using namespace std;
int main(){
	int n,contador; //se define la variable de la cual se calculara los divisores
	cout<<"Introduzca numero."<<endl;
	cin>>n;
	contador=n;
	if (contador<=0){ //se crea un error si el numero introducido es 0 o menor que este.
		cout<<"Introduzca un numero positivo mayor que 0."<<endl;
	}
	else{
		while (contador>0){ //se crea un bucle que revisa los numeros 1 a 1 y muestra solo los divisores del numero introducido
			if (n%contador==0){
				cout<<contador<<endl;
			}
			contador=contador-1;
		}	
		cout<<"Son los divisores de "<<n<<endl;	
	}
cin.ignore();
cin.get();
}