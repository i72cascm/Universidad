#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int a, b, c; //se crean las variables a y b, con una auxiliar c, que ayudara a cambiar sus valores.
	cout<<"Introduce dos valores a y b, en ese orden."<<endl;
	cin >> a;
	cin >> b;
	if (b>a) {
	cout<<b<<">"<<a<<endl;
	}
	else {
		if (a>b) {
		c=a;
		a=b;
		b=c;
		cout<<b<<">"<<a<<endl;
		}
		else {
		cout<<a<<"="<<b<<endl;
		}
	}
    system("pause");
}

