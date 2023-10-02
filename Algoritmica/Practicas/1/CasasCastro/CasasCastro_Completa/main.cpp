//============================================================================
// Algoritmica
// Name        : main.cpp
// Author      : Manuel Casas Castro (i72cascm)
// Fecha       : 26/09/2022
//============================================================================

//Includes
#include <iostream>
#include <string>

using namespace std;

void ordenacionQuickSort();
void determinanteIterativo();
void determinanteRecursivo();

int main(){

    //Menu para escoger el algoritmo a medir
    int op = 0;
    bool loop = true;

    do{

        cout<<"Introduzca una opcion para calcular su tiempo de ejecucion: "<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"Opcion 1: Ordenacion QuickSort"<<endl;
        cout<<"Opcion 2: Determinante Iterativo"<<endl;
        cout<<"Opcion 3: Determinante Recursivo"<<endl;
        cout<<"Opcion 4: Salir"<<endl;
        cout<<"----------------------------------------------------------"<<endl;
        cout<<"Opcion: ";
        cin>>op;


        //Opciones del menu
        switch(op){
            
            case 1:
                loop = false;
                ordenacionQuickSort();
            break;

            case 2:
                loop = false;
                determinanteIterativo();
            break;

            case 3:
                loop = false;
                determinanteRecursivo();
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