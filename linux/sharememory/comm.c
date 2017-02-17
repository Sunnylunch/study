/*************************************************************************
	> File Name: shm.c
	> Author:Sunnylunch
	> Mail:2401503224.com 
	> Created Time: Thu 16 Feb 2017 05:00:48 PM PST
 ************************************************************************/

#include"comm.h"

static int commshm(int flags)
{
	key_t _k=ftok(PATHNAME,PROJID);
	if(_k==-1)
	{
		perror("ftok");
		return -1;
	}
	int shmid=shmget(_k,SIZE,flags|0666);
	if(shmid==-1)
	{
		perror("shmget");
		return -1;
	}
	return shmid;
}


int creatshm()
{
	int shmid=commshm(IPC_CREAT | IPC_EXCL);
	return shmid;
}

int getshm()
{

	int shmid=commshm(IPC_CREAT);
	return shmid;
}

char *atshm(int shmid)
{
	char* addr=shmat(shmid,NULL,0);
	return (char*)addr;
}

int dtshm(const void* shmaddr)
{
	return shmdt(shmaddr);
}

int destroyshm(int shmid)
{
	if(shmctl(shmid,IPC_RMID,NULL)<0)
	{
		perror("shmctl");
		return -1;
	}
	return 0;
}

