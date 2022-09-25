#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

void replace(string& cad,char a,char b){
	int n=cad.size();
	for (int i=0;i<n;i++){
		if (cad[i]==a){
			cad[i]=b;
		}
	}
}

int main(){
	string cadena;
	char a,b;
	cout<<"Introduce cadena"<<endl;
	getline(cin,cadena);
	cout<<"Introduce caracter a reemplazar"<<endl;
	cin>>a;
	cout<<"Introduce caracter reemplazado"<<endl;
	cin>>b;
	replace(cadena,a,b);
	cout<<cadena<<endl;
    system("pause");
}

