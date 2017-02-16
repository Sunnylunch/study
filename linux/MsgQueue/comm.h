#ifndef __COMM_H__
#define __COMM_H_
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define PATHNAME "."
#define PROJ_ID 666
#define MYSIZE 128
#define CLIENT 1
#define SERVE 2

struct _msginfo
{
	long mtype;
	char mtext[MYSIZE];
};

int CommMsgQueue(int flag);
int CreatMsgQueue();
int GetMsgQueue();

int RcvMsgQueue(int Msgid,char out[],long type);

int SndMsgQueue(int Msgid,char out[],long type);

int DestoryMsgQueue(int Msgid);


#endif 
