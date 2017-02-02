#include <stdio.h>

int main(int argc, char * argv[])
{
	int temp, seektemp, i, j;
	FILE * fp;
	fpos_t ps;
	char wbuf[] = "this a test string!\n";

	if(argc!=2)
	{
		printf("usage: %s file", argv[0]);
	}

	fp = fopen(argv[1], "a+");

	for(i=0; i<3; i++)
	{
		j = sizeof(wbuf) * (i+1);
		fseek(fp, j, SEEK_SET);
		temp = fputs(wbuf, fp);
		fgetpos(fp, &ps);
		printf("current file end position is %ld \n", ps);
	}

	fclose(fp);
	
	return 0;
}
