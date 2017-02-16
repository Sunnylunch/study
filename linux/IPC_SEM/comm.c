#include"comm.h"

static int commSemSet(int nums,int flags)
{
	key_t _k=ftok(PATHNAME,PROJID);
	if(_k==-1)
	{
		perror("ftok");
		return -1;
	}

	int semid=semget(_k,nums,flags);
	if(semid<0)
	{
		perror("semget");
		return -1;
	}

	return semid;

}

int creatSemSet(int nums)
{
	
	return commSemSet(nums,IPC_CREAT | IPC_EXCL | 0666);

}

int getSemSet()
{
	return commSemSet(0,0);
}


int initSemSet(int semid,int which)
{
	union SemUn _SemUn;
	_SemUn.val=1;
	if(semctl(semid,which,SETVAL,_SemUn)<0)
	{
		perror("semctl");
		return -1;
	}
	return 0;
}


static int SemOp(int semid,int op,int which)
{
	struct sembuf buf[1];
	buf[0].sem_op=op;
	buf[0].sem_num=which;
	if(semop(semid,buf,1)==-1)
	{
		perror("semop");
		return -1;
	}
	return 0;
}

int P(int semid)
{
	return SemOp(semid,-1,0);
}

int V(int semid)
{
	return SemOp(semid,1,0);
}



int destorySemSet(int semid)
{
	if(semctl(semid,0,IPC_RMID,NULL)==-1)
	{
		perror("semctl");
		return -1;
	}
	return 0;
}









