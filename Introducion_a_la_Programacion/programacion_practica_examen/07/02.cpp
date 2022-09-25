#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

int digitos(string cad){
	int contador=0;
	int n=cad.size();
	for (int i=0;i<n;i++){
		if (isdigit(cad[i])){
			contador++;
		}
	}
	return contador;
}

int main(){
	string cadena;
	int n;
	cout<<"Introduzca una cadena"<<endl;
	getline(cin,cadena);
	n=digitos(cadena);
	cout<<"La cadena tiene: "<<n<<" digitos."<<endl;

cin.ignore();
cin.get();
}

