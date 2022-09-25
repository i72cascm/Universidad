#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	float aux,n;
	int contador=4;
	cout<<"Introduzca valor"<<endl;
	cin>>n;
	aux=n;
	do {
		cout<<"Introduzca valor"<<endl;
		cin>>n;
		if(n<aux) {
			aux=n;
		}
		contador--;
	}while(contador>0);
	cout<<"El menor es: "<<aux<<endl;
		
cin.ignore();
cin.get();
}

