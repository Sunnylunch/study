
#include"comm.c"
int main()
{
	char out[MYSIZE*2]={0};

	int Msgid=CreatMsgQueue();
	
	while(1)
	{
		sleep(10);
		if(RcvMsgQueue(Msgid,out,CLIENT)==-1)
		{
			exit(1);
		}
		printf("client# %s\n",out);


		if(SndMsgQueue(Msgid,out,SERVE)==-1)
		{
			exit(1);
		}
	}

	DestoryMsgQueue(Msgid);
	return 0;
}
