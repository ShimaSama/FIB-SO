#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void Usage() {
	
	char buf[200];
	sprintf(buf,"Usage:listaParametrosarg1 [arg2..argn]Este programa escribe por su salida la lista de argumentos que recibe\n");
	write(1,buf,strlen(buf));
	exit(1);
}

int main(int argc,char *argv[]) {

	char buf[80];
	int i = 0;
	for (;i<argc;i++){
		if (i!=0) {
			sprintf(buf,"El argumento %d es %s\n",i,argv[i]);
			write(1,buf,strlen(buf));
		}
	}
	
	if (i == 1) Usage();
	return 0;
}
