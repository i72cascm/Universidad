#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int n=0,contador, res=0;
	cout<<"Introduzca termino n"<<endl;
	cin>>contador;
	while (contador>=0){
		res=res+n;
		n++;
		contador--;
	}
	cout<<res<<endl;
		
cin.ignore();
cin.get();
}

