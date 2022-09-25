#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int n,contador;
	float aux,media=0;
	cout<<"Introduzca numero de parametros"<<endl;
	cin>>n;
	contador=n;
	while (contador>0){
		cout<<"Introduzca valor"<<endl;
		cin>>aux;
		media=media+aux;
		contador--;
	}
	media=media/n;
	cout<<"La media es: "<<media<<endl;
    system("pause");
}