#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	int i;
	FILE *fp;
	
	if(argc <= 1)
	{
		printf("usage: %s file \n", argv[0]);
		exit(0);
	}

	fp = fopen(argv[1], "w");
	fgetc(fp);
	printf("%d \n", ferror(fp));
	perror("Error, fgetc empty file");

	fputs("some test data", fp);
	fclose(fp);

	fp = fopen(argv[1], "r");
	printf("%d %d\n", ferror(fp), feof(fp));
	// set fp at the end of file
	fseek(fp, 0, SEEK_END);
	fgetc(fp);

	if(feof(fp))
	{
		printf("file end\n");
	}
	printf("%d %d\n", ferror(fp), feof(fp));

	clearerr(fp);
	printf("%d %d\n", ferror(fp), feof(fp));
	fclose(fp);

	return 0;
}
