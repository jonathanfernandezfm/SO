#define _DEFAULT_SOURCE

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#define tamano 1024
#define longnombre 50

#define FIFO_E "fifoe"
#define FIFO_S "fifos"

static void sig_handler(int sigNum){
	int estado, childpid;
	if(sigNum == SIGCHLD){
		if((childpid = wait(&estado)) == -1){
			perror("Servidor: Error en wait");
			exit(EXIT_FAILURE);
		}
	}
}

int main(int argc, char** argv){
	int pid, pidproxy, ctl;
	int dfE, dfS, dfProxy;
	char fifoProxy[longnombre];
	struct sigaction signal_act;

  	signal_act.sa_handler= sig_handler;
	sigemptyset (&signal_act.sa_mask);
  	signal_act.sa_flags = 0;

  	if( sigaction(SIGCHLD, &signal_act,NULL) <0) {
  		perror("\nServidor: Error al intentar establecer el manejador de senal para SIGCHLD");
  		exit(EXIT_FAILURE);
  	}

	if(argc < 1){
		printf("Servidor: Formato: servidor");
		exit(EXIT_FAILURE);
	}

	setbuf(stdout, NULL);

	mkfifo(FIFO_E, S_IRWXU);
	mkfifo(FIFO_S, S_IRWXU);

	if ((dfE = open (FIFO_E, O_RDWR)) == -1) {
		perror ("Servidor: Problema en la creación del archivo fifo de entrada");
		exit(EXIT_FAILURE);
	}
	if ((dfS = open (FIFO_S, O_WRONLY)) == -1) {
		perror ("Servidor: Problema en la creación del archivo fifo de salida");
		exit(EXIT_FAILURE);
	}

	while((ctl = read(dfE, &pid, sizeof(int))) != 0){
		if(ctl != -1){
			if((pid = fork()) == 0){ // hijo
				pidproxy = getpid();
				sprintf(fifoProxy, "fifo.%d", pidproxy);

				mkfifo(fifoProxy, S_IRWXU);

				if(!(ctl = write (dfS, &pidproxy, sizeof(int)))){
					perror ("Servidor: error al escribir pidproxy en fifo de salida");
					exit(EXIT_FAILURE);
				}
				if ((dfProxy = open (fifoProxy, O_RDONLY)) == -1) {
					perror ("Servidor: error al abrir el archivo fifoproxy");
					exit(EXIT_FAILURE);
				}

				if((ctl = dup2(dfProxy, STDIN_FILENO)) == -1){
					perror ("Servidor: error en dup2");
					exit(EXIT_FAILURE);
				}

				if((ctl = execl("proxy", "proxy")) == -1){
					perror ("Servidor: error en la ejecucion de proxy");
					exit(EXIT_FAILURE);
				}
			}
		}
	}

	return EXIT_SUCCESS;
}