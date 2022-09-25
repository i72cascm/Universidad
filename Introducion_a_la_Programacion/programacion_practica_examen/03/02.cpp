#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	float aux=0,n=0;
	for (;n>=0;){
		cout<<"Introduzca valor"<<endl;
		cin>>n;
		if(n>aux){
			aux=n;
		}
	}
	cout<<aux<<endl;

cin.ignore();
cin.get();
}

