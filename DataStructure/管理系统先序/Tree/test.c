#include"manage.h"

int main()
{
	Login();	
	Tr root;    //����һ�����ڵ�        
	int n = -1;
	strcpy(root.data.name,"SUST");            //�����ڵ������Ϣ
	strcpy(root.data.intro,"�����Ƽ���ѧ");
	root.lchild = NULL;
	root.rchild = NULL;
	root.parent = NULL;
	while (1)
	{
		Menu();
		scanf("%d", &n);
		switch (n)
		{
		case 0:
			Quit(&root);
			break;
		case 1:
			root.lchild = CreateTRee((&root)->lchild, &root);
			break;
		case 2:
			FindAllCHild(&root);
			break;
		case 3:
			FindParent(&root);
			break;
		case 4:
			FindPerson(&root);
			break;
		case 5:
			FindCollege(&root);
			break;
		case 6:
			DLR(&root);
			break;
		default:
			printf("ѡ����Ч,������ѡ��\n");
			break;
		}
	}
	system("pause");
	return 0;
}