#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

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
	int max,i,pid, pd[2], num, j, fd, pos;

	if(argc == 1){
		
		Usage(argv[0]);
		return 1;

	}
	max= atoi(argv[1]); //numero de hijos
	if(pipe(pd)<0){ //crea pipe sin nombre

		perror("Error en pipe");
		return 1;
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
			dup2(pd[1], 57); //lo q lee en el canal 57 lo pone en la pipe
			close(pd[0]);
			close(pd[1]);
			execlp("./aleatorios","./aleatorios","100", NULL); //100 numeros aleatorios
			perror("Error en el execlp");
			return 1;
		}
		else { //padre
			for(j=0; j<100; j++){
				read(pd[0],&num,sizeof(num)); //lee de la pipe
				write(fd, &num, sizeof(int)); //escribe a salida.bin

			}			
			if(waitpid(-1,NULL,0)<0){
				perror("Error en waitpid");
				return 1;
			}
			printf("Hijo %d finalizado\n",pid);
		}
	}
	close(pd[0]); close(pd[1]);
	pos = lseek(fd,0,SEEK_END)/ sizeof(int);
	pos = pos /2;
	lseek(fd, (pos)*sizeof(int), SEEK_SET);
	read(fd, &num, sizeof(int));
	printf("La mitad del fichero es el numero %d con valor %d\n", (pos), num);
	return 0;


}
