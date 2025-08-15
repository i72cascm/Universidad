#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include "common.h"

//Prototipo de función
void funcionLog(char*);
FILE *fLog=NULL;

int main(int argc, char* argv[]){
    //Cola del servidor
    mqd_t mq_server;
    //Cola del cliente
    mqd_t mq_client;
    //Atributos de la cola
    struct mq_attr attr;
    //Buffer para intercambiar mensajes
    char buffer[MAX_SIZE];
    char mensaje[MAX_SIZE];
    int x;
    //flag que indica cuando se debe parar (palabra exit)
    int must_stop=0;
    //Inicializar los atributos de la cola
    attr.mq_maxmsg[100];            //Maximo numero de mensajes
    attr.mq_msgsize=MAX_SIZE;       //Maximo tamaño de un mensaje
    //nombre para la cola
    char serverQueue[100];
    char clientQueue[100];

    //Nombre para la cola. Al concatenar el login sera unica en un sistema compartido.
    sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));
    printf("[Servidor]: El nombre de la cola para server es: %s\n", serverQueue);

    sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
    printf("[Servidor]:El nombre de la cola para cliente es: %s\n", clientQueue);

    //Crear la cola de mensajes del servidor. La cola CLIENT_QUEUE le servira en ejercicio resumen
    mq_server = mq_open(serverQueue, O_CREAT) | O_RDONLY, 0644, &attr);
    mq_client = mq_open(clientQueue, O_CREAT | O_RDONLY, 0644, &attr);

    if(mq_server == (mqd_t)-1 || mq_client == (mqd_t)-1){
        perror("Error al abrir la cola del servidor");
        exit(-1);
    }
    printf("[Servidor]: El descriptor de la cola server es: %d\n", (int) mq_server);
    printf("[Servidor]: El descriptor de la cola cliente es: %d\n", (int) mq_client);

    do{
        //Número de bytes leidos
        ssize_t bytes_read;

        //Recibir el mensaje
        bytes_read = mq_receive(mq_server, buffer, MAX_SIZE, NULL);

        //Comparar que la recepcion es correcta (bytes leidos no son negativos)
        if(bytes_read<0){
            perror("Error al recibir el mensaje");
            exit(-1);
        }

        //Cerrar la cadena
        //Buffer[bytes_read]='\0';
        //Comprobar elñ fin del bucle
        if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0)
        must_stop=1;
        else{
            printf("Recibido el mensaje: %s\n",buffer);
            funcionLog(buffer);
            //cuento tamaño del mensaje
            x=strlen(buffer)-1;
            sprintf(mensaje,"%d",x);
            //envio tamaño
            if(mq_send(mq_client, mensaje, MAX_SIZE, 0)!=0){
                perror("Error al enviar el mensaje");
                exit(-1);
            }

        }

    }while (!must_stop); //Iterar hasta que llegue el código de salida, es decir, la palabra exit

    //cerrar la cola del servidor
    if(mq_close(mq_server)==(mqd_t)-1 || mq_close(mq_client)==(mqd_t)-1){
        perror("Error al cerrar las colas del servidor");
        exit(-1);
    }

    //Eliminar la cola del servidor
    if(mq_unlink(serverQueue)==(mqd_t)-1 || mq_unlink(clientQueue)==(mqd_t)-1){
        perror("Error al eliminar las colas del servidor");
        exit(-1);
    }
    return 0;
    
}

/*Función auxiliar, escrituro en un log.
No se usa en este ejemplo, pero puede servir para algun ejercicio resumen*/

/*
void funcionLog(char *mensaje){
    int resultado
    char nombreFichero[100];
    char mensajeAEscribir[300];
    time_t t;

    //abrir el fichero
    sprintf(nombreFichero, "log-servidor.txt");
    if(fLog==NULL){
        fLog=fopen(nombreFichero,"at");
        if(fLog==NULL){
            perror("Error abriendo el fichero de log");
            exi(1);
        }
    }

    //Obtener la hora actual
    t=time(NULL);
    struct tm*p=localtime(&t);
    strtime(mensajeAEscribir,1000,"[%Y-%m-%d, %H:%M:%S]",p);

    //Vamos a incluir la hora y el mensaje que nos pasan
    sprintf(mensajeAEscribir, "%s ==> %s\n",mensajeAEscribir,fLog);
    if(resultado<0)
    perror("Error escribiendo en el fichero de log");
    fclose(flog);
    fLog=NULL;
}