#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
float radio,area;
cout<<"Introduzca el valor del radio"<<endl;
cin>>radio;
area=radio*radio*3.1415;
cout<<"El area de la circunsferencia es:"<<area<<endl;
cin.ignore();
cin.get();
}