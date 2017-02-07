#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void pr_exit(int status)
{
	if(WIFEXITED(status))
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if(WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),

#ifdef WCOREDUMP
		WCOREDUMP(status) ? " (core file generated)" : "");
#else
		"");
#endif
	else if(WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int main(void)
{
	pid_t pid;
	int status;

	if((pid = fork()) <0)
		perror("fork error");
	else if(0 == pid)
		exit(7);

	if(wait(&status) != pid)
		perror("wait error");

	pr_exit(status);

	if((pid = fork())<0)
		perror("fork error");
	else if(0 == pid)
		abort();

	if(wait(&status) != pid)
		perror("wait error");

	pr_exit(status);

	if((pid = fork()) < 0)
		perror("fork error");
	else if(0 == pid)
		status /= 0; //on purpose, make error

	if(wait(&status) != pid)
		perror("wait error");

	pr_exit(status);
	return 0;
}
