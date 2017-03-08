#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

void * my_thread(void * arg)
{
	int retval = 0;
	pthread_attr_t attr;
	struct sched_param param;
	size_t stacksize;
	int detachstate;
	int scope;
	int inherit;
	int policy;

	if(0 == pthread_attr_init(&attr)){
		if(0 == pthread_attr_getstacksize(&attr, &stacksize))
			printf("StackSize: %d\n", stacksize);
		
		if(0 == pthread_attr_getdetachstate(&attr, &detachstate)){
			if(PTHREAD_CREATE_JOINABLE == detachstate)
				printf("DetachState: PTHREAD_CREATE_JOINABLE\n");
			if(PTHREAD_CREATE_DETACHED == detachstate)
				printf("DetachState: PTHREAD_CREATE_DETACHED\n");
		}

		if(0 == pthread_attr_getscope(&attr, &scope)){
			if(scope == PTHREAD_SCOPE_PROCESS)
				printf("Scope: PTHREAD_SCOPE_PROCESS\n");
			if(scope == PTHREAD_SCOPE_SYSTEM)
				printf("Scope: PTHREAD_SCOPE_SYSTEM\n");
		}
		pthread_exit(&retval);
	}
}

int main(void)
{
	int count;
	pthread_t thread;
	int * retval;

	if(0 != pthread_create(&thread, NULL, my_thread, (void *)NULL)){
		printf("Count not create thread!\n");
		return -1;
	}

	if(0 != pthread_join(thread, (void **)(&retval))){
		printf("No thread to join!\n");
		return -2;
	}

	return 0;
}
