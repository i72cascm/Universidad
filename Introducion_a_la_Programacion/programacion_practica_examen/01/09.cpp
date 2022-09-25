#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	float a,b,c;
	cout<<"Introduzca a,b y c"<<endl;
	cin>>a;
	cin>>b;
	cin>>c;
	if (((c>a) && (c<b)) || ((c<a) && (c>b))) {
		cout<<"c esta entre a y b"<<endl;
	}
	else{ cout<<"c no esta entre a y b"<<endl;}
cin.ignore();
cin.get();
}

