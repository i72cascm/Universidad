#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int n;
	cout<<"Introduzca numero"<<endl;
	cin>>n;
	if (n>0) {
		cout<<"Numero mayor que 0"<<endl;
	}
	else{
		if (n==0) {
			cout<<"El numero es 0"<<endl;
		}
		else{
			cout<<"El numero es menor que 0"<<endl;
		}
	}
cin.ignore();
cin.get();

}