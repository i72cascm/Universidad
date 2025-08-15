#include <iostream>
#include <string>
#include <fstream>
#include "alumno.h"
using namespace std;

void editar()
{

  Alumno A;
  int grupo,curso;
  string dni,email, nombre, apellido, telefono, direccion, fecha;
  bool lider,tiempo;  //Tiempo parcial o no
  cout<<"Introduzca el DNI del alumno que quiere cambiar"<<endl;
  cin>>DNI;
  ifstream fentrada("Agenda.dat",ios::in|ios::binary);
  ofstream fsalida("Agenda.dat",ios::out|ios::binary)
  cout << "\nAcceso secuencial:" << endl;
  fentrada.read(dni);
  do
  {
    cout << cad << endl;
    if(fentrada.read(dni, 20):=dni)
    {
      cin>>nombre;
      A.setNombre(nombre)
    }

  } while(!fentrada.eof);

}
