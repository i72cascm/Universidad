#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int factorial(int n){
	int res=1;
	for(int i=1;i<=n;i++){
		res=res*i;
	}
	return res;
}

int main(){
	int  n, res;
	cout<<"Introduzca numero"<<endl;
	cin>>n;
	res=factorial(n);
	cout<<"El factorial es: "<<res<<endl;

    system("pause");
}

