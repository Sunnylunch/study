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

void creat(SeqList *L);                               //����˳���

int InsertSList(SeqList  *L, int i, int x);          //��iλ�ò���x

int DeleteList(SeqList  *L, int i);                 //ɾ��iλ�õ�Ԫ��

int GetData(SeqList *L, int  x);                          //����ֵΪx���±�

int GetLength(SeqList *L);           //��˳�㳤��

int InitSList(SeqList *L);       //��ʼ��˳����ͷ�����˳��

void output(SeqList * L);                 //��ӡ����˳���

void reverse_list(SeqList *L);        //��ת����˳���

void sortrank(SeqList *L);                  //��˳����������