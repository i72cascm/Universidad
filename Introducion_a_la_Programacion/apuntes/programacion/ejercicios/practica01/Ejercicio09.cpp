#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	float a, b, c; //se definen las tres variables
	cout<<"Introduzca 3 valores"<<endl;
	cin >> a;
	cin >> b;
	cin >> c;
	if (((a>c) && (c>b)) || ((b>c) && (c>a))) {cout<<"c esta entre a y b"<<endl;} //se define cuando c esta entre a y b
	else {cout<<"No esta entra a y b"<<endl;
}
    system("pause");
}

