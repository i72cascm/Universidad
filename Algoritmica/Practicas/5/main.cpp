//============================================================================
// Algoritmica
// Name        : main.cpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 22/11/2022
//============================================================================

//Includes
#include <iostream>
using namespace std;

void nReinas(bool solUnica);
void algVegas();

int main(){

    //Menu para escoger el algoritmo a medir
    int op = 0;
    bool loop = true, solUnica = false;

    do{

        cout<<"Introduzca el metodo que quiere usar: "<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"Opcion 1: Todas las soluciones del problema para un valor de n."<<endl;
        cout<<"Opcion 2: Encontrar la primera solución y el tiempo que tarda para un determinado n."<<endl;
        cout<<"Opcion 3: Algoritmo de las Vegas."<<endl;
        cout<<"Opcion 4: Salir"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"Opcion: ";
        cin>>op;


        //Opciones del menu
        switch(op){
            
            case 1:
                solUnica = false;
                nReinas(solUnica);
                cout<<endl;
            break;

            case 2:
                solUnica = true;
                nReinas(solUnica);
                cout<<endl;
            break;

            case 3:
                algVegas();
                cout<<endl;
            break;

            case 4:
                loop = false;
            break;

            default:
                cout<<endl;
                cout<<"Error: La opcion introducida debe ser un numero comprendido entre 1 y 4."<<endl;
                cout<<endl;
            break;

        }
    }while(loop);

    return 0;
    
}