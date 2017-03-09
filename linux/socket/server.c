#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int startup(const char *ip,const char* port)
{
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in serveraddr;
    serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(atoi(port));
	serveraddr.sin_addr.s_addr=inet_addr(ip);

	if(bind(sock,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0)
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


int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("plese printf [ip] [port]");
		return 3;
	}
	int lis_sock=startup(argv[1],argv[2]);
	
	while(1)
	{
		socklen_t len=0;
		struct sockaddr_in routme;
		int connfd=accept(lis_sock,(struct sockaddr*)&routme,&len);

		if(connfd<0)
		{
			continue;
		}
		printf("client link ip:%s port:%d\n ",\
			inet_ntoa(ntohl(routme.sin_addr.s_addr)),ntohs(routme.sin_port));
		
		char buf[1024];
		while(1)
		{
			ssize_t s=read(connfd,buf,sizeof(buf)-1);
			if(s<=0)
			{
				break;
			}
			buf[s]=0;
			printf("client# %s\n",buf);
		}
				
		close(connfd);
	}
	return 0;
}
