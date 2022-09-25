#include <iostream>
using namespace std;

int main() {
	int n,contador=1; //se define la variable del numero a conseguir sus divisores y un contador para ayudar a encontrarlos
	cout<<"Introduce numero"<<endl;
	cin>>n;
	if (n<=0){ //se crea un error si el numero introducido no es mayor que 0
		cout<<"Introduzca valores mayores que 0."<<endl;
	}
	else{
		while (contador<=n){ //se encuentran los divisores de manera ascendente
			if (n%contador==0){
				cout<<contador<<endl;
			}
		contador=contador+1;
		}
	cout<<"Son los divisores de: "<<n<<endl; //se muestra el resultado
	}
cin.ignore();
cin.get();
}