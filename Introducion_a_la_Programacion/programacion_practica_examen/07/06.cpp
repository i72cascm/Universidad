#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
string concatena(string a,string b){
	string c=a+b;
	return c;
}

int main(){
	string a, b, c;
	cout<<"Introduzca a"<<endl;
	getline(cin, a);
	cout<<"Introduzca b"<<endl;
	getline(cin, b);
	c=concatena(a,b);
	cout<<c<<endl;
    system("pause");
}

