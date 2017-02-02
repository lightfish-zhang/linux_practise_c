/*
 * example, int to string
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	char s[64];
	int offset = 0;
	int i;
	srand(time(0));

	for(i = 0; i<10; i++)
	{
		offset += sprintf(s+offset, "%d, ", rand()%100);
	}
	s[offset-1] = '\n';
	printf(s);
	return 0;
}
