#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define MAXLINE 4096

int main(int argc, char *argv[])
{
	char buf[MAXLINE];

	printf("pls enter some str, CTRL+D to send EOF\n");

	while(fgets(buf, MAXLINE, stdin) != NULL)
	{
		if(fputs(buf, stdout)==EOF)
		{
			perror("output error");
		}
	}

	if(ferror(stdin))
	{
		perror("input error");
	}

	return 0;
}
