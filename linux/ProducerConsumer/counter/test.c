#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int count=0;

void * Counter(void *arg)
{
	int i=0;
	int val=0;
	while(i<5000)
	{
		val=count;
		printf("thread id=%lu, count=%d\n",pthread_self(),val+1);
		count=val+1;
		i++;
	}	
	return NULL;
}


int main()
{
	pthread_t tid1,tid2;
	
	pthread_create(&tid1,NULL,Counter,NULL);
	pthread_create(&tid2,NULL,Counter,NULL);
	
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	
	printf("count=%d\n",count);
	return 0;
}
