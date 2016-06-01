#include"seqlist_d.h"

void InitSeqlist(pSeqlist pSeq)               
{
	pSeq->data = (DataType *)malloc(INIT_SIZE*sizeof(DataType));
	if (pSeq->data == NULL)
	{
		printf("out of memory\n");
		exit(1);
	}
	pSeq->size = 0;
	pSeq->capacity = INIT_SIZE;     //将容量置为当前空间所能存储的最大值
}

void DestorySeqlist(pSeqlist pSeq)
{
	free(pSeq->data);
	pSeq->data = NULL;
	pSeq->size = 0;
	pSeq->capacity = 0;
}

void CheckCapacity(pSeqlist pSeq)       //查看当前空间是否已满
{
	assert(pSeq);
	if (pSeq->size == pSeq->capacity)    //如果满了则进行扩容
	{
		DataType *tmp = NULL;                        
		//扩容，注意这时capacity也发生了变化
		tmp = (DataType *)realloc(pSeq->data, (pSeq->capacity += ADD_SIZE)*sizeof(DataType));
		if (NULL == tmp)
		{
			printf("out of memory\n");
			exit(1);
		}
		pSeq->data = tmp;
	}
}

void PushBack(pSeqlist pSeq, DataType x)
{
	assert(pSeq);
	CheckCapacity(pSeq);                  //只要插入元素，首先就要检查空间是否以满
	pSeq->data[pSeq->size++] = x;         //插入元素后size也要变化
}

void PopBack(pSeqlist pSeq)
{
	assert(pSeq);
	if (pSeq->size == 0)                   //异常情况，表已空
	{
		printf("表已空\n");
		return;
	}
	pSeq->size--;
}

void PushFront(pSeqlist pSeq, DataType x)
{
	assert(pSeq);
	CheckCapacity(pSeq);            //只要插入元素，首先就要检查空间是否以满
	int i = 0;
	for (i = pSeq->size; i > 0; i--)   //从后往前先将数据移动
	{
		pSeq->data[i] = pSeq->data[i-1];
	}
	pSeq->data[0] = x;
	pSeq->size++;
}

void PopFront(pSeqlist pSeq)
{
	assert(pSeq);
	int i = 0;
	if (pSeq->size == 0)                     //异常情况，表空
	{
		printf("表已空\n");
		return;
	}
	for (i = 0; i < pSeq->size-1; i++)        //直接从第二个元素依次向前覆盖
	{
		pSeq->data[i] = pSeq->data[i + 1];
	}
	pSeq->size--;
}

void Remove(pSeqlist pSeq, DataType x)       //删除第一个出现的x
{
	assert(pSeq);
	int i = 0;
	int j = 0;
	for (i = 0; i < pSeq->size; i++)
	{
		if (pSeq->data[i] == x)
		{
			for (j = i; j < pSeq->size-1; j++)      //删除的时候从这个元素的后面向前覆盖
			{
				pSeq->data[j] = pSeq->data[j + 1];
			}
			pSeq->size--;
			return;
		}
	}
}

void RemoveAll(pSeqlist pSeq, DataType x)
{
	assert(pSeq);
	int i = 0;
	int j = 0;
	for (i = 0; i < pSeq->size; i++)
	{
		if (pSeq->data[i] == x)
		{
			for (j = i; j < pSeq->size - 1; j++)      //删除的时候从这个元素的后面向前覆盖
			{
				pSeq->data[j] = pSeq->data[j + 1];
			}
			pSeq->size--;
		}
	}
}

void BubbleSort(pSeqlist pSeq)
{
	assert(pSeq);
	int flag = 0;
	int i = 0;
	int j = 0;
	int k = pSeq->size-1;
	for (i = 0; i < pSeq->size - 1; i--)
	{
		int m = 0;
		flag = 1;                               //将标记置1
		for (j = 0; j < k; j++)
		{
			if (pSeq->data[j]>pSeq->data[j + 1])
			{
				DataType tmp = pSeq->data[j];
				pSeq->data[j] = pSeq->data[j + 1];
				pSeq->data[j + 1] = tmp;
				flag = 0;
				m = j;                           //记录最后一次交换的位置
			}
		}
		if (flag)               //标记位1表示已经有序
		{
			return;
		}
		m = k;                  //将k设置成最后一次交换的位置
	}
}

void InsertSort(pSeqlist pSeq)                //插入排序
{
	assert(pSeq);
	int i = 0;
	int j = 0;
	for (i = 1; i < pSeq->size; i++)
	{
		DataType tmp = pSeq->data[i];
		for (j = i-1; j >=0; j--)
		{
			if (pSeq->data[j]>tmp)              //从有序区倒着查找一个位置，使的tmp大于这个位置的元素
			{
				pSeq->data[j+1] = pSeq->data[j];
			}
			else
			{
				break;
			}
		}
		pSeq->data[j+1] = tmp;                 //将tmp进行插入
	}
}

void SelectSort(pSeqlist pSeq)
{
	assert(pSeq);
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < pSeq->size; i++)
	{
		k = i;
		for (j = i + 1; j < pSeq->size; j++)
		{
			if (pSeq->data[k]>pSeq->data[j])
			{
				k = j;                                 //记录无无序区中最小元素的下标
			}
		}
		if (k != i)        //当找到的元素不是有序区的最后一个元素时，再进行交换
		{
			DataType tmp = pSeq->data[k];
			pSeq->data[k] = pSeq->data[i];
			pSeq->data[i] = tmp;
		}
	}
}

int BinarySearch(pSeqlist pSeq, DataType x)
{
	assert(pSeq);
	int left = 0;
	int right = pSeq->size - 1;
	int mid = (left&right) + ((left^right) >> 1);  //求平均值
	while (left <= right)
	{
		if (pSeq->data[mid]>x)
		{
			right = mid - 1;
		}
		else if (pSeq->data[mid] < x)
		{
			left = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

void  Erase(pSeqlist pSeq, int pos)
{
	assert(pSeq);
	int i = 0; 
	if (pos>= pSeq->size&&pos < 0)            //异常情况
	{
		printf("删除位置不合法\n");
		return;
	}
	for (i = pos; i < pSeq->size - 1; i++)      //从pos之后依次向前覆盖
	{
		pSeq->data[i] = pSeq->data[i + 1];
	}
	pSeq->size--;
}

void PrintSeqlist(pSeqlist pSeq)
{
	assert(pSeq);
	int i = 0;
	if (pSeq->size == 0)
	{
		printf("表为空\n");
		return;
	}
	for (i = 0; i < pSeq->size; i++)
	{
		printf("%d ", pSeq->data[i]);
	}
	printf("\n");
}