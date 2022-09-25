#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

bool palindromo(string cad){
	bool res=true;
	int n=cad.size();
	for (int i=0;i<n;i++){
		if(cad[i]!=cad[n-i-1]){
		res=false;
		}
	}
	return res;
}


int main(){
	bool res;
	string cadena;
	cout<<"introduzca cad"<<endl;
	getline(cin,cadena);
	res=palindromo(cadena);
	if(res==true){
		cout<<"Es palindromo"<<endl;
	}
	else{
		cout<<"No es palindromo"<<endl;
}

    system("pause");
}

