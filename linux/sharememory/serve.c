/*************************************************************************
	> File Name: shm.c
	> Author:Sunnylunch
	> Mail:2401503224.com 
	> Created Time: Thu 16 Feb 2017 05:00:48 PM PST
 ************************************************************************/

#include"comm.c"

int main()
{
	int shmid=creatshm();
	
	char* buf=(char*)atshm(shmid);
	int i=0;
	while(i<(SIZE-1))
	{
		buf[i]='A';
		i++;
	}	
	buf[SIZE-1]='\0';
	dtshm(buf);
	
//	destroyshm(shmid);
	return 0;
}
