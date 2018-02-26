#include <stdio.h>
#include "buffer.h"
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int insert_item(buffer_item item);
int remove_item(buffer_item *item);
buffer_item buffer[BUFFER_SIZE];

int empty = BUFFER_SIZE;
int full = 0;

pthread_mutex_t mutex;

void *producer_entry(void *param)
{
	buffer_item item;
	
		pthread_mutex_init(&mutex, NULL);	
        	pthread_mutex_lock(&mutex);
		item = rand();
		if(insert_item(item))
			printf("error\n");
		else
			printf("producer produced %d\n", item);
		pthread_mutex_unlock(&mutex);
		
}

void *consumer_entry(void *param)
{
	
	buffer_item item;
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	if(remove_item(&item))
	{
		printf("consumer consumed &d\n", item);
	}
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[])
{
	//get command line args
	if(argc < 4)
	{
		printf("Usage: not enough arguments\n");
		exit(1);
	}
	
	
	int time, numProd, numCons;
	time = atoi(argv[1]);
	numProd = atoi(argv[2]);
	numCons = atoi(argv[3]);
	printf("SLEEPTIME: %d seconds\nPRODUCERS: %d\nCONSUMERS %d\n", time, numProd, numCons);	
	


	//create producer thread
	
	unsigned long i = 0;	
	
	pthread_t tid[numProd + numCons];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	int err;
	while(i < numProd)
	{
		err = pthread_create(&tid[i], &attr, producer_entry, NULL);	
		if(err != 0)
			printf("\ncant create thread: [%s]", strerror(err));
		else
			printf("\nproducer thread created\n");
		i++;
	}
	//sleep
	i = 0;
	while(i < numCons)
	{

		err = pthread_create(&tid[i], &attr, consumer_entry, NULL);	
		if(err != 0)
			printf("\ncant create thread: [%s]", strerror(err));
		else
			printf("\nconsumer thread created\n");
		i++;

	}
	sleep(10);
	//exit
	
	return 0;

}

int insert_item(buffer_item item)
{
	if(full == BUFFER_SIZE)
	{
		printf("FULL\n");
		return -1;	
	}
	buffer[full] = item;
	++full;
	--empty;
	return 0;
}

int remove_item(buffer_item *item)
{
	if(empty == BUFFER_SIZE)
	{
		printf("EMPTY\n");
		return -1;
	}
	*item = buffer[full];
	--full;
	++empty;
	return 0;
}
