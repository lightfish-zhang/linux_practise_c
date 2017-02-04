#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	int i = 0;
	int child;

	printf("Before create son, the father's i is %d\n", i);

	if(!(child = vfork()))
	{
		int i;
		for(; i<100; i++)
		{
			printf("This is son, the i is %d\n", i);
			if(10 == i)
				exit(1);
		}

	}else{
		printf("After son, this is father, his pid is %d and the i is %d, and the child is %d\n", getpid(), i, child);
	}
	
	return 0;
}
