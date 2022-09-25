#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int a, b, c, d, e, f, g;
	cout<<"Introduzca dinero para cambiar"<<endl;
	cin>>a;
	cout<<a<<"se cambia en:"<<endl;
	b=a%500;
	a=a/500;
	cout<<a<<" billetes de 500,"<<endl;
	c=b%200;
	b=b/200;
	cout<<b<<" billetes de 200,"<<endl;
	d=c%100;
	c=c/100;
	cout<<c<<" billetes de 100,"<<endl;
	e=d%50;
	d=d/50;
	cout<<d<<" billetes de 50,"<<endl;
	f=e%20;
	e=e/20;
	cout<<e<<" billetes de 20,"<<endl;
	g=f%10;
	f=f/10;
	cout<<f<<" billetes de 10"<<endl;
	g=g/5;z
	cout<<g<<" billetes de 5."<<endl;
    system("pause");
}

