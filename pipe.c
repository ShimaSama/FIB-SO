#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	int fd_pipe[2];
	pipe(fd_pipe);

	int pid = fork();
       	// first son pid == 0;

	// first son executes the pipe
	if (pid == 0){

		dup2(fd_pipe[1],1);
		execlp("ls", "ls", NULL);
		exit(0);
	}

	else {
		char buff[100];
		write(1,"soc el señor\n",14); 
		dup2(fd_pipe[0],0);
		while(read(fd_pipe[0],&buff, 100) > 0)
			write(1,&buff,strlen(buff));
	}
}
