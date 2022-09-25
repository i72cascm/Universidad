#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

void fijaValorAleatorio(int v[],int n, int max){
	int aux;
	srand(time(0));
	for(int i=0;i<n;i++){
		aux=rand()%max;
		cout<<aux<<endl;
	}
}

int main(){
	int n,max;
	cout<<"Introduzca numero de parametros"<<endl;
	cin>>n;
	int v[n];
	cout<<"Introduzca valor max"<<endl;
	cin>>max;
	fijaValorAleatorio(v,n,max);

    system("pause");
}

