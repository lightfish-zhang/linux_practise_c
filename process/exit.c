#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char * argv[])
{
	pid_t pid;

	if((pid = fork()) == -1)
	{
		perror("failed to create a new process\n");
		exit(0);
	}
	else if(0 == pid)
	{
		printf("This is child process, output begin\n");
		printf("This child process, content in buffer");
		// there is not '\n', then buffer had no output
		exit(0);
		// function exit() will make buffer have to output and delete buffer
	}
	else
	{
		printf("\nparent process, output begin\n");
		printf("parent process, content in buffer");
		// there is not '\n', then buffer had no output
		_exit(0); 
		// function _exit() will lose buffer, buffer won't output' 
	}
	return 0;
}
