//consumidorFIFO.c
//Consumidor que usa mecanismo de comunicacion FIFO.
#define _DEFAULT_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#define ARCHIVO_FIFO "ComunicacionFIFO"

int main(int argc, char* argv[])
{
	int fd;
	int leidos;
	int num;

	/* Check args */
	if(argc != 1){
		printf("Usage: %s\n\n", argv[0]);
	}

	//Crear el cauce con nombre (FIFO) si no existe
	umask(0);
	mknod(ARCHIVO_FIFO,S_IFIFO|0666,0);
	//tambi�n vale: mkfifo(ARCHIVO_FIFO,0666);

	//Abrir el cauce para lectura-escritura
	if ( (fd=open(ARCHIVO_FIFO,O_RDONLY)) <0) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	//Aceptar datos a consumir hasta que se env�e la cadena fin
	while(1) {
		if ((leidos=read(fd,&num,sizeof(int))) != 0){
			if(num==-1) {
				close(fd);
				unlink(ARCHIVO_FIFO);
				return EXIT_SUCCESS;
			}
		printf("\nMensaje recibido: %d\n", num);
		}
	}

	return EXIT_SUCCESS;
}





