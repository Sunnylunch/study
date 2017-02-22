/*************************************************************************
	> File Name: semaphore.c
	> Author:Sunnylunch
	> Mail:2401503224.com 
	> Created Time: Tue 21 Feb 2017 09:00:23 AM PST
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define SIZE 10

int databuf[SIZE];
sem_t blanks;
sem_t datas;

pthread_mutex_t mylock=PTHREAD_MUTEX_INITIALIZER;

void* producer(void *arg)
{
	static int i=0;
	while(1)
	{	
		sem_wait(&blanks);	
		pthread_mutex_lock(&mylock);
		databuf[i]=rand()%1000;
		printf("thread_id:%lu  producer:%d  i:%d\n",pthread_self(),databuf[i],i);
		i++;
		i=i%SIZE;
		sem_post(&datas);
		pthread_mutex_unlock(&mylock);
	}
	return NULL;
}


void* consumer(void *arg)
{
	static int i=0;
	while(1)
	{
		sem_wait(&datas);
		pthread_mutex_lock(&mylock);
		int data=databuf[i];	
		printf("thread_id:%lu  consumer: %d  i:%d\n",pthread_self(),data,i);
		i++;
		i=i%SIZE;
		sem_post(&blanks);
		pthread_mutex_unlock(&mylock);	
	}

	return NULL;
}




int main()
{

	sem_init(&blanks,0,SIZE);
	sem_init(&datas,0,0);
	
	pthread_t producer_id1,consumer_id1;	
	pthread_t producer_id2,consumer_id2;
	
	
	pthread_create(&producer_id1,NULL,producer,NULL);
	pthread_create(&consumer_id1,NULL,consumer,NULL);


	pthread_create(&producer_id2,NULL,producer,NULL);
	pthread_create(&consumer_id2,NULL,consumer,NULL);


	pthread_join(producer_id1,NULL);
	pthread_join(consumer_id1,NULL);
	
	
	pthread_join(producer_id2,NULL);
	pthread_join(consumer_id2,NULL);

	sem_destroy(&blanks);
	sem_destroy(&datas);
	return 0;
}
