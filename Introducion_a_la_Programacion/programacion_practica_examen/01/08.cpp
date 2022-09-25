#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;

int main(){
	float x0,x1,y0,y1,x,y,distancia;
	cout<<"Introduzca posicion 1"<<endl;
	cin>>x0;
	cin>>y0;
	cout<<"Introduzca posicion 2"<<endl;
	cin>>x1;
	cin>>y1;
	x=x1-x0;
	y=y1-y0;
	distancia=sqrt(x*x+y*y);
	cout<<distancia<<endl;
cin.ignore();
cin.get();
}

