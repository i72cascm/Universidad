//main.cc

#include <string>
#include <iostream>
#include "alumno.h"
#include "agenda.h"
using namespace std;



int main(){

  string DNI,nombre,apellidos,email,direccion,nacimiento;
  string auxdni;
  int telefono,grupo,liderazgo,parcialidad,curso;
  int menu,menuMostrar,auxencontrar;

  Alumno alum(DNI, nombre, apellidos, email, direccion, nacimiento, telefono, grupo, liderazgo, parcialidad, curso);
  Agenda agen;

    do{

      //variables auxiliares
      string dnia="", nombrea="", apellidosa="", emaila="", direcciona="", nacimientoa="";
      int telefonoa=0, grupoa=0, liderazgoa=0, parcialidada=2, cursoa=0;

      //opciones del menu
      cout<<endl;
      cout<<"Bienvenido/a."<<endl;
      cout<<"Introduzca una opción:"<<endl;
      cout<<"1: Introducir alumno."<<endl;
      cout<<"2: Mostrar alumno."<<endl;
      cout<<"3: Mostrar listado de alumnos."<<endl;
      cout<<"4: Modificar alumno."<<endl;
      cout<<"5: Borrar alumno."<<endl;
      cout<<"6: Buscar alumno."<<endl;
      cout<<"7: Entrar en modo coordinador."<<endl;
      cout<<"8: Salir."<<endl;

      cin>>menu;

      switch(menu){

      case 1:

        cout<<"Introduzca DNI"<<endl; //set dni
        getchar();
        getline(cin, dnia); //este getline introduce "" al dni por lo que se utiliza un segundo getline
        if(dnia.empty()){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setDNI(dnia);
        }

        cout<<"Introduzca nombre."<<endl; //set nombre
        getline(cin, nombrea);
        if (nombrea.empty()){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setNombre(nombrea);
        }

        cout<<"Introduzca apellidos. Nota: separe los apellidos mediante una barra baja -> _."<<endl; //set apellidos
        getline(cin, apellidosa);
        if (apellidosa.empty()){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setApellidos(apellidosa);
        }

        cout<<"Introduzca email."<<endl; // set email
        getline(cin, emaila);
        if (emaila.empty()){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setEmail(emaila);
        }

        cout<<"Introduzca direccion."<<endl; // set direccion
        getline(cin, direcciona);
        if (direcciona.empty()){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setDireccion(direcciona);
        }

        cout<<"Introduzca fecha de nacimiento."<<endl; //set nacimiento
        getline(cin, nacimientoa);
        if (nacimientoa.empty()){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setNacimiento(nacimientoa);
        }

        cout<<"Introduzca telefono."<<endl; //set telefono
        cin>>telefonoa;
        if (telefonoa==0){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setTelefono(telefonoa);
        }

        cout<<"Introduzca grupo. Introducir 0 significa alumno sin grupo."<<endl; //set grupo
        cin>>grupoa;
        alum.setGrupo(grupoa);


        cout<<"Introduzca el liderazgo. 0=no es lider 1=es lider"<<endl; //set liderazgo
        cin>>liderazgoa;
        if((liderazgoa!=0) && (liderazgoa!=1)){
          cout<<"Error, ese valor no existe."<<endl;
          break;
        }else{
        alum.setLiderazgo(liderazgoa);

      }
        cout<<"Introduzca la parcialidad. 0=Completo 1=Parcial"<<endl; //set parcialidada
        cin>>parcialidada;
        if((parcialidada!=0) && (parcialidada!=1)){
          cout<<"Error, ese valor no existe."<<endl;
          break;
        }else{
          alum.setParcialidad(parcialidada);
        }

        cout<<"Introduzca curso."<<endl; //set curso
        cin>>cursoa;
        if (cursoa==0){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setCurso(cursoa);
        }
        agen.introducirAlumno(alum);

      break;

      case 2:

      cout<<"1:Mostrar por DNI 2:Mostrar por Apellidos 3:Mostrar por grupo"<<endl;
      getchar();
      cin>>menuMostrar;
      switch (menuMostrar){

        case 1:

        cout<<"Introduzca DNI para mostrar alumno."<<endl; //set dni
        getchar();
        getline(cin, dnia);
        auxencontrar=agen.encontrarAlumno(dnia);
        if (auxencontrar==1){
          alum=agen.mostrarAlumnodni(dnia);
          cout<<endl;
          cout<<"DNI: "<<alum.getDNI()<<endl;
          cout<<"Nombre: "<<alum.getNombre()<<endl;
          cout<<"Apellidos: "<<alum.getApellidos()<<endl;
          cout<<"Correo: "<<alum.getEmail()<<endl;
          cout<<"Dirección: "<<alum.getDireccion()<<endl;
          cout<<"Nacimiento: "<<alum.getNacimiento()<<endl;
          cout<<"Teléfono: "<<alum.getTelefono()<<endl;
          cout<<"Grupo (0=no grupo): "<<alum.getGrupo()<<endl;
          cout<<"Liderazgo (1=lider 0=no lider): "<<alum.getLiderazgo()<<endl;
          cout<<"Parcialidad (0=Completo 1=Parcial): "<<alum.getParcialidad()<<endl;
          cout<<"Curso: "<<alum.getCurso()<<endl;
        }else{
          cout<<"Alumno no encontrado."<<endl;
        }

        break;

        case 2:

        getchar();
        cout<<"Introduzca los apellidos separados por -> _. "<<endl;
        getline(cin,apellidosa);
        agen.mostrarAlumnoapellidos(apellidosa);

        break;

        case 3:

        getchar();
        cout<<"Introduzca el grupo que desea buscar."<<endl;
        cin>>grupoa;
        agen.mostrarAlumnogrupo(grupoa);

        break;

      }
      break;

      case 3:

      if(agen.mostrarListado()==1){
        cout<<"Listado.md creado en el directorio."<<endl;
      }else{
        cout<<"No hay alumnos para crear listado."<<endl;
      }

      break;

      case 4:

      getchar();
      cout<<"Introduzca el DNI del alumno que desea modificar."<<endl;
      getline(cin,dnia);
      auxdni=dnia;
      auxencontrar=agen.encontrarAlumno(dnia);
      if (auxencontrar==1){

        cout<<"Introduzca DNI"<<endl; //set dni
        getline(cin, dnia); //este getline introduce "" al dni por lo que se utiliza un segundo getline
        if(dnia.empty()){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setDNI(dnia);
        }

        cout<<"Introduzca nombre."<<endl; //set nombre
        getline(cin, nombrea);
        if (nombrea.empty()){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setNombre(nombrea);
        }

        cout<<"Introduzca apellidos. Nota: separe los apellidos mediante una barra baja -> _."<<endl; //set apellidos
        getline(cin, apellidosa);
        if (apellidosa.empty()){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setApellidos(apellidosa);
        }

        cout<<"Introduzca email."<<endl; // set email
        getline(cin, emaila);
        if (emaila.empty()){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setEmail(emaila);
        }

        cout<<"Introduzca direccion."<<endl; // set direccion
        getline(cin, direcciona);
        if (direcciona.empty()){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setDireccion(direcciona);
        }

        cout<<"Introduzca fecha de nacimiento."<<endl; //set nacimiento
        getline(cin, nacimientoa);
        if (nacimientoa.empty()){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setNacimiento(nacimientoa);
        }

        cout<<"Introduzca telefono."<<endl; //set telefono
        cin>>telefonoa;
        if (telefonoa==0){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setTelefono(telefonoa);
        }

        cout<<"Introduzca grupo. Introducir 0 significa alumno sin grupo."<<endl; //set grupo
        cin>>grupoa;
        alum.setGrupo(grupoa);


        cout<<"Introduzca el liderazgo. 0=no es lider 1=es lider"<<endl; //set liderazgo
        cin>>liderazgoa;
        if((liderazgoa!=0) && (liderazgoa!=1)){
          cout<<"Error, ese valor no existe."<<endl;
          break;
        }else{
        alum.setLiderazgo(liderazgoa);

      }
        cout<<"Introduzca la parcialidad. 0=Completo 1=Parcial"<<endl; //set parcialidada
        cin>>parcialidada;
        if((parcialidada!=0) && (parcialidada!=1)){
          cout<<"Error, ese valor no existe."<<endl;
          break;
        }else{
          alum.setParcialidad(parcialidada);
        }

        cout<<"Introduzca curso."<<endl; //set curso
        cin>>cursoa;
        if (cursoa==0){
          cout<<"Error, campo obligatorio."<<endl;
          break;
        }else{
          alum.setCurso(cursoa);
        }
        agen.modificarAlumno(alum, auxdni);

      }else{
        cout<<"Alumno no encontrado."<<endl;
      }

      break;

      case 5:

      getchar();
      cout<<"Introduzca DNI del alumno que desea eliminar."<<endl;
      getline(cin,dnia);
      auxencontrar=agen.borrarAlumno(dnia);
      if(auxencontrar==1){
        cout<<"Alumno encontrado y eliminado."<<endl;
      }
      if(auxencontrar==2){
        cout<<"Alumno no encontrado."<<endl;
      }

      break;

      case 6:

      cout<<"Introduzca el DNI del alumno a buscar."<<endl;
      getchar();
      getline (cin, dnia);
      auxencontrar=agen.encontrarAlumno(dnia);
      if (auxencontrar==1){
        cout<<"Alumno encontrado."<<endl;
      }else{
        cout<<"Alumno no encontrado."<<endl;
      }

      break;

      case 7:
      //guardar y cargar
      break;
      }

    } while(menu!=8);

    return 0;
}
