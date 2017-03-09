#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>


int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("printf  [ip]  [port]\n");
		exit(1);
	}

	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in clientaddr;
	clientaddr.sin_family=AF_INET;
	clientaddr.sin_port=htons(atoi(argv[2]));
	clientaddr.sin_addr.s_addr=inet_addr(argv[1]);

	int connfd=connect(sock,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
	if(connfd<0)
	{
		perror("connet");
		return -1;
	}
	printf("connect success...\n");
	char buf[1024];
	while(1)
	{
		printf("client#  ");
		fflush(stdout);
	    ssize_t  s=read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			write(sock,buf,s-1);
		}
		else
		{
			break;
		}
	}
	close(sock);
	return 0;
}
