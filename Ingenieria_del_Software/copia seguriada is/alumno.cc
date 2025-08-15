//alumno.cc
//métodos de la clase alumnos

#include <string>
#include <iostream>
#include "alumno.h"
using namespace std;

Alumno::Alumno(string DNI, string nombre, string apellidos, string email, string direccion, string nacimiento, int telefono, int grupo, int liderazgo,int parcialidad, int curso){
  DNI_=DNI;
  nombre_=nombre;
  apellidos_=apellidos;
  email_=email;
  direccion_=direccion;
  nacimiento_=nacimiento;
  telefono_=telefono;
  grupo_=grupo;
  liderazgo_=liderazgo;
  parcialidad_=parcialidad;
  curso_=curso;
}
