#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	printf("The current process ID is %d\n", getpid());
	printf("The parent process ID is %d\n", getppid());
	printf("The user ture ID is %d\n", getuid());
	printf("The valid user ID is %d\n", geteuid());
	printf("The group ID is %d\n", getgid());
	printf("The valid group ID is %d\n", getegid());

	return 0;
}
