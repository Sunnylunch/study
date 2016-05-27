#include"seqlist.h"

void PrintSeqlist(pSeqlist pSeq)
{
	assert(pSeq);
	int i = 0;
	if (pSeq->sz == 0)                                 //异常情况，表为空
	{
		printf("表是空表\n");
	}
	else
	{
		for (i = 0; i < pSeq->sz; i++)
		{
			printf("%d  ",pSeq->Data[i]);
		}
		printf("\n");
	}
}


void InitSeqlist(pSeqlist pSeq)
{
	assert(pSeq);
	pSeq->sz = 0;
}


void PushBack(pSeqlist pSeq, DataType x)
{
	assert(pSeq);
	if (pSeq->sz == MAX)                                        //异常情况，表为满
	{
		printf("表已满\n");
		return;
	}
	pSeq->Data[pSeq->sz] = x;
	pSeq->sz++;
}


void Popback(pSeqlist pSeq)
{
	assert(pSeq);
	if (pSeq->sz == 0)                                           //异常情况，表为空
	{
		printf("表已空\n");                           
		return;
	}
	pSeq->sz--;
}


void PushFornt(pSeqlist pSeq, DataType x)
{
	assert(pSeq);
	int i=0;
	if (pSeq->sz == MAX)                                              //异常情况，表为满
	{
		printf("表已满\n");
		return;
	}
	for (i = pSeq->sz; i > 0; i--)
	{
		pSeq->Data[i] = pSeq->Data[i - 1];
	}
	pSeq->Data[0] = x;
	pSeq->sz++;
}


void PopFornt(pSeqlist pSeq)
{
	assert(pSeq);
	int i = 0;
	if (pSeq->sz ==0)                                                   //异常情况，表为空
	{
		printf("表已空\n");
		return;
	}
	for (i = 0; i< pSeq->sz-1; i++)
	{
		pSeq->Data[i] = pSeq->Data[i+1];
	}
	pSeq->sz--;
}


void Insert(pSeqlist pSeq, int pos, DataType x)
{
	assert(pSeq);
	int i = 0;                                         
	if (pSeq->sz == MAX)                                   //异常情况，表为满
	{
		printf("表已满\n");
		return;
	}
	if (pos > pSeq->sz&&pos<0)                           //插入位置小于0或者大于sz都是不合法，顺序表要求位置连续
	{
		printf("插入位置不合法\n");
		return;
	}
	for (i = pSeq->sz;i>pos; i--)
	{
		pSeq->Data[i] = pSeq->Data[i - 1];
	}
	pSeq->Data[pos] = x;
	pSeq->sz++;
}


void Remove(pSeqlist pSeq, DataType x)
{
	assert(pSeq);
	int i = 0;
	if (pSeq->sz == 0)                                             //异常情况，表为空
	{
		printf("表已空\n");
		return;
	}
	while (i<pSeq->sz)
	{
		if (pSeq->Data[i] == x)
		{
			for (; i< pSeq->sz - 1; i++)
			{
				pSeq->Data[i] = pSeq->Data[i + 1];
			}
			pSeq->sz--;
			break;
		}
		i++;
	}
}


void RemoveAll(pSeqlist pSeq, DataType x)
{
	assert(pSeq);
	int i = 0;
	int j = 0;
	if (pSeq->sz == 0)                                                  //异常情况，表为空
	{
		printf("表已空\n");
		return;
	}
	while (i<=pSeq->sz)
	{
		if (pSeq->Data[i] == x)
		{
			for (j=i; j< pSeq->sz - 1; j++)
			{
				pSeq->Data[j] = pSeq->Data[j + 1];
			}
			pSeq->sz--;
		}
		i++;
	}
}


void Sort(pSeqlist pSeq)
{
	assert(pSeq);
	if (pSeq->sz == 0)                                                    //异常情况，表为空
	{
		printf("表已空\n");
		return;
	}
	int i = 0;
	int j = 0;
	int flag = 0;
	for (i = 0; i < pSeq->sz - 1;i++)
	{
		flag = 0;
		for (j = 0; j < pSeq->sz - i - 1; j++)
		{
			if (pSeq->Data[j]>pSeq->Data[j + 1])
			{
				DataType tmp = pSeq->Data[j];
				pSeq->Data[j] = pSeq->Data[j+1];
				pSeq->Data[j+1] = tmp;
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
}


int BinarySearch(pSeqlist pSeq, DataType x)
{
	assert(pSeq);
	if (pSeq->sz == 0)                                                //异常情况，表为空
	{
		printf("表已空\n");
		return -1;
	}
	int left = 0;
	int right = pSeq->sz-1;
	int mid = (left&right) + ((left^right)>>1);                       //mid取平均值
	while (left<right)
	{
		if (x>pSeq->Data[mid])
		{
			left = mid + 1;
			mid = (left&right) + ((left^right) >> 1);
		}
		else if (x<pSeq->Data[mid])
		{
			right = mid -1;
			mid = (left&right) + ((left^right) >> 1);
		}
		else
		{
			printf("%d\n",mid);
			return mid;                                                        //返回这个元素所在的下标
		}
	}
	return -1;
}