#include"comm.c"

int main()
{
	int Msgid=GetMsgQueue();
	char out[MYSIZE];
	char str[2*MYSIZE]={0};
	
	while(1)
	{
		printf("Pelese Enter#...");
		fflush(stdout);
	
		ssize_t size=read(0,out,sizeof(out)-1);
		
		if(size>0)
		{
			out[size-1]='\0';
			if(SndMsgQueue(Msgid,out,CLIENT)==-1)
			{
				exit(1);
			}
		}	

		ssize_t _s=RcvMsgQueue(Msgid,str,SERVE);
		if(_s>0)
		{	
			printf("SERVS# %s\n",str);
		}
		
	}
	return 0;
}
