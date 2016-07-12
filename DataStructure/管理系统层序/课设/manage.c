#include"manage.h"

pTree CreateTRee(pTree root, pTree parent)
{
	pTree s = NULL;
	root = NULL;
	char arr[SIZE] = { 0 };
	pTree quene[LEN] = { 0 };             //创建一个队列
	int fornt = 1;
	int rear = 0;
	while (arr[0]!='#')                   //#表示创建结束
	{
		printf("<<层序创建二叉树，以@表示虚结点，#表示结束>>\n");
		printf("请输入部门名称：");
		scanf("%s", arr);
		s = NULL;
		if (arr[0]!='@'&&arr[0]!='#')                              //如果不是虚结点，则创建结点
		{
			s = (pTree)malloc(sizeof(Tree));
			strcpy(s->Key,arr);
			printf("请输入部门信息：");
			scanf("%s", s->data);
			s->lchild = NULL;
			s->rchild = NULL;
		}
		rear++;
		quene[rear] = s;                         //在队尾处添加结点
		if (rear == 1)
		{
			root = s;                            //将第一个结点作为树根
			root->parent = parent;
		}
		else
		{
			if (s&&quene[fornt])                 //如果s和quene[fornt]不是虚结点
			{
				if (rear % 2 == 0)
				{
					quene[fornt]->lchild = s;          //如果队尾是偶数，则s为左孩子
					s->parent = quene[fornt];
				}
				else
				{
					quene[fornt]->rchild = s;          //如果队尾是奇数，则s为右孩子
					s->parent = quene[fornt];
				}
			}
			if (rear % 2 == 1)
				fornt++;
		}
	}
	return root;
}

pTree Find(pTree root,char *name)
{
	if (root == NULL)
	{
		return NULL;
	}
	pTree p = NULL;
	if (strcmp(root->Key,name)==0)                                           //先判断是不是根节点
		return root;
	if (root->lchild != NULL)                                      //先寻找左孩子
	{
		p = Find(root->lchild,name);
		if (p != NULL)                                              //如果找到则返回p
			return p;
	}
	if (root->rchild != NULL)
		return Find(root->rchild,name);
	return NULL;
}

void FindAllCHild(pTree root)
{
	char arr[MAX] = { 0 };
	printf("请输入要查找的部门名称：");
	scanf("%s",arr);
	pTree p=Find(root,arr);
	if (NULL == p)
	{
		printf("查询无果\n");
		return;
	}
	DLR(p->lchild);
}


void FindParent(pTree root)
{
	char arr[MAX] = { 0 };
	printf("请输入要查找的部门名称：");
	scanf("%s", arr);
	pTree p = Find(root, arr);
	if (NULL == p)
	{
		printf("查询无果\n");
		return;
	}
	if (NULL == p->parent)                   //没有上级
	{
		printf("没有上级\n");
		return;
	}
	printf("上级单位：\n");
	while (p->parent->lchild!= p)           //寻找上级
	{
		p = p->parent;
	}
	printf("名称：%s\n", p->parent->Key);
	printf("基本信息：%s\n", p->parent->data);
}


void FindPerson(pTree root)
{
	char arr[MAX] = { 0 };
	printf("请输入要查找的教师姓名：");
	scanf("%s", arr);
	pTree p = Find(root, arr);
	if (NULL == p)
	{
		printf("查询无果\n");
		return;
	}
	printf("教师姓名：%s\n",p->Key);
	printf("教师信息：%s\n\n",p->data);
}


void FindCollege(pTree root)
{
	char arr[MAX] = { 0 };
	printf("请输入要查找的部门名称：");
	scanf("%s", arr);
	pTree p = Find(root, arr);
	if (NULL == p)
	{
		printf("查询无果\n");
		return;
	}

	printf("本学院信息：%s\n\n", root->data);

	if (NULL == p->parent)                   //没有上级
	{
		printf("没有上级\n");
	}
	else
	{
		printf("上级单位：\n");
	}
	while (p->parent->lchild != p)           //寻找上级
	{
		p = p->parent;
	}
	printf("名称：%s\n", p->parent->Key);
	printf("基本信息：%s\n", p->parent->data);
}


void DLR(pTree root)
{
	if (root != NULL)
	{
		printf("部门名称：%s\n", root->Key);
		printf("部门信息：%s\n\n", root->data);
		DLR(root->lchild);
		DLR(root->rchild);
	}
	return;
}


void Quit()
{
	exit(1);
}


void Menu()
{
	printf("^v^ ^v^ ^v^ ^v^ ^v^ ^v^ ^v^ ^v^ \n");
	printf("--------------------------------\n");
	printf("0.Quit             1.CreateTRee \n");
	printf("________________________________\n");
	printf("2.FindAllCHild     3.FindParent \n");
	printf("________________________________\n");
	printf("4.FindPerson       5.FindCollege\n");
	printf("________________________________\n");
	printf("6.DLR              -------------\n");
	printf("--------------------------------\n");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("请选择：");
}
