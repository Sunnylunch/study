#include"linklist.h"
void Menu()
{
	printf("**********************************\n");
	printf("*0.Quit           1.InitLinkList *\n");
	printf("*2.PushBack       3.PopBack      *\n");
	printf("*4.PushFront      5.PopFront     *\n");
	printf("*6.PrintList      7.Find         *\n");
	printf("*8.Insert         9.Remove       *\n");
	printf("*10.RemoveAll     11.Erase       *\n");
	printf("*12.BubbleSort    ****************\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("请选择:> ");
}

void test()
{
	LinkList list;
	DataType x = 0;
	pLinkNode pos = NULL;
	int n = -1;
	while (1)
	{
		Menu();
		scanf("%d", &n);
		switch (n)
		{
		case 0:
			DestoryList(&list);
			exit(1);
			break;
		case 1:
			InitLinkList(&list);
			break;
		case 2:
			printf("请输入：>");
			scanf("%d",&x);
			PushBack(&list,x);
			break;
		case 3:
			PopBack(&list);
			break;
		case 4:
			printf("请输入：>");
			scanf("%d", &x);
			PushFront(&list,x);
			break;
		case 5:
			PopFront(&list);
			break;
		case 6:
			PrintList(&list);
			break;
		case 7:
			printf("请输入：>");
			scanf("%d", &x);
			pos=Find(&list,x);
			printf("查找成功\n");
			break;
		case 8:
			printf("请输入元素：>");
			scanf("%d", &x);
			Insert(&list,pos,x);
			break;
		case 9:
			printf("请输入：>");
			scanf("%d", &x);
			Remove(&list,x);
			break;
		case 10:
			printf("请输入：>");
			scanf("%d", &x);
			RemoveAll(&list,x);
			break;
		case 11:
			Erase(&list,pos);
			break;
		case 12:
			BubbleSort(&list);
			break;
		default:
			printf("选择无效,请重新选择\n");
			break;
		}
	}
}

int main()
{
	test();
	system("pause");
	return 0;
}