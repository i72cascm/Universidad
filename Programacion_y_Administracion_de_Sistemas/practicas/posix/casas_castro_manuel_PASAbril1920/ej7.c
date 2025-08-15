#include <stdio.h>   //IMPORTANTE ESCRIBETE QUE SON CADA UNA!!!!!!!!!!
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>


int main(int argc, char* argv[]){
  //creacion de las estructuras para obtencion de informacion de usuario y grupo
  char *lgn;
  FILE* fichero;
  char cadena[30];
  struct passwd *pw;
  struct group *gr;
  int c;
  int option_index=0;

  //Estructura a utilizar por getoptlong
  static struct option long_options[] =
  {
    //"opcion", recibe o no argumento, 0,identificador de la opción(forma corta)
    {"username", required_argument, 0, 'u'},
    {"useruid", required_argument, 0, 'i'},
    {"groupname", required_argument, 0, 'g'},
    {"groupuid", required_argument, 0, 'd'},
    {"allgroups", no_argument, 0, 's'},
    {"allinfo", required_argument, 0, 'a'},
    {"bactive", no_argument, 0, 'b'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
  };

//si no se ha introducido ningún argumento, el programa mostrará
  if (argc<2){
    if ((lgn=getenv("USER"))==NULL || (pw=getpwnam(lgn))==NULL){
      fprintf(stderr, "Obtención de usuario fallida.\n");
      exit(1);
    }

    printf("Nombre: %s\n", pw->pw_gecos);
    printf("Login: %s\n", pw->pw_name);
    printf("Contraseña: %s\n", pw->pw_passwd);
    printf("UID: %d\n", pw->pw_uid);
    printf("Directorio: %s\n", pw->pw_dir);
    printf("Consola: %s\n", pw->pw_shell);
    printf("Número de grupo principal: %d\n", pw->pw_gid);

    //Obtencion de la estructura de información del grupo a traves del número de grupo al que pertenece el usuario y se imprime
    gr=getgrgid(pw->pw_gid);
    printf("Nombre del grupo principal: %s\n",gr->gr_name);

  }else{

    while ((c=getopt_long(argc, argv, "u:i:g:d:sa:bh",long_options, &option_index))!=-1){

      //el usuario ha terminado de introducir opciones
      if(c==-1)
      break;

      switch(c){

        case 'u': //mostrara los datos del nombre de usuario de sistema introducido
        if((pw=getpwnam(optarg))==NULL){
          fprintf(stderr,"Error: Ese nombre de usuario no existe en este sistema.\n");
          break;
        }
        printf("Nombre: %s\n", pw->pw_gecos);
        printf("Login: %s\n", pw->pw_name);
        printf("Contraseña: %s\n", pw->pw_passwd);
        printf("UID: %d\n", pw->pw_uid);
        printf("Directorio: %s\n", pw->pw_dir);
        printf("Consola: %s\n", pw->pw_shell);
        printf("Número de grupo principal: %d\n", pw->pw_gid);
        break;

        case 'i': //mostrará los datos del usuario a traves de su UID
        if((pw=getpwuid(atoi(optarg)))==NULL){
          fprintf(stderr,"Error: Ese UID de usuario no existe en el sistema.\n");
          break;
        }
        printf("Nombre: %s\n", pw->pw_gecos);
        printf("Login: %s\n", pw->pw_name);
        printf("Contraseña: %s\n", pw->pw_passwd);
        printf("UID: %d\n", pw->pw_uid);
        printf("Directorio: %s\n", pw->pw_dir);
        printf("Consola: %s\n", pw->pw_shell);
        printf("Número de grupo principal: %d\n", pw->pw_gid);
        break;

        case 'g': //mostrará los datos del GRUPO a traves del nombre dado
        if((gr = getgrnam(optarg))==NULL){
          fprintf(stderr, "Error: Ese grupo no consta en el sistema.\n");
          break;
        }
        printf("Nombre del grupo principal: %s\n",gr->gr_name);
        printf("Número del grupo principal: %d\n",gr->gr_gid);
        break;

        case 'd': //mostrará los datos del grupo a traves del uid dado
        if((gr = getgrgid(atoi(optarg)))==NULL){
          fprintf(stderr, "Error: Esa ID de grupo no consta en el sistema.\n");
          break;
        }
        printf("Nombre del grupo principal: %s\n",gr->gr_name);
        printf("Número del grupo principal: %d\n",gr->gr_gid);
        break;

        case 's': //abre el fichero de groups, lo recorre y lo muestra por pantalla
        chdir("/etc");
        fichero=fopen("group","r");
				if(fichero==NULL){
					exit(-1);
				}
				while(fgets(cadena,30,fichero)!=NULL){
					strtok(cadena,":");
					if ((gr=getgrnam(cadena))==NULL){
						exit(-1);
					}
					printf("ID del grupo principal: %d\n", gr->gr_gid);
        	printf("Nombre del grupo principal: %s\n", gr->gr_name);
				}
				//chdir(""); //poner aqui la direccion de la carpeta de practicas!!!!!!!!!!!!!!!!!!!!!!
        break;


        case 'a': //muestra toda la info de un usuario pasado
        if((pw=getpwnam(optarg))==NULL){
          fprintf(stderr, "Error: No se ha encontrado a ese usuario en el sistema.\n");
          break;
        }
        printf("Nombre: %s\n", pw->pw_gecos);
        printf("Login: %s\n", pw->pw_name);
        printf("Contraseña: %s\n", pw->pw_passwd);
        printf("UID: %d\n", pw->pw_uid);
        printf("Directorio: %s\n", pw->pw_dir);
        printf("Consola: %s\n", pw->pw_shell);

        gr=getgrgid(pw->pw_gid); //obtenemos la estructura de grupo a traves de la de usuario
        printf("..................................................\n" );
        printf("Nombre del grupo principal: %s\n",gr->gr_name );
        printf("Número del grupo principal: %d\n",gr->gr_gid );
        break;

        case 'b': //obtener datos del grupo del usuario
        if ((lgn=getenv("USER"))==NULL || (pw=getpwnam(lgn))==NULL){
          fprintf(stderr, "Error, no se ha podido obtener el usuario actual.\n" );
          break;
        }
        gr=getgrgid(pw->pw_gid);
        printf("Nombre del grupo principal: %s\n",gr->gr_name );
        printf("Número del grupo principal: %d\n",gr->gr_gid );
        break;

        case 'h': //muestra las opciones
        printf("Uso del programa: ejercicio1 [opciones]\n");
        printf("Opciones:\n" );
        printf("-h, --help        Imprimir esta ayuda\n" );
        printf("-u, --username    Nombre de Usuario\n" );
        printf("-i, --useruid     Identificador de Usuario\n" );
        printf("-g, --groupname   Nombre de Grupo\n");
        printf("-d, --groupuid    Identificador de Grupo\n" );
        printf("-s, --allgroups   Muestra la info de todos los grupos\n" );
        printf("-a, --allinfo     Nombre de Usuario + su info\n" );
        printf("-b, --bactive     Muestra info del grupo usuario actual\n" );
        break;

        case '?': //muestra las opciones si se ha introducido los parámetros mal
        printf("Uso del programa: ejercicio1 [opciones]\n");
        printf("Opciones:\n" );
        printf("-h, --help        Imprimir esta ayuda\n" );
        printf("-u, --username    Nombre de Usuario\n" );
        printf("-i, --useruid     Identificador de Usuario\n" );
        printf("-g, --groupname   Nombre de Grupo\n");
        printf("-d, --groupuid    Identificador de Grupo\n" );
        printf("-s, --allgroups   Muestra la info de todos los grupos\n" );
        printf("-a, --allinfo     Nombre de Usuario + su info\n" );
        printf("-b, --bactive     Muestra info del grupo usuario actual\n" );
        break;
      }
    }
  }
  return 0;
}
