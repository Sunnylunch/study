#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

void* fun(void* arg)
{
	int connfd=*(int*)arg;
	while(1)
	{
		char buf[1024];
		ssize_t s=read(connfd,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s-1]=0;
 			printf("client# %s\n",buf);
		}
		else
		{
			break;
		} 
	}
	close(connfd);
	return NULL;
}

int startup(char* ip,int port)
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("sock");
		exit(1);
	}

	int opt=1;
	if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt))<0)
	{
		perror("setsockopt");
		exit(1);
	}
	
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(port);
	local.sin_addr.s_addr=inet_addr(ip);

	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
		exit(1);
	}

	if(listen(sock,5)<0)
	{
		perror("listen");
		exit(1);
	}
	return sock;
}

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("usage:%s [ip]] [port]\n",argv[0]);
		return 0;
	}

	int sock=startup(argv[1],atoi(argv[2]));
	
	struct sockaddr_in peer;
	int len=0;
	while(1)
	{
		int connfd=accept(sock,(struct sockaddr*)&peer,&len);
		if(connfd<0)
		{
			 perror("accept");
			 continue;
		}
		printf("%s:%d\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
		pthread_t tid;
	int ret=pthread_create(&tid,NULL,fun,(void*)&connfd);
		if(ret<0)
		{
			close(connfd);
			perror("pthread_create\n");
			continue;
		}
		pthread_detach(tid);
	}
	return 0;
}
