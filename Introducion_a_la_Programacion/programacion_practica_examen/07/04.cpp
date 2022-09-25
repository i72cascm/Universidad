#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int vocales(string cad){
	int va='a',ve='e',vi='i',vo='o',vu='u';
	int n=cad.size();
	int res=0;
	for (int i=0;i<n;i++){
		cad[i]=tolower(cad[i]);
	}
	for (int i=0;i<n;i++){
		if ((cad[i]==va)||(cad[i]==ve)||(cad[i]==vi)||(cad[i]==vo)||(cad[i]==vu)){
			res++;
		}
	}
	return res;
}
int main(){
	string cadena;
	int n;
	cout<<"Introduzca cadena"<<endl;
	getline(cin, cadena);
	n=vocales(cadena);
	cout<<n<<" vocales"<<endl;

    system("pause");
}

