
#ifndef __SEQLIST_D_H__                          //条件编译
#define __SEQLIST_D_H__
#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define INIT_SIZE  2
#define ADD_SIZE 3
typedef int DataType;

typedef struct Seqlist
{
	DataType *data;
	int size;                         //当前空间存储的元素个数
	int capacity;                     //当前空间所能存储的最大容量
}Seqlist,*pSeqlist;

void InitSeqlist(pSeqlist pSeq);
void DestorySeqlist(pSeqlist pSeq);
void PushBack(pSeqlist pSeq,DataType x);
void PopBack(pSeqlist pSeq);
void PushFront(pSeqlist pSeq,DataType x);
void PopFront(pSeqlist pSeq);
void Remove(pSeqlist pSeq,DataType x);
void RemoveAll(pSeqlist pSeq,DataType x);
void BubbleSort(pSeqlist pSeq);
void InsertSort(pSeqlist pSeq);
void SelectSort(pSeqlist pSeq);
int BinarySearch(pSeqlist pSeq,DataType x);
void  Erase(pSeqlist pSeq,int pos);
void PrintSeqlist(pSeqlist pSeq);

#endif             //SEQLIST_D_H__