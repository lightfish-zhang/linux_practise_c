#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#if 0

char * str_accumulate(char * s)
{
	static char accu[1024] = {0};
	strcat(accu, s);
	return accu;
}

#endif

static pthread_key_t str_key;
static pthread_once_t str_alloc_key_once = PTHREAD_ONCE_INIT;
static void str_alloc_key();
static void str_alloc_destory_accu(void * accu);

char * str_accumulate(const char *s)
{
	char * accu;
	pthread_once(&str_alloc_key_once, str_alloc_key);
	accu = (char *)pthread_getspecific(str_key);
	if(NULL == accu)
	{
		accu = malloc(1024);
		if(NULL == accu) return NULL;
		accu[0] = 0;
		pthread_setspecific(str_key, (void *)accu);
		printf("Thread %lx:")
	}
}
