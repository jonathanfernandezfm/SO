#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int var;
	pid_t pid;

	if(argc<2) {
		printf("\nSintaxis de ejecucion: sesion3ej1 numero\n\n");
		exit(EXIT_FAILURE);
	}

	var = strtol(argv[1], NULL, 10);

	printf("\nMensaje previo a la ejecución de fork\n");

	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(EXIT_FAILURE);
	}
	else if(pid==0) {  
		//proceso hijo ejecutando el programa
		if(var%2 == 0){
			printf("HIJO: El numero %i es par\n", var);
		}else{
			printf("HIJO: El numero %i es impar\n", var);
		}
	} else {	//proceso padre ejecutando el programa
		if(var%4 == 0){
			printf("PADRE: El numero %i es divisible por 4\n", var);
		}else{
			printf("PADRE: El numero %i no es divisible por 4\n", var);
		}
	} 		
	exit(EXIT_SUCCESS);
}
