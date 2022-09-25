#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

void lee(float v[],int n){
	float aux; int contador=0;
	for (;n>0;n--){
		cout<<"Introduzca valor"<<endl;
		cin>>aux;
		v[contador]=aux;
		contador++;
	}
}

void imprime(float v[],int n){
	cout<<""<<endl;
	for( int contador=0;contador<n;contador++){
		cout<<v[contador]<<endl;
	}
}

int main(){
	int n;
	cout<<"Introduzca numero de parametros"<<endl;
	cin>>n;
	float v[n];
	lee(v,n);
	imprime(v,n);
	
cin.ignore();
cin.get();
}

