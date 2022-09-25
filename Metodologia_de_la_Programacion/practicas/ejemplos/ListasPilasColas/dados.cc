#include <iostream>
#include <ctime>
#include "dados.h"

Dados::Dados(){
	d1=1;
	d2=1;
}

void Dados::lanzamiento(){
	srand(time(NULL));
	d1=1+rand()%7-1;
	d2=1+rand()%7-1;
}

int Dados::getDado1(){
	return d1;
}

int Dados::getDado2(){
	return d2;
}

bool Dados::setDado1(int a){
	if(a>6||a<0){
		return false;
	}else{
		d1=a;
		return true;
	}
}

int Dados::getSuma(){
	return d1+d2;
}