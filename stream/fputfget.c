#include <stdio.h>
#include <errno.h>

int main(int argc, char * argv[])
{
	int c;
	printf("pls enter some str, CTRL+D to send EOF\n");

	while( (c = getc(stdin)) != EOF )
	{
		if( putc(c, stdout) == EOF )
		{
			perror("output error");
		}
	}

	if(ferror(stdin))
		perror("input error");

	return 0;
}
