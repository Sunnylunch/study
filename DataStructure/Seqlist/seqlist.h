
#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#define MAX 100
typedef int DataType;

typedef struct Seqlist
{
	DataType Data[MAX];
	DataType sz;
}Seqlist ,*pSeqlist;

void PrintSeqlist(pSeqlist pSeq);                      //��ӡ˳���
void InitSeqlist(pSeqlist pSeq);                       //��ʼ��˳���    
void PushBack(pSeqlist pSeq, DataType x);              //�Ӻ������һ��Ԫ��
void Popback(pSeqlist pSeq);                           //�׳�������
void PushFornt(pSeqlist pSeq,DataType x);              //��ͷ������һ��Ԫ��
void PopFornt(pSeqlist pSeq);                          //ɾ��ͷԪ��
void Insert(pSeqlist pSeq,int pos, DataType x);        //ָ��λ�ò���
void Remove(pSeqlist pSeq, DataType x);                //�Ƴ���һ�����ֵ�x
void RemoveAll(pSeqlist pSeq, DataType x);             //�Ƴ�ȫ����x
void Sort(pSeqlist pSeq);                              //����˳���  
int BinarySearch(pSeqlist pSeq,DataType x);            //���ֲ��ң�����Ԫ�������±�

#endif         //__SEQLIST_H__