//jugador.cc
//metodos de la clase jugador

#include "jugador.h"

void Jugador::setApuestas(){

  char tipo[10], valor[10], cantidad[10];
  Apuesta a;
  apuestas_.clear(); //borra todos los elementos de la lista

  string nomfich= getDNI() + ".txt";
  ifstream entrada (nomfich.c_str());
  if(entrada.is_open()){
    while (entrada.getline(tipo,256,',')){

      entrada.getline(valor,256,',');
      entrada.getline(cantidad,256,'\n');
      a.tipo= atoi(tipo);
      a.valor=valor;
      a.cantidad=atoi(cantidad);
      apuestas_.push_back(a);
    }

  entrada.close();

  }else{
    std::cout<< "Fichero no esta abierto"<<std::endl;
    exit(-1);
  }
}
