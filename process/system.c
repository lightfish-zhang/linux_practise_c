#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

void pr_system(char * command)
{
	printf("system(%s):\n", command);
	int status;
	if( (status = system(command)) < 0)
	{
		perror("system error");
		exit(0);
	}
	printf("exit status = %d \n\n", status);
}

int main()
{
	pr_system("date");
	pr_system("nosuchcommand");
	pr_system("who; exit 44");
	return 0;
}
