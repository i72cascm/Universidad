#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

bool espar(int v){
	bool res;
	if (v%2==0) {
		res=true;
	}
	else{ res=false;}
	return res;
}

int main(){
	int n;
	cout<<"Intrduzca numero"<<endl;
	cin>>n;
	if (espar(n)==true){
		cout<<"Es par"<<endl;
	}
	else{
		cout<<"No es par"<<endl;
	}
cin.ignore();
cin.get();
}

