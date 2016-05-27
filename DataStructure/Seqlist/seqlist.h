
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

void PrintSeqlist(pSeqlist pSeq);                      //打印顺序表
void InitSeqlist(pSeqlist pSeq);                       //初始化顺序表    
void PushBack(pSeqlist pSeq, DataType x);              //从后面插入一个元素
void Popback(pSeqlist pSeq);                           //抛出最后面的
void PushFornt(pSeqlist pSeq,DataType x);              //在头部插入一个元素
void PopFornt(pSeqlist pSeq);                          //删除头元素
void Insert(pSeqlist pSeq,int pos, DataType x);        //指定位置插入
void Remove(pSeqlist pSeq, DataType x);                //移除第一个出现的x
void RemoveAll(pSeqlist pSeq, DataType x);             //移除全部的x
void Sort(pSeqlist pSeq);                              //排序顺序表  
int BinarySearch(pSeqlist pSeq,DataType x);            //二分查找，返回元素所在下标

#endif         //__SEQLIST_H__