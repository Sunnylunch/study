#include"manage.h"



pT CreateTRee(pT root,pT parent)                  //递归创建创建树
{
	root = NULL;
	char arr1[MAXSIZE] = { 0 };
	char arr2[MAX_NEWS] = { 0 };
	printf("输入名称: ");
	scanf("%s", arr1);
	if (arr1[0] == '$')                          //'$'表示指针域为空
	{
		return NULL;
	}
	printf("结点信息:>");
	scanf("%s",arr2);
	root = (pT)malloc(sizeof(Tr));                //创建一个结点
	if (NULL == root)
	{
		exit(1);
	}
	root->lchild = NULL;
	root->rchild = NULL;
	root->parent = NULL;
	strcpy(root->data.name, arr1);                              //将名字复制到name中
	strcpy(root->data.intro, arr2);
	root->parent = parent;
	root->lchild = CreateTRee(root->lchild,root);             //递归创建左孩子
	root->rchild = CreateTRee(root->rchild,root);             //递归创建右孩子
	return root;
}


pT DLRCHECK(pT root,char *name)
{
	pT p = NULL;
	if (NULL == root)
	{
		return NULL;
	}
	if (strcmp(root->data.name, name) == 0)      //先判断是不是根节点
	{
		return root;
	}	                                        
	if (root->lchild != NULL)                    //寻找左子树
	{
		p = DLRCHECK(root->lchild, name);
		if (p != NULL)                            //找到则返回p
			return p;
	}
	if (root->rchild != NULL)
		return DLRCHECK(root->rchild, name);
	return NULL;
}

void FindAllCHild(pT root)                    //找下属单位
{
	char name[MAXSIZE] = { 0 };
	printf("请输入名称：>");
	pT p = NULL;
	scanf("%s", name);
	p = DLRCHECK(root, name);                  //查找节点
	if (p == NULL)
	{
		printf("查询无果\n");
		return;
	}
	printf("下属单位：\n");
	DLR(p->lchild);                            //先序输出下属节点
}




void FindParent(pT root)                       //寻找上级
{
	char name[MAXSIZE] = { 0 };
	printf("请输入单位名称：>");
	pT p = NULL;
	scanf("%s", name);
	p = DLRCHECK(root, name);                 //查找节点位置
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
	while (p->parent->rchild == p)           //寻找上级
	{
		p = p->parent;
	}
	printf("名称：%s\n", p->parent->data.name);
	printf("基本信息：%s\n", p->parent->data.intro);	
}


void FindPerson(pT root)                                  //查询教师信息
{
	pT p = NULL;
	char name[MAXSIZE] = { 0 };
	printf("输入教师名称：>");
	scanf("%s", name);
	p = DLRCHECK(root, name);
	if (NULL == p)
	{
		printf("查询无果\n");
		return;
	}
	pT par = p;
	if (NULL != p->parent)
	{
		printf("直属上级： ");
		while (par->parent->rchild == par)
		{
			par = par->parent;
		}
		printf("%s\n", par->parent->data.name);
	}
	else
	{
		printf("没有上级：");
	}
	printf("名称：%s\n", p->data.name);
	printf("简介：%s\n", p->data.intro);
}



//void RD_check(pT root)                               //寻找同一级的结点
//{
//	printf("名称：%s   ", root->data.name);
//	printf("简介：%s\n\n", root->data.intro);
//	DLR(root->rchild);
//}

void FindCollege(pT root)
{
	char name[MAXSIZE] = { 0 };
	pT p = NULL;
	printf("输入学院名称：>");
	scanf("%s", name);
	p = DLRCHECK(root, name);
	if (NULL == p)
	{
		printf("查询无果\n");
		return;
	}
	pT par= p;
	if (NULL != p->parent)
	{
		printf("直属上级： ");
		while (par->parent->rchild == par)
		{
			par = par->parent;
		}
		printf("%s\n", par->parent->data.name);
	}
	else
	{
		printf("没有上级： ");
	}
	printf("本学院信息：%s\n", p->data.intro);
	//printf("直属下级： ");
	//RD_check(p->lchild);
	//printf("\n");
}




void DLR(pT root)                                             //先序遍历
{
	if (NULL == root)                                         //root为空则返回
	{
		printf("\n");
		return;
	}
	printf("名称：%s   ", root->data.name);
	printf("基本信息：%s\n\n", root->data.intro);
	DLR(root->lchild);                                        //递归遍历左子数
	DLR(root->rchild);                                        //递归遍历右子树
}






void  Login()
{
	int i = 0;
	char name[10] = { 0 };
	char password[10] = { 0 };
	printf("**欢迎使用sust管理系统**\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("请登录\n\n\n");
	Sleep(1000);
	for (i = 3; i >0;i--)
	{
		printf("账号：");
		scanf("%s", name);
		printf("密码：");
		scanf("%s", password);
		if ((!strcmp(name, "123456")) && (!strcmp(password, "123456")))
		{
			printf("\n\n登陆成功，页面正在跳转中........\n\n\n");
			Sleep(10000);
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			return;
		}
		printf("用户名或密码不正确\n");
		printf("还有%d次机会\n", i-1);
	}
	exit(1);
}







void Menu()
{
	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	printf("$0.Quit         $$  1.CreateTRee $\n");
	printf("$2.FindAllCHild $$  3.FindParent $\n");
	printf("$4.FindPerson   $$  5.FindCollege$\n");
	printf("$6.DLR          $$  $$$$$$$$$$$$$$\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("请选择:> ");
}



void LRD(pT root)
{
	if (NULL == root)
	{
		return;
	}
	DLR(root->lchild);
	DLR(root->rchild);
	free(root);
	root = NULL;
}

void Destory(pT root)
{
	LRD(root->lchild);
	LRD(root->rchild);
}

void Quit(pT root)
{
	Destory(root);
	exit(1);
}