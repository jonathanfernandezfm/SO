#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <linux/limits.h>

int func(char* pathname)
{
	int cont=0;
	DIR* dir;
	struct dirent* entrada;
	struct stat atributos;
	dir=opendir(pathname);
	char strpathname[PATH_MAX];

	while((entrada=readdir(dir)) != NULL){
		sprintf(strpathname, "%s/%s", pathname, entrada->d_name);
		if(!strcmp(entrada->d_name, ".") || !strcmp(entrada->d_name, "..")){
			continue;
		}
		if(stat(strpathname,&atributos) < 0) {
			printf("\nError al intentar acceder a los atributos %s", strpathname);
			perror("\nError en lstat");
			exit(EXIT_FAILURE);
		}
		if(S_ISDIR(atributos.st_mode)){
			cont += func(strpathname);
		}
		else{
			if(S_ISREG(atributos.st_mode)){
				cont += atributos.st_size;
				printf("%s \t\t%lu\n", strpathname, atributos.st_ino);
			}
		}
	}
	return cont;
}

int main(int argc, char *argv[])
{
	if(argc<2) {
		printf("\nSintaxis de ejecucion: ./xxxx pathname\n\n");
		exit(EXIT_FAILURE);
	}
	printf("File\t\t\t\tInode\n");
	printf("\nTamaño total: %i bytes\n", func(argv[1]));
	return EXIT_SUCCESS;
}