#include"comm.c"

int main()
{
	int semid=creatSemSet(1);
	initSemSet(semid,0);
	pid_t id=fork();
	
	if(id==0)
	{
		int semid=getSemSet();
		while(1)
		{
			P(semid);
			printf("A");
			fflush(stdout);
			usleep(10031);
			printf("A");
			fflush(stdout);
			usleep(10021);
			V(semid);
		}
	}
	else
	{
		while(1)
		{
			P(semid);
			printf("B");
			fflush(stdout);
			usleep(10051);
			printf("B");
			fflush(stdout);
			usleep(10003);
			V(semid);
		}
	}

	destorySemSet(semid);

}
