/*************************************************************************
	> File Name: shm.c
	> Author:Sunnylunch
	> Mail:2401503224.com 
	> Created Time: Thu 16 Feb 2017 05:00:48 PM PST
 ************************************************************************/

#include"comm.c"

int main()
{
	int shmid=getshm();
	char* buf=(char*)atshm(shmid);
	printf("%s\n",buf);
	dtshm(buf);

	return 0;
}
