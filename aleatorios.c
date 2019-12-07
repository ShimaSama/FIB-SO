#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char vec[1048576];

void Usage(char *name){

	char buf[80];
	sprintf(buf,"Usage %s: %s cantidad de numeros aleatorios\n", name, name);
	write(2,buf,strlen(buf));
	exit(1);

}

void error_y_exit(char *msg){
	
	perror(msg);
	exit(1);

}

int main(int argc, char *argv[]){
	
	if(argc==1){
		
		Usage(argv[0]);
		return 1;
	}
	int num,len;
	srand(getpid());
	char buf[256];	
	int N = atoi(argv[1]);
	int i=0;
	while(i<N){
		num= rand()% 1048576;
		if(vec[num]!='0'){
			vec[num]='1';
			++i;
			len=sprintf(buf, "num %d\n ", num);
			write(57, buf , len);
		//	write(57, &num, sizeof(int));
		}	
	}
	return 0;
		
	//sprintf(buf, "%d", N);
	//write(1, buf, sizeof(int));



}
