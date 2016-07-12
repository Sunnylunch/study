#include"manage.h"



pT CreateTRee(pT root,pT parent)                  //�ݹ鴴��������
{
	root = NULL;
	char arr1[MAXSIZE] = { 0 };
	char arr2[MAX_NEWS] = { 0 };
	printf("��������: ");
	scanf("%s", arr1);
	if (arr1[0] == '$')                          //'$'��ʾָ����Ϊ��
	{
		return NULL;
	}
	printf("�����Ϣ:>");
	scanf("%s",arr2);
	root = (pT)malloc(sizeof(Tr));                //����һ�����
	if (NULL == root)
	{
		exit(1);
	}
	root->lchild = NULL;
	root->rchild = NULL;
	root->parent = NULL;
	strcpy(root->data.name, arr1);                              //�����ָ��Ƶ�name��
	strcpy(root->data.intro, arr2);
	root->parent = parent;
	root->lchild = CreateTRee(root->lchild,root);             //�ݹ鴴������
	root->rchild = CreateTRee(root->rchild,root);             //�ݹ鴴���Һ���
	return root;
}


pT DLRCHECK(pT root,char *name)
{
	pT p = NULL;
	if (NULL == root)
	{
		return NULL;
	}
	if (strcmp(root->data.name, name) == 0)      //���ж��ǲ��Ǹ��ڵ�
	{
		return root;
	}	                                        
	if (root->lchild != NULL)                    //Ѱ��������
	{
		p = DLRCHECK(root->lchild, name);
		if (p != NULL)                            //�ҵ��򷵻�p
			return p;
	}
	if (root->rchild != NULL)
		return DLRCHECK(root->rchild, name);
	return NULL;
}

void FindAllCHild(pT root)                    //��������λ
{
	char name[MAXSIZE] = { 0 };
	printf("���������ƣ�>");
	pT p = NULL;
	scanf("%s", name);
	p = DLRCHECK(root, name);                  //���ҽڵ�
	if (p == NULL)
	{
		printf("��ѯ�޹�\n");
		return;
	}
	printf("������λ��\n");
	DLR(p->lchild);                            //������������ڵ�
}




void FindParent(pT root)                       //Ѱ���ϼ�
{
	char name[MAXSIZE] = { 0 };
	printf("�����뵥λ���ƣ�>");
	pT p = NULL;
	scanf("%s", name);
	p = DLRCHECK(root, name);                 //���ҽڵ�λ��
	if (NULL == p)
	{
		printf("��ѯ�޹�\n");
		return;
	}
	if (NULL == p->parent)                   //û���ϼ�
	{
		printf("û���ϼ�\n");
		return;
	}
	printf("�ϼ���λ��\n");
	while (p->parent->rchild == p)           //Ѱ���ϼ�
	{
		p = p->parent;
	}
	printf("���ƣ�%s\n", p->parent->data.name);
	printf("������Ϣ��%s\n", p->parent->data.intro);	
}


void FindPerson(pT root)                                  //��ѯ��ʦ��Ϣ
{
	pT p = NULL;
	char name[MAXSIZE] = { 0 };
	printf("�����ʦ���ƣ�>");
	scanf("%s", name);
	p = DLRCHECK(root, name);
	if (NULL == p)
	{
		printf("��ѯ�޹�\n");
		return;
	}
	pT par = p;
	if (NULL != p->parent)
	{
		printf("ֱ���ϼ��� ");
		while (par->parent->rchild == par)
		{
			par = par->parent;
		}
		printf("%s\n", par->parent->data.name);
	}
	else
	{
		printf("û���ϼ���");
	}
	printf("���ƣ�%s\n", p->data.name);
	printf("��飺%s\n", p->data.intro);
}



//void RD_check(pT root)                               //Ѱ��ͬһ���Ľ��
//{
//	printf("���ƣ�%s   ", root->data.name);
//	printf("��飺%s\n\n", root->data.intro);
//	DLR(root->rchild);
//}

void FindCollege(pT root)
{
	char name[MAXSIZE] = { 0 };
	pT p = NULL;
	printf("����ѧԺ���ƣ�>");
	scanf("%s", name);
	p = DLRCHECK(root, name);
	if (NULL == p)
	{
		printf("��ѯ�޹�\n");
		return;
	}
	pT par= p;
	if (NULL != p->parent)
	{
		printf("ֱ���ϼ��� ");
		while (par->parent->rchild == par)
		{
			par = par->parent;
		}
		printf("%s\n", par->parent->data.name);
	}
	else
	{
		printf("û���ϼ��� ");
	}
	printf("��ѧԺ��Ϣ��%s\n", p->data.intro);
	//printf("ֱ���¼��� ");
	//RD_check(p->lchild);
	//printf("\n");
}




void DLR(pT root)                                             //�������
{
	if (NULL == root)                                         //rootΪ���򷵻�
	{
		printf("\n");
		return;
	}
	printf("���ƣ�%s   ", root->data.name);
	printf("������Ϣ��%s\n\n", root->data.intro);
	DLR(root->lchild);                                        //�ݹ����������
	DLR(root->rchild);                                        //�ݹ����������
}






void  Login()
{
	int i = 0;
	char name[10] = { 0 };
	char password[10] = { 0 };
	printf("**��ӭʹ��sust����ϵͳ**\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("���¼\n\n\n");
	Sleep(1000);
	for (i = 3; i >0;i--)
	{
		printf("�˺ţ�");
		scanf("%s", name);
		printf("���룺");
		scanf("%s", password);
		if ((!strcmp(name, "123456")) && (!strcmp(password, "123456")))
		{
			printf("\n\n��½�ɹ���ҳ��������ת��........\n\n\n");
			Sleep(10000);
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			return;
		}
		printf("�û��������벻��ȷ\n");
		printf("����%d�λ���\n", i-1);
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
	printf("��ѡ��:> ");
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