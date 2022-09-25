#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

void convierte_a_mayuscula(string& cad){
	int n=cad.size();
	for (int i=0;i<n;i++){
		cad[i]=toupper(cad[i]);
	}
}

int main(){
	string cadena;
	cout<<"Introduzca cadena"<<endl;
	getline(cin,cadena);
	convierte_a_mayuscula(cadena);
	cout<<cadena<<endl;

cin.ignore();
cin.get();
}

