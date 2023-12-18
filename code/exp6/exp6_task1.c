#include <stdio.h>
#include <signal.h>
#include<unistd.h>
#include <stdlib.h>


void myfunc(int no){
	printf("[processing	func]		pid: %d\n", getpid());
	if(no == SIGINT){
		printf("[processing 	func]		received SIGINT:%d.\n",no);
		exit(1);
	}
	else if(no == SIGUSR1){
		printf("[processing 	func]		received SIGUSR1:%d.\n",no);
	}
	else if(no == SIGUSR2){
		printf("[processing 	func]		received SIGUSR2:%d.\n",no);
	}
}

int main(){

	int pid;
	
	pid = fork();
	
	if(pid < 0){
		printf("failed to fork a child process!\n");
		return -1;
	}
	else if(pid == 0){
		// child
		printf("[child process]			pid: %d\n", getpid());
		signal(SIGUSR1, myfunc);
		signal(SIGUSR2, myfunc);
		for(;;) pause();
		
	}
	else {
		// father
		printf("[parent process]		pid: %d\n", getpid());
		signal(SIGINT, myfunc);
		for(;;) pause();
	}

	return 0;
}
