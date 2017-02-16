#include"comm.h"

int CommMsgQueue(int flag)
{

	key_t key=ftok(PATHNAME,PROJ_ID);
	if(key==-1)
	{
		perror("ftok");
		return 0;
	}
	
	int Msgid=msgget(key,flag);

	if(Msgid<0)
	{
		perror("msgget");
		return -1;
	}
		return Msgid;

}

int CreatMsgQueue()
{
	return CommMsgQueue(IPC_CREAT | IPC_EXCL);
}

int GetMsgQueue()
{	
	return CommMsgQueue(IPC_CREAT);
}

int RcvMsgQueue(int Msgid,char out[],long type)
{
	struct _msginfo buf;
	ssize_t size=msgrcv(Msgid,&buf,sizeof(buf),type,0);
	strncpy(out,buf.mtext,size);
	if(size==-1)
	{
		perror("msgrcv");
		return -1;
	}
	return size;
}


int SndMsgQueue(int Msgid,char out[],long type)
{
	struct _msginfo buf;
	buf.mtype=type;
	strncpy(buf.mtext,out,strlen(out)+1);
	ssize_t size=msgsnd(Msgid,&buf,sizeof(buf),0);
	if(size==-1)
	{
		perror("msgsnd");
		return -1;
	}
	return size;
}


int DestoryMsgQueue(int Msgid)
{
	if(msgctl(Msgid,IPC_RMID ,0)<0)
	{
		perror("msgctl");
		return -1;
	}
	return Msgid;
}

