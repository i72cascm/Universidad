#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;

int main(){
	float numero,resultado;
	cout<<"Introduzca numero"<<endl;
	cin>>numero;
	if (numero>=0){
		resultado=sqrt(numero);
		cout<<resultado<<endl;
	}
	else{
		cout<<"Introduzca un numero mayor que o igual a 0"<<endl;
	}

cin.ignore();
cin.get();
}

