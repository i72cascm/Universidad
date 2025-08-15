//agenda.cc

#include <string>
#include <iostream>
#include <list>
#include <cstdlib>
#include <fstream>
#include "agenda.h"
using namespace std;

Agenda::Agenda(){}

void Agenda::introducirAlumno(Alumno alumno){
  list <Alumno>::iterator i;
  for(i=datos_.begin();i!=datos_.end();i++){
    if(alumno.getDNI()==i->getDNI()){
      cout<<"Ese DNI ya esta registrado."<<endl;
      break;
    }
  }
  datos_.push_back(alumno);
} //1

Alumno Agenda::mostrarAlumnodni(string dnia){
  list <Alumno>::iterator i;
  for(i=datos_.begin();i!=datos_.end();i++){
    if(dnia==i->getDNI()){
      return *i;
    }
  }} //2.1

void Agenda::mostrarAlumnoapellidos(string apellidosa){
  list <Alumno>::iterator i;
  for(i=datos_.begin();i!=datos_.end();i++){
    if(apellidosa==i->getApellidos()){
      cout<<endl;
      cout<<"DNI: "<<i->getDNI()<<endl;
      cout<<"Nombre: "<<i->getNombre()<<endl;
      cout<<"Apellidos: "<<i->getApellidos()<<endl;
      cout<<"Correo: "<<i->getEmail()<<endl;
      cout<<"Dirección: "<<i->getDireccion()<<endl;
      cout<<"Nacimiento: "<<i->getNacimiento()<<endl;
      cout<<"Teléfono: "<<i->getTelefono()<<endl;
      cout<<"Grupo (0=no grupo): "<<i->getGrupo()<<endl;
      cout<<"Liderazgo (1=lider 0=no lider): "<<i->getLiderazgo()<<endl;
      cout<<"Parcialidad (0=Completo 1=Parcial): "<<i->getParcialidad()<<endl;
      cout<<"Curso: "<<i->getCurso()<<endl;
    }
  }
} //2.2

void Agenda::mostrarAlumnogrupo(int grupoa){
  list <Alumno>::iterator i;
  for(i=datos_.begin();i!=datos_.end();i++){
    if(grupoa==i->getGrupo()){
      cout<<endl;
      cout<<"DNI: "<<i->getDNI()<<endl;
      cout<<"Nombre: "<<i->getNombre()<<endl;
      cout<<"Apellidos: "<<i->getApellidos()<<endl;
      cout<<"Correo: "<<i->getEmail()<<endl;
      cout<<"Dirección: "<<i->getDireccion()<<endl;
      cout<<"Nacimiento: "<<i->getNacimiento()<<endl;
      cout<<"Teléfono: "<<i->getTelefono()<<endl;
      cout<<"Grupo (0=no grupo): "<<i->getGrupo()<<endl;
      cout<<"Liderazgo (1=lider 0=no lider): "<<i->getLiderazgo()<<endl;
      cout<<"Parcialidad (0=Completo 1=Parcial): "<<i->getParcialidad()<<endl;
      cout<<"Curso: "<<i->getCurso()<<endl;
    }
  }
} //2.3

int Agenda::mostrarListado(){

  list <Alumno>::iterator i;
  if(datos_.empty()){
    return 0;
  }else{
    ofstream ficherosalida("Listado.md");
    for(i=datos_.begin();i!=datos_.end();i++){
      ficherosalida<<"DNI: "<<(*i).getDNI()<<endl;
      ficherosalida<<"Nombre: "<<(*i).getNombre()<<endl;
      ficherosalida<<"Apellidos: "<<(*i).getApellidos()<<endl;
      ficherosalida<<"Correo: "<<(*i).getEmail()<<endl;
      ficherosalida<<"Direccion: "<<(*i).getDireccion()<<endl;
      ficherosalida<<"Nacimiento: "<<(*i).getNacimiento()<<endl;
      ficherosalida<<"Telefono: "<<(*i).getTelefono()<<endl;
      ficherosalida<<"Grupo: "<<(*i).getGrupo()<<endl;
      ficherosalida<<"Liderazgo: "<<(*i).getLiderazgo()<<endl;
      ficherosalida<<"Parcialidad: "<<(*i).getParcialidad()<<endl;
      ficherosalida<<"Curso: "<<(*i).getCurso()<<endl;
      ficherosalida<<endl;
    }
    ficherosalida.close();
    return 1;
  }} //3

void Agenda::modificarAlumno(Alumno alumno, string dnia){
  list <Alumno>::iterator i;
  for(i=datos_.begin(); i!=datos_.end();i++){
    if(dnia==i->getDNI()){
      datos_.push_back(alumno);
      datos_.erase(i);
      cout<<"Alumno modificado."<<endl;
      break;
    }
  }
} //4

int Agenda::borrarAlumno(string dnia){
  list <Alumno>::iterator i;
  for(i=datos_.begin(); i!=datos_.end();i++){
    if(dnia==i->getDNI()){
      datos_.erase(i);
      return 1;
    }
  }
  return 2;
}//5

int Agenda::encontrarAlumno(string dnia){
  list <Alumno>::iterator i;
  for(i=datos_.begin();i!=datos_.end();i++){
    if(dnia==i->getDNI()){
      return 1;
    }
  }
  return 0;
} //6
