#include"seqlist.h"


void menu()
{
	printf("*********************************\n");
	printf("0.exit            1.PrintSeqlist \n");
	printf("2.InitSeqlist     3.PushBack     \n");
	printf("4.Popback         5.PushFornt    \n");
	printf("6.PopFornt        7.Insert       \n");
	printf("8.Remove          9.RemoveAll    \n");
	printf("10.Sort           11.BinarySearch\n");
	printf("请输入：>");
}

void test(pSeqlist pSeq)
{
	DataType x = 0;
	int n = 0;
	int pos = 0;
	while (1)
	{
		menu();
		scanf("%d", &n);
		switch (n)
		{
		case 0:
			exit(1);
			break;
		case 1:
			PrintSeqlist(pSeq);
			break;
		case 2:
			InitSeqlist(pSeq);
			break;
		case 3:
			printf("请输入元素\n");
			scanf("%d", &x);
			PushBack(pSeq, x);
			break;
		case 4:
			Popback(pSeq);
			break;
		case 5:
			printf("请输入元素\n");
			scanf("%d", &x);
			PushFornt(pSeq, x);
			break;
		case 6:
			PopFornt(pSeq);
			break;
		case 7:
			printf("请输入元素\n");
			scanf("%d", &x);
			printf("请输入插入位置\n");
			scanf("%d", &pos);
			Insert(pSeq, pos, x);
			break;
		case 8:
			printf("请输入元素\n");
			scanf("%d", &x);
			Remove(pSeq, x);
			break;
		case 9:
			printf("请输入元素\n");
			scanf("%d", &x);
			RemoveAll(pSeq, x);
			break;
		case 10:
			Sort(pSeq);
			break;
		case 11:
			printf("请输入元素\n");
			scanf("%d", &x);
			BinarySearch(pSeq, x);
			break;
		default:
			printf("输入无效\n");
			break;
		}
	}
}



int main()
{
	Seqlist pSeq;
	memset(pSeq.Data, 0, sizeof(DataType)*MAX);
	pSeq.sz = 0;
	test(&pSeq);
	system("pause");
	return 0;
}