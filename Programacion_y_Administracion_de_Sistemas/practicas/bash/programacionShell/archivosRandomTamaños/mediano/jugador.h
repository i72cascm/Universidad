//jugador.h

#ifndef JUGADOR_H
#define JUGADOR_H

#include "persona.h"
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <cstdlib>

struct Apuesta{
  int tipo;
  string valor;
  int cantidad;
};

using namespace std;

class Jugador: public Persona{

private:

  int dinero_;
  string codigo_;
  list <Apuesta> apuestas_;

public:

  Jugador(string DNI,string codigo,string nombre="",string apellidos="",int edad=0,string direccion ="",string localidad="",string provincia="",string pais=""):Persona(DNI,nombre,apellidos,edad,direccion,localidad,provincia,pais) {

  codigo_=codigo;
  dinero_=1000;
};

  //set y de codigo
  inline string getCodigo()const{return codigo_;};
  inline void setCodigo(string codigo){codigo_=codigo;};

  //set y get de dinero
  inline int getDinero()const{return dinero_;};
  inline void setDinero(int dinero){dinero_=dinero;};

  //set y get de dinero
  inline list <Apuesta> getApuestas(){return apuestas_;};
  void setApuestas();

};

#endif
