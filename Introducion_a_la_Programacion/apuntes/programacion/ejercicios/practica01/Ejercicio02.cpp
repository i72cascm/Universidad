#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	float grados,radianes; //Se define las variables a convertir
	cout<<"Introduce el angulo en grados para convertir"<<endl;
	cin >> grados;
	radianes=grados*3.1415/180; //Se realizan las operaciones matematicas para convertir grados en radianes
	cout<<radianes<<" radianes"<<endl;
    system("pause");
}

