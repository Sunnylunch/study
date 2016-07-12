#include"manage.h"

int main()
{
	Login();	
	Tr root;    //创建一个根节点        
	int n = -1;
	strcpy(root.data.name,"SUST");            //给根节点添加信息
	strcpy(root.data.intro,"陕西科技大学");
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
			printf("选择无效,请重新选择\n");
			break;
		}
	}
	system("pause");
	return 0;
}