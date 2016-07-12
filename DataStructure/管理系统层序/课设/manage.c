#include"manage.h"

pTree CreateTRee(pTree root, pTree parent)
{
	pTree s = NULL;
	root = NULL;
	char arr[SIZE] = { 0 };
	pTree quene[LEN] = { 0 };             //����һ������
	int fornt = 1;
	int rear = 0;
	while (arr[0]!='#')                   //#��ʾ��������
	{
		printf("<<���򴴽�����������@��ʾ���㣬#��ʾ����>>\n");
		printf("�����벿�����ƣ�");
		scanf("%s", arr);
		s = NULL;
		if (arr[0]!='@'&&arr[0]!='#')                              //����������㣬�򴴽����
		{
			s = (pTree)malloc(sizeof(Tree));
			strcpy(s->Key,arr);
			printf("�����벿����Ϣ��");
			scanf("%s", s->data);
			s->lchild = NULL;
			s->rchild = NULL;
		}
		rear++;
		quene[rear] = s;                         //�ڶ�β����ӽ��
		if (rear == 1)
		{
			root = s;                            //����һ�������Ϊ����
			root->parent = parent;
		}
		else
		{
			if (s&&quene[fornt])                 //���s��quene[fornt]��������
			{
				if (rear % 2 == 0)
				{
					quene[fornt]->lchild = s;          //�����β��ż������sΪ����
					s->parent = quene[fornt];
				}
				else
				{
					quene[fornt]->rchild = s;          //�����β����������sΪ�Һ���
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
	if (strcmp(root->Key,name)==0)                                           //���ж��ǲ��Ǹ��ڵ�
		return root;
	if (root->lchild != NULL)                                      //��Ѱ������
	{
		p = Find(root->lchild,name);
		if (p != NULL)                                              //����ҵ��򷵻�p
			return p;
	}
	if (root->rchild != NULL)
		return Find(root->rchild,name);
	return NULL;
}

void FindAllCHild(pTree root)
{
	char arr[MAX] = { 0 };
	printf("������Ҫ���ҵĲ������ƣ�");
	scanf("%s",arr);
	pTree p=Find(root,arr);
	if (NULL == p)
	{
		printf("��ѯ�޹�\n");
		return;
	}
	DLR(p->lchild);
}


void FindParent(pTree root)
{
	char arr[MAX] = { 0 };
	printf("������Ҫ���ҵĲ������ƣ�");
	scanf("%s", arr);
	pTree p = Find(root, arr);
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
	while (p->parent->lchild!= p)           //Ѱ���ϼ�
	{
		p = p->parent;
	}
	printf("���ƣ�%s\n", p->parent->Key);
	printf("������Ϣ��%s\n", p->parent->data);
}


void FindPerson(pTree root)
{
	char arr[MAX] = { 0 };
	printf("������Ҫ���ҵĽ�ʦ������");
	scanf("%s", arr);
	pTree p = Find(root, arr);
	if (NULL == p)
	{
		printf("��ѯ�޹�\n");
		return;
	}
	printf("��ʦ������%s\n",p->Key);
	printf("��ʦ��Ϣ��%s\n\n",p->data);
}


void FindCollege(pTree root)
{
	char arr[MAX] = { 0 };
	printf("������Ҫ���ҵĲ������ƣ�");
	scanf("%s", arr);
	pTree p = Find(root, arr);
	if (NULL == p)
	{
		printf("��ѯ�޹�\n");
		return;
	}

	printf("��ѧԺ��Ϣ��%s\n\n", root->data);

	if (NULL == p->parent)                   //û���ϼ�
	{
		printf("û���ϼ�\n");
	}
	else
	{
		printf("�ϼ���λ��\n");
	}
	while (p->parent->lchild != p)           //Ѱ���ϼ�
	{
		p = p->parent;
	}
	printf("���ƣ�%s\n", p->parent->Key);
	printf("������Ϣ��%s\n", p->parent->data);
}


void DLR(pTree root)
{
	if (root != NULL)
	{
		printf("�������ƣ�%s\n", root->Key);
		printf("������Ϣ��%s\n\n", root->data);
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
	printf("��ѡ��");
}
