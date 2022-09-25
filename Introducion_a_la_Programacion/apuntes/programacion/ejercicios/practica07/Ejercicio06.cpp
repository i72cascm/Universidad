#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;
string concatena(string a, string b){ //la funcion concatena unira dos cadenas introducidas en una sola
	a=a+b; 
	return a;
}

int main(){
	string cad1, cad2, a; //se pide la cadena 1 y 2
	cout<<"Introduzca una cadena de caracteres."<<endl;
	getline(cin,cad1);
	cout<<"Introduzca segunda cadena."<<endl;
	getline(cin,cad2);
	a=concatena(cad1,cad2); //se llama a la funcion para realizar la union
	cout<<"El resultado es: "<<a<<endl; //se muestra el resultado

    system("pause");
}

