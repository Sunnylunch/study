
#ifndef __LINKLIST_H__
#define __LINKLIST_H__
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef int DataType;
typedef struct LinkNode
{
	DataType data;
	struct LinkNode *next;
}LinkNode, *pLinkNode;

typedef struct LinkList
{
	pLinkNode pHead;
}LinkList,*pLinkList;

void InitLinkList(pLinkList list);
void DestoryList(pLinkList list);
void PushBack(pLinkList list , DataType x);
void PopBack(pLinkList list);
void PushFront(pLinkList list , DataType x);
void PopFront(pLinkList list);
void PrintList(pLinkList list);
pLinkNode Find(pLinkList list,DataType x);
void Insert(pLinkList list, pLinkNode pos, DataType x);
void Remove(pLinkList list, DataType x);
void RemoveAll(pLinkList list, DataType x);
void Erase(pLinkList list,pLinkNode pos);
void BubbleSort(pLinkList list);

#endif //__LINKLIST_H__