#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int var, n_ch=5;
	pid_t childpid;

	
	printf("\nMensaje previo a la ejecución de fork\n");

	for(int i=0; i<n_ch; i++){
		if( (childpid=fork())<0) {
			perror("\nError en el fork 1");
			exit(EXIT_FAILURE);
		}

		if(!childpid){
			printf("Soy el hijo PID: %i\n", getpid());
			exit(EXIT_SUCCESS);
		}
	}
		for(n_ch; n_ch > 0; n_ch--){
			if((childpid=wait(NULL)) < 0){
				perror("\nERROR en el wait");
				exit(EXIT_FAILURE);
			}else{
				printf("Acaba de finalizar mi hijo con PID: %i\n", childpid);
				printf("Solo me queda %i hijos vivos\n", n_ch-1);
			}
		}
	exit(EXIT_SUCCESS);
}
