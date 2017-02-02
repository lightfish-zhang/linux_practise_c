#include <stdio.h>

int main(int argc, char *argv[])
{
	int temp, seektemp, i, j;
	FILE *fp;
	char wbuf[] = "this is a test!\n";

	if(argc !=2)
	{
		printf("usage: %s file\n", argv[0]);
		return 1;
	}

	fp = fopen(argv[1], "a+b");

	for(i=1; i<4; i++)
	{
		j = sizeof(wbuf) * (i+1);
		fseek(fp, j, SEEK_SET);
		temp = fputs(wbuf, fp);
	}
	fclose(fp);
	return 0;
}
