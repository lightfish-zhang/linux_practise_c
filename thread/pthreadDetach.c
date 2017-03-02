#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void * func(void * arg)
{
	int i = * (int *)(arg);
	printf("I'am worker:%d\n", i);
}

int main(void)
{
	pthread_t tid;
	int j;
	int count = 10000;
	for(j=0; j<count; j++)
	{
		int *p = &j;
		int ret = pthread_create(&tid, NULL, func, (void*)p);
		if(ret)
			printf("create thread error:%d\n", ret);
		else
			pthread_detach(tid);
	}
	return 0;
}
