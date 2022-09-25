#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

int main(int argc,char **argv){ 
	float contador=0,sumatorio=0,res,a; //se crea un contador para ir sumando al sumatorio de la media
	for(int i=1;i<argc;i++){
		a=stof(argv[i]); //se transforma los argumentos en valores flotantes
		sumatorio=sumatorio+a;
		contador++; //el contador suma hasta el numero de valores que se introducen para hacer la media
	}
	res=sumatorio/contador; //se realiza la media
	cout<<res<<endl;//se muestra la media
    system("pause");
}