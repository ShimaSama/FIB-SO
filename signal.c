#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
int to;
void error_y_exit(char *msg,int exit_status)
{
    perror(msg);
    exit(exit_status);
}

void trata_alarma(int s){
	kill(to,SIGUSR1);
	int ret= waitpid(to,NULL,WNOHANG);
	if (ret<0) write(1, "error \n", 6);
	exit(0);
}

int main(int argc,char *argv[]){
	
	int to=atoi(argv[1]);
	struct sigaction sa;
	 sigset_t mask;

    	 sa.sa_handler = &trata_alarma;
  	 sa.sa_flags = SA_RESTART;
    	sigfillset(&sa.sa_mask);
	 if (sigaction(SIGALRM, &sa, NULL) < 0) error_y_exit("sigaction", 1);
	
//	sigfillset(&mask);
   //    / sigdelset(&mask, SIGALRM);
     
	alarm(1);
	sigsuspend(&mask);
}
