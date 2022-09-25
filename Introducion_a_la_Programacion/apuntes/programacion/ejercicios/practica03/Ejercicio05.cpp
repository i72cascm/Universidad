#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
int n,contador; //se crean las variables
	cout <<"Introduce numero"<<endl;
	cin>>n;
	if (n<=0) { //se crea un error si el numero introducido es 0 o menor
		cout<<"Introduzca valores mayores que 0."<<endl;
	}
	else{
		for (contador=1;contador<=n;contador++){ //mediante el for se averiguan los divisores del numero y se van mostrando en orden ascendente
			if (n%contador==0){
				cout<<contador<<endl;
			}
		}
	cout<<"Son los divisores de: "<<n<<endl;
	}
    system("pause");
}

