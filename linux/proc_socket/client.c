#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("usage:%s [ip] [port]\n",argv[0]);
		return 0;
	}

	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket");
		return 1;
	}
	struct sockaddr_in dst;
	dst.sin_family=AF_INET;
	dst.sin_port=htons(atoi(argv[2]));
	dst.sin_addr.s_addr=inet_addr(argv[1]);


	int connfd=connect(sock,(struct sockaddr*)&dst,sizeof(dst));
	if(connfd<0)
	{
		close(sock);
		perror("connect");
		return 2;
	}
	printf("connect success %d\n",sock);
	char buf[1024];
	while(1)
	{
		printf("client#");
		fflush(stdout);
		int s=read(0,buf,sizeof(buf)-1);
		if(s<0)
		{
			break;
		}
		buf[s]=0;
		int _s=write(sock,buf,s);
		if(_s<0)
		{
			continue;
		}
	}
	close(sock);
	return 0;
}
