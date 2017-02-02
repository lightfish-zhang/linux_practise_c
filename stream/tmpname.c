#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#define MAXLINE 4096

int main(int argc, char * argv[])
{
	char name[L_tmpnam], line[MAXLINE];
	FILE *fp;

	printf("%s\n", tmpnam(NULL));
	tmpnam(name);
	printf("%s\n", name);
	if((fp = tmpfile()) == NULL)
	{
		perror("tmpfile error");
	}
	fputs("this is a test of tempfile!\n", fp);
	rewind(fp);

	if(fgets(line, sizeof(line), fp) == NULL)
	{
		perror("fgets error");
	}
	fputs(line, stdout);
	
	return 0;
}
