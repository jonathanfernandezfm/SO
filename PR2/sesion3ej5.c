#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	if(argc<2) {
		printf("\nSintaxis de ejecucion: sesion3ej5 numero\n\n");
		exit(EXIT_FAILURE);
	}

	int n_ch=strtol(argv[1], NULL, 10);
	int estado;
	pid_t childpid[n_ch], pid;
	
	for(int i=0; i<n_ch; i++){
		if( (pid=fork())<0) {
			perror("\nError en el fork 1");
			exit(EXIT_FAILURE);
		}
		if(!pid){
			printf(" + Soy el hijo PID: %i\n", getpid());
			exit(EXIT_SUCCESS);
		}
		childpid[i] = pid;
	}

	//for(int i=0; i<n_ch; i++){
	//	printf(" - %i", childpid[i]);
	//}

	int cont = n_ch;

	for(int i=0; i < n_ch; i+=2){
		if((pid=waitpid(childpid[i], &estado, 0)) < 0){
			perror("\nERROR en el wait");
			exit(EXIT_FAILURE);
		}else{
			printf("\n - - Acaba de finalizar mi hijo impar con PID: %i\n", pid);
			cont--;
			printf("     Solo me quedan %i hijos vivos\n\n", cont);
		}
	}
	for(int i=1; i < n_ch; i+=2){
		if((pid=waitpid(childpid[i], &estado, 0)) < 0){
			perror("\nERROR en el wait");
			exit(EXIT_FAILURE);
		}else{
			printf(" - - Acaba de finalizar mi hijo par con PID: %i\n", pid);
			cont--;
			printf("     Solo me quedan %i hijos vivos\n\n", cont);
		}
	}
	exit(EXIT_SUCCESS);
}
