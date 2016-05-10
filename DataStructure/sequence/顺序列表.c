#include"sequence.h"
void creat(SeqList *L)                          //创建一个顺序表
{
	printf("请输入顺序表：\n");
	for (int n = 0; n <= L->last; n++)
	{
		scanf("%d", &(L->data[n]));
	}
	printf("输入成功\n");
}

int InsertSList(SeqList  *L, int i, int x)         //将x插入到i位置上，成功返回1
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

int DeleteList(SeqList  *L, int i)                     //删除i位置上的元素，成功返回1
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

int GetData(SeqList *L, int  x)                      //查找x元素的所在的位置
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

int GetLength(SeqList *L)                           //求取表的长度
{
	return (L->last + 1);
}

int InitSList(SeqList *L)                          //初始化顺序表，将当前顺序表释放
{
	L->last = -1;
	return 1;
}

void output(SeqList * L)                   //打印顺序表
{
	if (L->last==-1)
	{
		printf("请先创建顺序表\n");
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
		printf("请先创建顺序表\n");
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
		printf("逆序成功\n");
	}
}

void sortrank(SeqList *L)                               //对顺序表进行排序
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
	printf("排序成功\n");
}