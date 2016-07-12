#include"manage.h"


int main()
{
	Tree p;
	int n = 0;
	p.parent = NULL;
	p.lchild = NULL;
	p.rchild = NULL;
	strcpy(p.Key, "sust");
	strcpy(p.data, "陕西科技大学\n");
	while (1)
	{
		Menu();
		scanf("%d", &n);
		switch (n)
		{
		case QUIT:
			Quit();
			break;
		case CREATETREE:
			p.lchild = CreateTRee(p.lchild, &p);
			break;
		case FINFALLCHILD:
			FindAllCHild(&p);
			break;
		case FINDPARENT:
			FindParent(&p);
			break;
		case FINDPARSON:
			FindPerson(&p);
			break;
		case FINDCOLLAGE:
			FindCollege(&p);
			break;
		case DLr:
			DLR(&p);
			break;
		default:
			printf("选择无效\n");
		}
	}
	system("pause");
	return 0;
}