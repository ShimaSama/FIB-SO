#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

void Usage(char *name){

	char buf[80];
	sprintf(buf,"Usage %s: %s N\n", name, name);
	write(2,buf,strlen(buf));
	exit(1);

}

void error_y_exit(char *msg){
	
	perror(msg);
	exit(1);

}

int main(int argc, char *argv[]){
	int max,i,pid, num, j, fd, pos;
	int npd=0;
	if(argc == 1){
		
		Usage(argv[0]);
		return 1;

	}
	max= atoi(argv[1]); //numero de hijos
	if(mknod("MIPIPE",S_IFIFO|0666,0)<0){ //crea pipe con nombre
		if(errno != EEXIST){ //existe
			perror("Error en mdnod");
			return 1;
		}
	}
	fd = open("salida.bin", O_RDWR|O_CREAT|O_TRUNC, 0640); //lectura y escritura propietario
	if(fd <0){

		perror("Error en open");
		return 1;
	}
	for(i=0; i<max; i++){

		pid=fork();
		if(pid==-1){

			perror("Error en fork");
			return 1;
		}
		else if(pid==0){ //child
			if((npd = open("MIPIPE", O_WRONLY))<0){ //abre la pipe en write porq solo escribe el hijo
				perror("Error en open WR pipe");
				return 1;
			}
			dup2(npd, 57); //lo q lee en el canal 57 lo pone en la pipe
			close(npd);
			execlp("./aleatorios","./aleatorios","100", NULL); //100 numeros aleatorios
			perror("Error en el execlp");
			return 1;
		}
		else { //padre
			if(npd==0){ //abrir una sola vez
				if((npd = open("MIPIPE", O_RDONLY))<0){
					perror("Error en open RD pipe");
					return 1;
				}
			}
			for(j=0; j<100; j++){
				read(npd,&num,sizeof(num)); //lee de la pipe
				write(fd, &num, sizeof(int)); //escribe a salida.bin

			}			
			if(waitpid(-1,NULL,0)<0){
				perror("Error en waitpid");
				return 1;
			}
			printf("Hijo %d finalizado\n",pid);
		}
	}
	close(npd); 
	pos = lseek(fd,0,SEEK_END)/ sizeof(int);
	pos = pos /2;
	lseek(fd, (pos)*sizeof(int), SEEK_SET);
	read(fd, &num, sizeof(int));
	printf("La mitad del fichero es el numero %d con valor %d\n", (pos), num);
	return 0;


}
