#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

void readfun();
void writefun();
char buffer[256];
int buffer_has_item= 0;
int retflag = FALSE;
pthread_mutex_t mutex;

int main(void)
{
	pthread_t reader;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&reader, NULL, (void *)&readfun, NULL);
	writefun();
	exit(0);
}

void readfun(void)
{
	while(1)
	{
		if(retflag)
			return;

		pthread_mutex_lock(&mutex);

		if(1 == buffer_has_item)
		{
			printf("%s", buffer);
			buffer_has_item = 0;
		}
		pthread_mutex_unlock(&mutex);
	}
	return;
}

void writefun(void)
{
	int i = 0;
	while(1)
	{
		if(10 == i)
		{
			retflag = TRUE;
			return;
		}

		pthread_mutex_lock(&mutex);
		if(0 == buffer_has_item)
		{
			sprintf(buffer, "This is %d\n", i++);
			buffer_has_item = 1;
		}
		pthread_mutex_unlock(&mutex);
	}
	return;
}
