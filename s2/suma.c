#include "mis_funciones.h"



int main(int argc, char *argv[]){

	char buf[80];
	int suma = 0;
	for(int i=1; i<argc; i++){
		if(esNumero(argv[i])) suma += mi_atoi(argv[i]);
		else {
			sprintf(buf, "Error: el parámetro “%s” no es un número\n",argv[i]);
			write(1,buf,strlen(buf));
			exit(1);
		}
	}
	sprintf(buf, "La suma es %d\n", suma);
	write(1,buf,strlen(buf));
}
