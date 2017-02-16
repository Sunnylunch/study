#ifndef __COMM_H__
#define __COMM_H__

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#define PATHNAME "."
#define PROJID 0666

union SemUn
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

int creatSemSet(int nums);
int getSemSet();
int initSemSet(int semid,int which);
int P(int semid);
int V(int semid);
int destorySemSet(int semid);

#endif	
