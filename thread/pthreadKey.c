// this is the test code for pthread_key 
#include <stdio.h> 
#include <pthread.h> 

pthread_key_t key;	// 私有数据，全局变量

void echomsg(void *t) 
{ 
	printf("[destructor] thread_id = %lu, param = %p\n", pthread_self(), t); 
} 

void *child1(void *arg) 
{ 
	int i = 10;

	pthread_t tid = pthread_self(); //线程号
	printf("\nset key value %d in thread %lu\n", i, tid); 

	pthread_setspecific(key, &i); // 设置私有数据

	printf("thread one sleep 2 until thread two finish\n\n");
	sleep(2); 
	printf("\nthread %lu returns %d, add is %p\n",
			tid, *((int *)pthread_getspecific(key)), pthread_getspecific(key) ); 
} 

void *child2(void *arg) 
{ 
	int temp = 20;

	pthread_t tid = pthread_self();  //线程号
	printf("\nset key value %d in thread %lu\n", temp, tid); 

	pthread_setspecific(key, &temp); //设置私有数据

	sleep(1); 
	printf("thread %lu returns %d, add is %p\n", 
			tid, *((int *)pthread_getspecific(key)), pthread_getspecific(key)); 
} 

int main(void) 
{ 
	pthread_t tid1,tid2; 
	pthread_key_create(&key, echomsg); // 创建

	//一般情况下，线程在主函数创建，函数分配在栈区，遵循先进后出规则，先创建后运行。
	pthread_create(&tid1, NULL, child1, NULL); 
	pthread_create(&tid2, NULL, child2, NULL); 
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	pthread_key_delete(key); // 注销

	return 0; 
} 
