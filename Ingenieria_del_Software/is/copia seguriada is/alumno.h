//alumno.h

#ifndef ALUMNO_H
#define ALUMNO_H

#include <string>
#include <iostream>
using namespace std;

class Alumno{

private:

  string DNI_,nombre_,apellidos_,email_,direccion_,nacimiento_;
  int telefono_,grupo_,liderazgo_,parcialidad_,curso_;

public:

  Alumno(string DNI, string nombre,string apellidos,string email,string direccion,string nacimiento,int telefono,int grupo, int liderazgo,int parcialidad,int curso);

  //set y get DNI
  inline string getDNI()const{return DNI_;};
  inline void setDNI(string DNI){DNI_=DNI;};

  //set y get nombre
  inline string getNombre()const{return nombre_;};
  inline void setNombre(string nombre){nombre_=nombre;};

  //set y get apellidos
  inline string getApellidos()const{return apellidos_;};
  inline void setApellidos(string apellidos){apellidos_=apellidos;};

  //set y get email
  inline string getEmail()const{return email_;};
  inline void setEmail(string email){email_=email;};

  //set y get direccion
  inline string getDireccion()const{return direccion_;};
  inline void setDireccion(string direccion){direccion_=direccion;};

  //set y get nacimiento
  inline string getNacimiento()const{return nacimiento_;};
  inline void setNacimiento(string nacimiento){nacimiento_=nacimiento;};

  //set y get telefono
  inline int getTelefono()const{return telefono_;};
  inline void setTelefono(int telefono){telefono_=telefono;};

  //set y get grupo
  inline int getGrupo()const{return grupo_;};
  inline void setGrupo(int grupo){grupo_=grupo;};

  //set y get liderazgo
  inline int getLiderazgo()const{return liderazgo_;};
  inline void setLiderazgo(int liderazgo){liderazgo_=liderazgo;};

  //set y get parcialidad
  inline int getParcialidad()const{return parcialidad_;};
  inline void setParcialidad(int parcialidad){parcialidad_=parcialidad;};

  //set y get curso
  inline int getCurso()const{return curso_;};
  inline void setCurso(int curso){curso_=curso;};
};

#endif
