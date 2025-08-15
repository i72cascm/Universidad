#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mqueue.h>
#include <sys/wait.h>
#include <errno.h> 
#include <string.h> 

#define MAX_SIZE     1024
#define MSG_STOP     "exit"

#define QUEUE_NAME  "/una_cola"

int main()
{
	// Descriptor de la cola
	mqd_t mq;

	// Buffer para lectura/escritura
	char buffer[MAX_SIZE];
	char msj[MAX_SIZE];

	// Atributos de la cola
	struct mq_attr attr;

    // Almacena el nombre de la cola
    char queue_name[100];

	//flag para indicar que hay que parar
	int x; 
	ssize_t bytes_read;

	// Para realizar el fork
	int must_stop=0;
    pid_t s, flag;
    int status;

	// Inicializar los atributos de la cola.
	attr.mq_maxmsg = 10;        // Max número de mensajes
	attr.mq_msgsize = MAX_SIZE; // Max tamaño de un mensaje. Incluir el '/0'

    // Nombre de la cola.
    sprintf(queue_name, "%s-%s", QUEUE_NAME, getenv("USER"));

	// Fork
	s = fork();
	switch (s)
	{
		// Error
		case -1:
			printf ("No he podido crear el proceso hijo \n");
			exit(1);

		case 0: // Hijo. El hijo solo se encargará de escribir.

			/* Apertura de la cola
			   O_CREAT: si no existe, se crea
			   O_RDWR: lectura/escritura
			   O_RDONLY: solo lectura
			   O_WRONLY: solo escritura
			   0644: permisos rw-r--r--
			         permisos de lectura y escritura para el propietario, y de sólo lectura para el grupo y para otros
			   attr: estructura con atributos para la cola  */
			mq = mq_open(queue_name, O_CREAT | O_RDWR, 0644, &attr);
            printf ("[HIJO]: Nombre de la cola: %s\n", queue_name);
            printf ("[HIJO]: Descriptor de la cola: %d\n", (int) mq);

			if(mq==-1){
				perror("[HIJO]: Error al abrir la cola");
				exit(-1);
			}
			printf ("[HIJO]: Mi PID es %d y mi PPID es %d\n", getpid(), getppid());

			printf("Enviando mensajes al servidor (\"%s\" para parar):\n", MSG_STOP);
			do{
				printf("--> ");
				fgets(buffer,MAX_SIZE, stdin);
				if(mq_send(mq,buffer,MAX_SIZE,0)!=0){
					perror("Error al enviar");
					exit(-1);
				}
				if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))!=0){
					bytes_read=mq_receive(mq,msj,MAX_SIZE,NULL);
					if(bytes_read<0){
						perror("Error al recibir el mensaje");
						exit(-1);
					}
					printf("Recibido el mensaje: %s\n",msj);
				}
			}while(strncmp(buffer,MSG_STOP,strlen(MSG_STOP)));

			// Cerrar la cola
			if(mq_close(mq) == -1)
			{
				perror("[HIJO]: Error cerrando la cola");
				exit(-1);
			}
            printf("[HIJO]: Cola cerrada\n");
			break; 

		default: // Padre. El padre solo se encargará de leer

			/* Apertura de la cola */
			mq = mq_open(queue_name, O_CREAT | O_RDWR, 0644, &attr);
            printf ("[PADRE]: El nombre de la cola es: %s\n", queue_name);
            printf ("[PADRE]: El descriptor de la cola es:%d\n", (int) mq);

			if(mq==-1)
			{
				perror("[PADRE]: Error en la apertura de la cola");
				exit(-1);
			}



			do{
				bytes_read=mq_receive(mq,buffer,MAX_SIZE,NULL);
				if(bytes_read<0){
					perror("Error al recibir el mensaje");
					exit(-1);
				}
				buffer[bytes_read]= '\0';
				if(strncmp(buffer,MSG_STOP,strlen(MSG_STOP))==0){
					must_stop=1;
				}else{
					printf("Recibido el mensaje: %s\n",buffer);
					x=strlen(buffer)-1;
					sprintf(msj,"%d",x);
					if(mq_send(mq,msj,MAX_SIZE,0)!=0){
						perror("Error al enviar el mensaje");
						exit(-1);
					}
				}
			}while(!must_stop);

			// Cerrar la cola
			if(mq_close(mq) == -1)
			{
				perror("[PADRE]: Error cerrando la cola");
				exit(-1);
			}
			printf("[PADRE]: Cola cerrada.\n");

			// Eliminar la cola
			if(mq_unlink(queue_name) == -1)
			{
				perror("[PADRE]: Error eliminando la cola");
				exit(-1);
			}

    	/*Espera del padre a los hijos*/
	    while ( (flag=wait(&status)) > 0 )
	    {
		    if (WIFEXITED(status)) {
			    printf("Proceso Padre, Hijo con PID %ld finalizado, status = %d\n", (long int)flag, WEXITSTATUS(status));
		    }
		    else if (WIFSIGNALED(status)) {  //Para seniales como las de finalizar o matar
			    printf("Proceso Padre, Hijo con PID %ld finalizado al recibir la señal %d\n", (long int)flag, WTERMSIG(status));
		    }
	    }
	    if (flag==(pid_t)-1 && errno==ECHILD)
	    {
		    printf("Proceso Padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
	    }
	    else
	    {
		    printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
		    exit(EXIT_FAILURE);
	    }
	}
	exit(0);
}
