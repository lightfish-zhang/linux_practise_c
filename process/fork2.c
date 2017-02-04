#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int glob = 6;
char buf[] = "write to stdout\n";

int main(void)
{
	int var;
	pid_t pid;
	var = 88;
	if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
	{
		perror("write error");
	}
	printf("before fork\n");

	if((pid = fork()) == 0)
	{
		glob ++;
		var ++;
	}else{
		sleep(2);
	}

	printf("pid = %d, ppid = %d, glob = %d, var = %d\n", getpid(), getppid(), glob, var);

	return 0;
}
