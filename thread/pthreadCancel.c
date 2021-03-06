#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void * thread_func(void * arg)
{
	int * val = arg;
	printf("Hi, I'm a thread!\n");

	if(NULL != arg)
		while(1)
			printf("argument set: %d\n", *val);
}

int main(void)
{
	pthread_t tid;
	int t_arg = 10;

	if(pthread_create(&tid, NULL, thread_func, &t_arg))
		perror("Fail to create thread");

	sleep(1);
	printf("Main thread!\n");
	pthread_cancel(tid);

	return 0;
}
