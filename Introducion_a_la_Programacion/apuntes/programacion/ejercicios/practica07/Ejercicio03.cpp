#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

void convierte_a_mayusculas(string cad){ 	//esta funcion convierte las letras minusculas en mayusculas
	int loncad=cad.size();
	for(int i=0; i<loncad;i++){ //el bucle i, busca las vocales y as convierte en mayusculas mediante la funcion toupper
		cad[i]=toupper(cad[i]);
	}
	cout<<"cambio: "<<cad<<endl;
}


int main(){
	string cad; //se introduce una cadena
	cout<<"Introduzca cadena."<<endl;
	cin>>cad;
	convierte_a_mayusculas(cad); //se llama a la funcion 
    system("pause");
}

