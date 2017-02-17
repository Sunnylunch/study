#ifndef __COMM_H__
#define __COMM_H__

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#define PATHNAME "."
#define PROJID 0666
#define SIZE 4096*1

int creatshm();
int getshm();
char *atshm(int shmid);
int dtshm(const void* shmaddr);
int destroyshm(int shmid);

#endif
