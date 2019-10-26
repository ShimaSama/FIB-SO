#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void error_y_exit(char *msg,int exit_status)
{
    perror(msg);
    exit(exit_status);
}
 
int main(int argc,char *argv[]){
	
	char buf[80];
	int n=atoi(argv[1]);
	int pidh[10];
	int t=getpid();

	for(int i=0; i<n; i++){
		pidh[i]=fork();
		if(pidh[i]==0 && i!=0){
		
			sprintf(buf, "PID hermano mayor: %d\n", pidh[i-1]);
			write(1,buf,strlen(buf));
			exit(0);

		}
		else if(pidh[i]==0 && i==0){
		
			sprintf(buf, "PID padre: %d\n", t);
			write(1,buf,strlen(buf));
			exit(0);
	
		}
		else if(pidh[i]<0) error_y_exit("error en el fork", 1);


	}
	for(int i=0; i<n; i++){
	
		waitpid(pidh[i], NULL,0);

	}
	write(1,"fin",3);
}
