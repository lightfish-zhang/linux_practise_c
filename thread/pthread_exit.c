#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void print_message(char * ptr);

int main()
{
	pthread_t thread1, thread2;
	char * msg1 = "This is the first thread!\n";
	char * msg2 = "This is the second thread!\n";

	pthread_create(&thread1, NULL, (void *)(&print_message), (void *)msg1);
	pthread_create(&thread2, NULL, (void *)(&print_message), (void *)msg2);

	sleep(1);
	return 0;
}

void print_message(char * ptr)
{
	int retval;
	printf("Thread ID : %lx\n", pthread_self());
	printf("%s", ptr);
	pthread_exit(&retval);
}
