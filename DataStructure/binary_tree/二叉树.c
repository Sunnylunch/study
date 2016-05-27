#include"tree.h"

tree* creat(tree *root, tree* (*p)(tree *root))       //ʹ�ú���ָ��p
{
	root = p(root);
	return root;
}

void menu()
{
	printf("********************************** \n");
	printf("*0.exit              1.creat       \n");
	printf("*2.tree_deep         3.search_node \n");
	printf("*4.leaf_node         5.tree_node   \n");
	printf("*6.output            7.init        \n");
	printf("�����룺>");
}

void test()
{
	tree *root = NULL;
	void(*trav[3])(const tree *root);                   //����ָ�����飬������ű�����ʽ
	trav[0] = DLR;
	trav[1] = LDR;
	trav[2] = LRD;
	tree* (*build[4])(tree *root);                       //����ָ�����飬������Ŵ�����ʽ
	build[0] = tier_creat;
	build[1] = DLR_creat;
	build[2] = LDR_creat;
	build[3] = LRD_creat;
	int ret = 0;
	int i = 0;
	int n = 0;
	ElemType x = 0;
	
	while (1)
	{
		menu();
		scanf("%d", &n);
		switch (n)
		{
		case 0:
			exit(EXIT_FAILURE);
			break;
		case 1:
			printf("************************\n");
			printf("1.Tier_creat 2.DLR_creat\n");
			printf("3.LDR_creat  4.LRD_creat\n\n");
			while (1)
			{
				printf("�����룺>");
				scanf("%d", &i);
				if (i >= 1 && i <= 4)
					break;
				else
					printf("������Ч\n");
			}
			root = creat(root, build[i-1]);
			break;
		case 2:
			ret = tree_deep(root);
			printf("������ȣ�%d\n", ret);
			break;
		case 3:
			printf("������Ҫ���ҵĽ�㣺>");
			scanf("%d", &x);
			tree *p = search_node(root, x);
			printf("���λ�ã�%#p\n", p);
			break;
		case 4:
			ret = leaf_node(root);
			printf("Ҷ�ӽ��ĸ�����%d\n", ret);
			break;
		case 5:
			ret = tree_node(root);
			printf("���н��ĸ�����%d\n", ret);
			break;
		case 6:
			printf("************************\n");
			printf("1.DLR_creat  2.LRD_creat\n");
			printf("3.LDR_creat             \n\n");
			while (1)
			{
				printf("�����룺>");
				scanf("%d", &i);
				if (i >= 1 && i <= 3)
					break;
				else
					printf("������Ч\n");
			}
			output(root, trav[i - 1]);
			break;
		case 7:
			init(root);
			root = NULL;
			printf("��ʼ���ɹ�\n");
			break;
		case 8:
			break;
		default:
			printf("ѡ����Ч\n");
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