#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
float n,aux;
int contador;
cout<<"Introduce numero"<<endl;
cin>>n;
aux=n; //se definen las variables y se piden numeros de manera similar al ejercicio con while
for (contador=4;contador>0;contador--) { //se utiliza un for para la variable contador y en el se piden mas numeros y se guarda el menor de ellos
	cout<<"Introduce numero"<<endl;
	cin>>n;
	if (aux>=n) {aux=n;}
}
cout<<"El numero menor de los introducidos es: "<<aux<<endl; //se muestra el resultado
    system("pause");
}

