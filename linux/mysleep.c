/*************************************************************************
	> File Name: test.c
	> Author:Sunnylunch
	> Mail:2401503224.com 
	> Created Time: Thu 23 Feb 2017 12:22:40 AM PST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>

void sig_alarm(int argc)
{
	//default
}

int mysleep(int n)
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGALRM);
	struct sigaction act,oact;
	act.sa_handler=sig_alarm;
	act.sa_flags=0;

	sigaction(SIGALRM,&act,&oact);
	alarm(n);
	pause();
	int ret=alarm(0);
	sigaction(SIGALRM,&oact,NULL);
	return ret;
}

int main()
{
	while(1)
	{
		mysleep(1);
		printf("me sleep\n");
	}
	return 0;
}
