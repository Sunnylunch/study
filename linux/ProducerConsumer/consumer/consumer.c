#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<assert.h>


typedef struct Node
{
	int data;
	struct Node * next;
}Node,*Node_p,**Node_pp;

Node_p CreatNode(int data)
{
	Node_p _n=(Node_p)malloc(sizeof(Node));
	if(_n==NULL)
	{
		return NULL;
	}
	_n->data=data;
	_n->next=NULL;
	return _n;
}

void Init(Node_pp list)
{
	*list=CreatNode(0);
}

void PushFront(Node_p list ,int data)
{
	assert(list);
	Node_p _n=CreatNode(data);
	if(_n==NULL)
	{
		perror("Push");
		return;
	}
	
	_n->next=list->next;
	list->next=_n;
}

void del_Node(Node_p del)
{
	assert(del);
	free(del);
}

void PopFront(Node_p list,int *data)
{
	if(!isEmpty(list))
	{
		Node_p del=list->next;
		list->next=del->next;
		*data=del->data;
		del_Node(del);
	}
	else
	{
		printf("list Empty\n");
	}
}

int isEmpty(Node_p list)
{
	assert(list);
	if(list->next==NULL)
		return 1;
	else
		return 0;
}

void destroy(Node_p list)
{
	int data;
	assert(list);
	while(!isEmpty(list))
	{
		PopFront(list,&data);
	}
	del_Node(list);
}

void ShowList(Node_p list)
{
	assert(list);
	Node_p cur=list->next;
	while(cur->next)
	{
		printf("%d->",cur->data);
		cur=cur->next;
	}
	printf("\n");
}


Node_p list=NULL;

pthread_mutex_t mylock= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mycond=PTHREAD_COND_INITIALIZER;

void * Consumer(void *arg)
{
	int data=0;
	while(1)
	{
	//	sleep(1);
		pthread_mutex_lock(&mylock);
		while(isEmpty(list))
		{
			pthread_cond_wait(&mycond,&mylock);
		}
		PopFront(list,&data);
		pthread_mutex_unlock(&mylock);
		printf("consumer:%d\n",data);
	}
	return NULL;
}

void * Producer(void *arg)
{
	int data=0;
	while(1)
	{
		usleep(123456);
		data=rand()%1000;
		pthread_mutex_lock(&mylock);
		PushFront(list,data);
		pthread_mutex_unlock(&mylock);
		pthread_cond_signal(&mycond);
		printf("Producer:%d\n",data);
	}
	return NULL;
}


int main()
{
//	int data=0;
//	Node_p list;
//	Init(&list);
//	int i=0;
//	for(i=0;i<10;i++)
//	{
//		PushFront(list,i);
//		ShowList(list);
//	}

//	for(;i>5;i--)
//	{
//		PopFront(list,&data);
//		ShowList(list);
//	}
//	destroy(list);

	Init(&list);

	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,Consumer,NULL);
	pthread_create(&tid2,NULL,Producer,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	
	destroy(list);
	return 0;
}
