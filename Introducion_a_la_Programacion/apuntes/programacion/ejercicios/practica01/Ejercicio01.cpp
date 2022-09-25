#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	float radio,area; //Se definen las variables radio y area
	cout<<"Introduzca el valor del radio"<<endl;
	cin >> radio;
	area=3.1415*radio*radio; //Realiza los calculos necesarios para averiguar el area
	cout<<"El area es :"<<area<<endl;
    system("pause");
}

