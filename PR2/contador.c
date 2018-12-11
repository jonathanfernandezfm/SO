/*
 reciboSignal.c
 Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
 Utilizaci—n de la llamada sigaction para cambiar el comportamiento del proceso       
 frente a la recepci—n de una se–al.
*/

#define _DEFAULT_SOURCE

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

int cont[17];

static void sig_USR_hdlr(int sigNum){
  cont[sigNum] = cont[sigNum] + 1;
  printf("He recibido la señal %i un total de %i veces\n", sigNum, cont[sigNum]);
}

int main(int argc, char *argv[])
{
  for(int i=0; i<17; i++){
    cont[i] = 0;
  }

  struct sigaction sig_USR_nact;

  if(setvbuf(stdout,NULL,_IONBF,0)){
    perror("\nError en setvbuf");
  }

//Inicializar la estructura sig_USR_na para especificar la nueva acci—n para la se–al.

  sig_USR_nact.sa_handler= sig_USR_hdlr;

  printf("\n No puedo manejar la señal %i\n", SIGKILL);
  printf(" No puedo manejar la señal %i\n", SIGSTOP);
  printf(" No puedo manejar la señal %i\n", SIGTTOU);
  printf(" Esperando el envio de señales...\n");

//'sigemptyset' inicia el conjunto de se–ales dado al conjunto vacio. 

  sigemptyset (&sig_USR_nact.sa_mask);
  sig_USR_nact.sa_flags = 0;


  for(int i=1; i < 30; i++){
    if(i != 9 && i != 19){
      if(sigaction(i, &sig_USR_nact, NULL) <0) {
        perror("\nError al intentar establecer el manejador de senal para señal");
        printf("%i", i);
        exit(EXIT_FAILURE);
      }
    }
  }
  //Establecer mi manejador particular de se–al para SIGUSR1
  if( sigaction(SIGUSR1,&sig_USR_nact,NULL) <0) {
  	perror("\nError al intentar establecer el manejador de senal para SIGUSR1");
  	exit(EXIT_FAILURE);
  }
  //Establecer mi manejador particular de se–al para SIGUSR2
  if( sigaction(SIGUSR2,&sig_USR_nact,NULL) <0) {
  	perror("\nError al intentar establecer el manejador de senal para SIGUSR2");
  	exit(EXIT_FAILURE);
  }
  if( sigaction(SIGHUP,&sig_USR_nact,NULL) <0) {
    perror("\nError al intentar establecer el manejador de senal para SIGHUP");
    exit(EXIT_FAILURE);
  }
  if( sigaction(SIGINT,&sig_USR_nact,NULL) <0) {
    perror("\nError al intentar establecer el manejador de senal para SIGINT");
    exit(EXIT_FAILURE);
  }
  if( sigaction(SIGQUIT,&sig_USR_nact,NULL) <0) {
    perror("\nError al intentar establecer el manejador de senal para SIGQUIT");
    exit(EXIT_FAILURE);
  }
  if( sigaction(SIGILL,&sig_USR_nact,NULL) <0) {
    perror("\nError al intentar establecer el manejador de senal para SIGILL");
    exit(EXIT_FAILURE);
  }
  if( sigaction(SIGSEGV,&sig_USR_nact,NULL) <0) {
    perror("\nError al intentar establecer el manejador de senal para SIGSEGV");
    exit(EXIT_FAILURE);
  }
  if( sigaction(SIGALRM,&sig_USR_nact,NULL) <0) {
    perror("\nError al intentar establecer el manejador de senal para SIGALRM");
    exit(EXIT_FAILURE);
  }
  if( sigaction(SIGTERM,&sig_USR_nact,NULL) <0) {
    perror("\nError al intentar establecer el manejador de senal para SIGTERM");
    exit(EXIT_FAILURE);
  }
  if( sigaction(SIGUSR1,&sig_USR_nact,NULL) <0) {
    perror("\nError al intentar establecer el manejador de senal para SIGUSR1");
    exit(EXIT_FAILURE);
  }
  if( sigaction(SIGUSR2,&sig_USR_nact,NULL) <0) {
    perror("\nError al intentar establecer el manejador de senal para SIGUSR2");
    exit(EXIT_FAILURE);
  }
  if( sigaction(SIGCHLD,&sig_USR_nact,NULL) <0) {
    perror("\nError al intentar establecer el manejador de senal para SIGCHLD");
    exit(EXIT_FAILURE);
  }
  if( sigaction(SIGCONT,&sig_USR_nact,NULL) <0) {
    perror("\nError al intentar establecer el manejador de senal para SIGCONT");
    exit(EXIT_FAILURE);
  }

  if( sigaction(SIGTSTP,&sig_USR_nact,NULL) <0) {
    perror("\nError al intentar establecer el manejador de senal para SIGTSTP");
    exit(EXIT_FAILURE);
  }
  if( sigaction(SIGTTIN,&sig_USR_nact,NULL) <0) {
    perror("\nError al intentar establecer el manejador de senal para SIGTTIN");
    exit(EXIT_FAILURE);
  }

  for(;;){}
}