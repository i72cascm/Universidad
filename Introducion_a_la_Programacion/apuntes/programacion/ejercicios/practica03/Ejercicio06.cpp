#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int n,contador=2;
	bool v=true;
	cout<<"Introduzca numero para comprobar si es primo."<<endl;
	cin>>n;
	if (n<=0){
		cout<<"Introduzca valores mayores que 0."<<endl;
	}
	else{
		for (;contador<n;contador++){
			if(n%contador==0){
				v=false;
			}
		}
	if (v==true) { 
		cout<<"El numero es primo."<<endl;
	}
	else{
		cout<<"El numero no es primo."<<endl;
	}
}
    system("pause");
}

