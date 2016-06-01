#include"seqlist_d.h"

void menu()
{
	printf("*********************************\n");
	printf("0.exit            1.PrintSeqlist \n");
	printf("2.InitSeqlist     3.PushBack     \n");
	printf("4.Popback         5.PushFornt    \n");
	printf("6.PopFornt        7.Erase        \n");
	printf("8.Remove          9.RemoveAll    \n");
	printf("10.BubbleSort     11.BinarySearch\n");
	printf("12.DestorySeqlist 13.InsertSort  \n");
	printf("14.SelectSort           \n");
	printf("�����룺>");
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
			printf("������Ԫ��\n");
			scanf("%d", &x);
			PushBack(pSeq, x);
			break;
		case 4:
			PopBack(pSeq);
			break;
		case 5:
			printf("������Ԫ��\n");
			scanf("%d", &x);
			PushFront(pSeq, x);
			break;
		case 6:
			PopFront(pSeq);
			break;
		case 7:
			printf("������ɾ��λ��\n");
			scanf("%d", &pos);
			Erase(pSeq, pos);
			break;
		case 8:
			printf("������Ԫ��\n");
			scanf("%d", &x);
			Remove(pSeq, x);
			break;
		case 9:
			printf("������Ԫ��\n");
			scanf("%d", &x);
			RemoveAll(pSeq, x);
			break;
		case 10:
			BubbleSort(pSeq);
			break;
		case 11:
			printf("������Ԫ��\n");
			scanf("%d", &x);
			int ret=BinarySearch(pSeq, x);
			if (ret == -1)
				printf("û�����Ԫ��\n");
			printf("�±�Ϊ��%d\n", ret);
			break;
		case 12:
			DestorySeqlist(pSeq);
			break;
		case 13:
			InsertSort(pSeq);
			break;
		case 14:
			SelectSort(pSeq);
			break;
		default:
			printf("������Ч\n");
			break;
		}
	}
}



int main()
{
	Seqlist pSeq;
	test(&pSeq);
	system("pause");
	return 0;
}