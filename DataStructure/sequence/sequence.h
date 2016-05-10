#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<stdlib.h>
#define MAXSIZE 20
typedef int ElemType;
typedef struct
{
	ElemType data[MAXSIZE];
	int last;
}SeqList;

void creat(SeqList *L);                               //创建顺序表

int InsertSList(SeqList  *L, int i, int x);          //在i位置插入x

int DeleteList(SeqList  *L, int i);                 //删除i位置的元素

int GetData(SeqList *L, int  x);                          //查找值为x的下标

int GetLength(SeqList *L);           //求顺便长度

int InitSList(SeqList *L);       //初始化顺序表，释放整个顺表

void output(SeqList * L);                 //打印整个顺序表

void reverse_list(SeqList *L);        //反转整个顺序表

void sortrank(SeqList *L);                  //对顺序表进行排序