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

int main(int argc, char *argv[])
{
	if(argc<3) {
		printf("\nSintaxis de ejecucion: ./xxxx pathname permisions\n\n");
		exit(EXIT_FAILURE);
	}

	int perm = (int) strtol(argv[2], NULL, 8);
	int old_perm;
	DIR* dir;
	struct dirent* entrada;
	char str[PATH_MAX];
	struct stat atributos;


	if((dir = opendir(argv[1])) == NULL) {
		perror("\nError en opendir");
		exit(EXIT_FAILURE);
	}

	while((entrada=readdir(dir)) != NULL){
		sprintf(str, "%s/%s", argv[1], entrada->d_name);
		if(!strcmp(entrada->d_name, ".") || !strcmp(entrada->d_name, "..")){
			continue;
		}

		if(stat(str,&atributos) < 0) {
			printf("\nError al intentar acceder a los atributos de archivo1");
			perror("\nError en lstat");
			exit(EXIT_FAILURE);
		}
		old_perm = atributos.st_mode & 07777;
		if(chmod(str,perm) < 0) {
			printf("\n%s : %i : %o\n", str, errno, old_perm);
			perror("\nError en chmod para archivo2");
			exit(EXIT_FAILURE);
		}
		printf("%s : %o : %o\n", str, old_perm, perm);
	}
	return EXIT_SUCCESS;
}