#include"sequence.h"
void creat(SeqList *L)                          //����һ��˳���
{
	printf("������˳���\n");
	for (int n = 0; n <= L->last; n++)
	{
		scanf("%d", &(L->data[n]));
	}
	printf("����ɹ�\n");
}

int InsertSList(SeqList  *L, int i, int x)         //��x���뵽iλ���ϣ��ɹ�����1
{
	if ((i<1) || i>(L->last + 2))
		return -1;
	if ((L->last) == (MAXSIZE - 1))
		return -1;
	for (int n = L->last; n >= i - 1; n--)
		L->data[n + 1] = L->data[n];
	L->data[i - 1] = x;
	L->last++;
	return 1;
}

int DeleteList(SeqList  *L, int i)                     //ɾ��iλ���ϵ�Ԫ�أ��ɹ�����1
{
	if ((i > L->last + 1) || (i < 1))
		return -1;
	if (L->last == -1)
		return -1;
	for (int n = i - 1; n <L->last; n++)
	{
		L->data[n] = L->data[n + 1];
	}
	L->last--;
	return 1;
}

int GetData(SeqList *L, int  x)                      //����xԪ�ص����ڵ�λ��
{
	int i = 0;
	if (L->last<0)
		return -1;
	while (i <= L->last)
	{
		if (L->data[i] == x)
			return i + 1;
		i++;
	}
	return -1;
}

int GetLength(SeqList *L)                           //��ȡ��ĳ���
{
	return (L->last + 1);
}

int InitSList(SeqList *L)                          //��ʼ��˳�������ǰ˳����ͷ�
{
	L->last = -1;
	return 1;
}

void output(SeqList * L)                   //��ӡ˳���
{
	if (L->last==-1)
	{
		printf("���ȴ���˳���\n");
	}
	else
	{
		for (int n = 0; n <= L->last; n++)
			printf("%d  ", L->data[n]);
		printf("\n");
	}
}

void reverse_list(SeqList *L)
{
	if (L->last == -1)
		printf("���ȴ���˳���\n");
	else
	{
		ElemType *left = L->data;
		ElemType *right = left + L->last;
		while (left<right)
		{
			ElemType tmp = *left;
			*left = *right;
			*right = tmp;
			left++;
			right--;
		}
		printf("����ɹ�\n");
	}
}

void sortrank(SeqList *L)                               //��˳����������
{
	ElemType tmp;
	int i = 0;
	int j = 0;
	for (i = 0; i <= L->last; i++)
	{
		for (j = 0; j <(L->last - i); j++)
		{
			if (L->data[j]>L->data[j + 1])
			{
				tmp = L->data[j];
				L->data[j] = L->data[j + 1];
				L->data[j + 1] = tmp;
			}
		}
	}
	printf("����ɹ�\n");
}