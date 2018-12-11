#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define tamano 1024
#define longnombre 50

/* LOCK_UNLOCK(FILE_HANDLER, L_TYPE, CERROJO) */
void lock_unlock(int fh, short type, struct flock cerrojo){
	int ctl;

	cerrojo.l_type = type;
	cerrojo.l_whence =SEEK_SET;
	cerrojo.l_start =0;
	cerrojo.l_len =0;
	
	if((ctl = fcntl(fh, F_SETLKW, &cerrojo)) == -1){
		perror ("Proxy: error al hacer LOCK_UNLOCK (cerrojo)");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char** argv){
	struct flock cerrojo;
	int ctl, nread, nwritten, pidproxy;
	FILE* fhtmp;
	char bufer[tamano];
	char fifoProxy[longnombre];

	pidproxy = getpid();
	sprintf(fifoProxy, "fifo.%d", pidproxy);

	/* TURN out buffer OFF */
	setbuf(stdout, NULL);

	/* CREATION of temp file */
	if((fhtmp = tmpfile()) == NULL){
		perror ("Proxy: error al crear archivo temporal");
		exit(EXIT_FAILURE);
	}
	//printf("check1");
	/* READ of fifo.<pidproxy> */
	while((nread = read (STDIN_FILENO, &bufer, sizeof(char)*tamano)) > 0) {
		//printf("\n%i\n", nread);
		//printf("BUFFER: %.*s\n", nread, bufer);
		/* WRITE on temp file */
		if(!(ctl = fwrite(bufer, sizeof(char)*nread, 1, fhtmp))){
			perror ("Proxy: error al escribir en archivo temporal");
			exit(EXIT_FAILURE);
		}
	}

	/* CHECK error of while(read) */
	if (ctl == -1){
		perror ("Proxy: error al leer fifo proxy");
		exit(EXIT_FAILURE);
	}

	if((ctl = fseek(fhtmp, 0, SEEK_SET)) == -1){
		perror ("Proxy: error al mover el puntero lectura escritura");
		exit(EXIT_FAILURE);
	}
	
	lock_unlock(STDOUT_FILENO, F_WRLCK, cerrojo);

	//printf("check4");
	/* READ of temp file and WRITE on STDOUT */
	while((nread = fread(&bufer, sizeof(char), tamano, fhtmp)) != 0){
		if(ferror(fhtmp)){
			perror ("Proxy: error al leer en archivo temporal");
			exit(EXIT_FAILURE);
		}
		if((nwritten = write(STDOUT_FILENO, bufer, nread)) != nread){
			perror ("Proxy: error al escribir en pantalla");
			exit(EXIT_FAILURE);
		}
	}
	
	lock_unlock(STDOUT_FILENO, F_UNLCK, cerrojo);

	//printf("check7");
	unlink(fifoProxy);

	/* RETURN */
	return EXIT_SUCCESS;
}