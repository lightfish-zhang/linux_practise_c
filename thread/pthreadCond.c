#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 4
#define OVER (-1)

struct producers
{
	int buffer[BUFFER_SIZE];
	pthread_mutex_t lock;
	int readpos, writepos;
	pthread_cond_t notempty, notfull;
};

void init(struct producers * b)
{
	pthread_mutex_init(&b->lock, NULL);
	pthread_cond_init(&b->notempty, NULL);
	pthread_cond_init(&b->notfull, NULL);
	b->readpos = 0;
	b->writepos = 0;
}

void put(struct producers * b, int data)
{
	//two while do the same thing,the first is better, it will sleep, the second will circular and take up cpu

//	pthread_mutex_lock(&b->lock);
//	while((b->writepos +1) % BUFFER_SIZE == b->readpos)
//		pthread_cond_wait(&b->notfull, &b->lock);

	while(1){
		pthread_mutex_lock(&b->lock);
		if((b->writepos +1) % BUFFER_SIZE == b->readpos){
			pthread_mutex_unlock(&b->lock);
		}else{
			break;
		}
	}

	b->buffer[b->writepos] = data;
	b->writepos ++;
	if(BUFFER_SIZE <= b->writepos)
		b->writepos = 0;

	pthread_cond_signal(&b->notempty);
	pthread_mutex_unlock(&b->lock);
}

int get(struct producers * b)
{
	int data;
	pthread_mutex_lock(&b->lock);

	while(b->writepos == b->readpos)
		pthread_cond_wait(&b->notempty, &b->lock);

	data = b->buffer[b->readpos];
	b->readpos++;

	if(b->readpos >= BUFFER_SIZE)
		b->readpos = 0;

	pthread_cond_signal(&b->notfull);
	pthread_mutex_unlock(&b->lock);
	return data;
}

struct producers buffer;

void * producer(void * data)
{
	int n;
	for(n=0;n<10;n++)
	{
		printf("Producer: %d-->\n", n);
		put(&buffer, n);
	}
	put(&buffer, OVER);
	return NULL;
}

void * consumer(void * data)
{
	int d;
	while(1)
	{
		d = get(&buffer);

		if(OVER == d)
			break;

		printf("Consumer: --> %d\n", d);
	}
	return NULL;
}

int main(void)
{
	pthread_t tha, thb;
	void * retval;
	init(&buffer);
	pthread_create(&tha, NULL, producer, 0);
	pthread_create(&thb, NULL, consumer, 0);
	pthread_join(tha, &retval);
	pthread_join(thb, &retval);
	return 0;
}
