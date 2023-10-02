//============================================================================
// Algoritmica
// Name        : main.cpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 8/11/2022
//============================================================================

//Includes
#include <iostream>
using namespace std;

void metodo_primero();

int main(){

    //Menu para escoger el algoritmo a medir
    int op = 0;
    bool loop = true;

    do{

        cout<<"Introduzca el metodo que quiere usar: "<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"Opcion 1: Metodo 1"<<endl;
        cout<<"Opcion 2: Salir"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"Opcion: ";
        cin>>op;


        //Opciones del menu
        switch(op){
            
            case 1:
                metodo_primero();
                cout<<endl;
            break;

            case 2:
                loop = false;
            break;

            default:
                cout<<endl;
                cout<<"Error: La opcion introducida debe ser un numero comprendido entre 1 y 2."<<endl;
                cout<<endl;
            break;

        }
    }while(loop);

    return 0;
    
}