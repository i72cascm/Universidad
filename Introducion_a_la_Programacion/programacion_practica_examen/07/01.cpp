#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

int espacios(string cad){
	int contador=0;
	int n;
	n=cad.size();
	for (int i=0; i<n; i++){
		if (cad[i]==' '){
			contador++;
		}
	}
	return contador;
}

int main(){
	string cadena;
	int n;
	cout<<"Introduce una cadena de caracteres"<<endl;
	getline(cin,cadena);
	n=espacios(cadena);
	cout<<"Tiene "<<n<<" espacios."<<endl;

cin.ignore();
cin.get();
}

