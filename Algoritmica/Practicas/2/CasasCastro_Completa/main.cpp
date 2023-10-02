//============================================================================
// Algoritmica
// Name        : main.cpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 04/10/2022
//============================================================================

//Includes
#include <iostream>
using namespace std;

void metodo_primero();
void metodo_segundo();

int main(){

    //Menu para escoger el algoritmo a medir
    int op = 0;
    bool loop = true;

    do{

        cout<<"Introduzca el metodo que quiere usar: "<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"Opcion 1: Metodo 1"<<endl;
        cout<<"Opcion 2: Metodo 2"<<endl;
        cout<<"Opcion 3: Salir"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"Opcion: ";
        cin>>op;


        //Opciones del menu
        switch(op){
            
            case 1:
                loop = false;
                metodo_primero();
            break;

            case 2:
                loop = false;
                metodo_segundo();
            break;

            case 3:
                loop = false;
                
            break;

            default:
                cout<<endl;
                cout<<"Error: La opcion introducida debe ser un numero comprendido entre 1 y 3."<<endl;
                cout<<endl;
            break;

        }
    }while(loop);

    return 0;
    
}