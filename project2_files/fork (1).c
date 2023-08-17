#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	pid_t retVal;

	retVal = fork();
	if(retVal < 0){
		printf("fork() failed\n");
		return 1;
	}
	else if(retVal == 0){
		printf("fork1 retVal == 0 ");
		printf("in child process pid = %d \n", getpid());
		sleep(5);
		printf(" finished sleeping\n" );
	}
	else{
		printf("parent pid = %d \n", getpid());
		printf("fork1 in parent process waiting for child ...\n");
		wait(NULL);
		printf("wait() finished in parent proces \n");
	}
	return 0;
}
