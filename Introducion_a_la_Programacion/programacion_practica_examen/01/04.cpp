#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int n;
	cout<<"Introduzca numero"<<endl;
	cin>>n;
	if ((n>=1)&&(n<=7)) {
		if (n==1){
			cout<<"Lunes, laboral"<<endl;
		}
		if (n==2){
			cout<<"Mates, laboral"<<endl;
		}
		if (n==3){
			cout<<"Miercoles, laboral"<<endl;
		}
		if (n==4){
			cout<<"Jueves, laboral"<<endl;
		}
		if (n==5){
			cout<<"Viernes, laboral"<<endl;
		}
		if (n==6){
			cout<<"Sabado, finde"<<endl;
		}
		if (n==7){
			cout<<"Domingo, finde"<<endl;
		}
	}
	else{
		cout<<"Dia incorrecto"<<endl;
	}
cin.ignore();
cin.get();
}

