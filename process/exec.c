#include <stdio.h>

int main(int argc, char * argv[], char * envp[])
{
	printf("This is argc\n%d\n", argc);
	printf("This is argv\n");

	while(*argv)
	{
		printf("%s\n", *(argv++));
	}

	printf("This is envp\n");
	while(*envp)
	{
		printf("%s\n", *(envp++));
	}

	return 0;
}
