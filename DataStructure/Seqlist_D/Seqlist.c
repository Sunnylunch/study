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
	pSeq->capacity = INIT_SIZE;     //��������Ϊ��ǰ�ռ����ܴ洢�����ֵ
}

void DestorySeqlist(pSeqlist pSeq)
{
	free(pSeq->data);
	pSeq->data = NULL;
	pSeq->size = 0;
	pSeq->capacity = 0;
}

void CheckCapacity(pSeqlist pSeq)       //�鿴��ǰ�ռ��Ƿ�����
{
	assert(pSeq);
	if (pSeq->size == pSeq->capacity)    //����������������
	{
		DataType *tmp = NULL;                        
		//���ݣ�ע����ʱcapacityҲ�����˱仯
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
	CheckCapacity(pSeq);                  //ֻҪ����Ԫ�أ����Ⱦ�Ҫ���ռ��Ƿ�����
	pSeq->data[pSeq->size++] = x;         //����Ԫ�غ�sizeҲҪ�仯
}

void PopBack(pSeqlist pSeq)
{
	assert(pSeq);
	if (pSeq->size == 0)                   //�쳣��������ѿ�
	{
		printf("���ѿ�\n");
		return;
	}
	pSeq->size--;
}

void PushFront(pSeqlist pSeq, DataType x)
{
	assert(pSeq);
	CheckCapacity(pSeq);            //ֻҪ����Ԫ�أ����Ⱦ�Ҫ���ռ��Ƿ�����
	int i = 0;
	for (i = pSeq->size; i > 0; i--)   //�Ӻ���ǰ�Ƚ������ƶ�
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
	if (pSeq->size == 0)                     //�쳣��������
	{
		printf("���ѿ�\n");
		return;
	}
	for (i = 0; i < pSeq->size-1; i++)        //ֱ�Ӵӵڶ���Ԫ��������ǰ����
	{
		pSeq->data[i] = pSeq->data[i + 1];
	}
	pSeq->size--;
}

void Remove(pSeqlist pSeq, DataType x)       //ɾ����һ�����ֵ�x
{
	assert(pSeq);
	int i = 0;
	int j = 0;
	for (i = 0; i < pSeq->size; i++)
	{
		if (pSeq->data[i] == x)
		{
			for (j = i; j < pSeq->size-1; j++)      //ɾ����ʱ������Ԫ�صĺ�����ǰ����
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
			for (j = i; j < pSeq->size - 1; j++)      //ɾ����ʱ������Ԫ�صĺ�����ǰ����
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
		flag = 1;                               //�������1
		for (j = 0; j < k; j++)
		{
			if (pSeq->data[j]>pSeq->data[j + 1])
			{
				DataType tmp = pSeq->data[j];
				pSeq->data[j] = pSeq->data[j + 1];
				pSeq->data[j + 1] = tmp;
				flag = 0;
				m = j;                           //��¼���һ�ν�����λ��
			}
		}
		if (flag)               //���λ1��ʾ�Ѿ�����
		{
			return;
		}
		m = k;                  //��k���ó����һ�ν�����λ��
	}
}

void InsertSort(pSeqlist pSeq)                //��������
{
	assert(pSeq);
	int i = 0;
	int j = 0;
	for (i = 1; i < pSeq->size; i++)
	{
		DataType tmp = pSeq->data[i];
		for (j = i-1; j >=0; j--)
		{
			if (pSeq->data[j]>tmp)              //�����������Ų���һ��λ�ã�ʹ��tmp�������λ�õ�Ԫ��
			{
				pSeq->data[j+1] = pSeq->data[j];
			}
			else
			{
				break;
			}
		}
		pSeq->data[j+1] = tmp;                 //��tmp���в���
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
				k = j;                                 //��¼������������СԪ�ص��±�
			}
		}
		if (k != i)        //���ҵ���Ԫ�ز��������������һ��Ԫ��ʱ���ٽ��н���
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
	int mid = (left&right) + ((left^right) >> 1);  //��ƽ��ֵ
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
	if (pos>= pSeq->size&&pos < 0)            //�쳣���
	{
		printf("ɾ��λ�ò��Ϸ�\n");
		return;
	}
	for (i = pos; i < pSeq->size - 1; i++)      //��pos֮��������ǰ����
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
		printf("��Ϊ��\n");
		return;
	}
	for (i = 0; i < pSeq->size; i++)
	{
		printf("%d ", pSeq->data[i]);
	}
	printf("\n");
}