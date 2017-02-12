#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(void)
{
	pid_t pid;
	if((pid = fork()) < 0)
	{
		perror("fork error.\n");
		exit(0);
	}
	else if(0 < pid)
		printf("first child, pid = %d\n", pid);
	else if(0 == pid)
	{
		if((pid = fork()) < 0)
		{
			perror("fork error\n");
			exit(0);
		}
		else if(pid > 0)
		{
			printf("second child, pid = %d, parent pid = %d\n", pid, getpid());
			exit(0);
		}

		sleep(2);
		printf("second child, parent pid = %d\n", getppid());
		exit(0);
	}

	if(waitpid(pid, NULL, 0) != pid)
	{
		perror("waitpid error.\n");
		exit(0);
	}
	else
		printf("pid = %d thread dead\n", pid);

	return 0;
}
