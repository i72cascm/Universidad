#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

bool esprimo(int v){
	bool res=false;
	int contador=0;
	for (int i=1;i<=v;i++){
		if (v%i==0){
			contador++;
		}
	}
	if (contador==2){
		res=true;
	}
	return res;
}

int main(){
	int n;
	bool res;
	cout<<"Introduzca valor"<<endl;
	cin>>n;
	res=esprimo(n);
	if (res==true){
		cout<<"Es primo"<<endl;
	}
	else{cout<<"No es primo"<<endl;}

cin.ignore();
cin.get();
}

