#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

int find(string cad1, string cad2){
	int n1=cad1.size();
	int n2=cad2.size();
	if (n2>n1){
		return-1;
	}
	else{
		int contador=0;
		for (int i=0;i<n1;i++){
			if (cad1[i]==cad2[contador]){
				contador++;
			}
			if (contador==n2){
				return n2-1;
			}
		else contador=0;
	}
	return-1;
}
}

int main(){
int n;
string cadena1, cadena2;
	cout<<"Introduce 1"<<endl;
	getline(cin, cadena1);
	cout<<"Introduce cadena 2"<<endl;
	getline(cin, cadena2);
	n=find(cadena1, cadena2);
	cout<<n<<endl;

cin.ignore();
cin.get();
}

