#include"tree.h"

void judge_NULL(tree *p)
{
	if (p==NULL)
	{
		perror("out of mermoy");
		exit(EXIT_FAILURE);
	}
}
tree* tier_creat(tree *root)
{
	printf("���򴴽�������0��ʾ���㣬-1��ʾ����\n");
	tree *s = NULL;
	root = NULL;
	ElemType n = 0;
	tree *quene[MAXSIZE] = { 0 };                //����һ������
	int fornt = 1;
	int rear = 0;
	scanf("%d", &n);
	while (n != -1)                              //-1��ʾ��������
	{
		s = NULL;                               
		if (n != 0)                              //����������㣬�򴴽�
		{
			s = (tree *)malloc(sizeof(tree));
			judge_NULL(s);
			s->data = n;
			s->lchild = NULL;
			s->rchild = NULL;
		}
		rear++;                                  
		quene[rear] = s;                         //�ڶ�β����ӽ��
		if (rear == 1)
			root = s;                            //����һ�������Ϊ����
		else
		{
			if (s&&quene[fornt])                 //���s��quene[fornt]��������
			{
				if (rear % 2 == 0)
					quene[fornt]->lchild = s;          //�����β��ż������sΪ����
				else
					quene[fornt]->rchild = s;          //�����β����������sΪ�Һ���
			}
			if (rear % 2 == 1)
				fornt++;                            
		}
		scanf("%d", &n);
	}
	return root;
}







tree* DLR_creat(tree *root)
{
	printf("��0��ʾָ����ΪNULL\n");
	root = NULL;
	int n = 0;
	scanf("%d", &n);
	if (n == 0)                       //n==0�ݹ����
		return NULL;
	root = (tree *)malloc(sizeof(tree));
	judge_NULL(root);
	root->data = n;
	root->lchild = DLR_creat(root->lchild);    
	root->rchild = DLR_creat(root->rchild);
	return root;
}





tree* LDR_creat(tree *root)
{
	printf("��0��ʾָ����ΪNULL\n");
	root = NULL;
	int n = 0;
	scanf("%d", &n);
	if (n == 0)
		return NULL;
	root = (tree *)malloc(sizeof(tree));
	judge_NULL(root);
	root->lchild =LDR_creat(root->lchild);
	root->data = n;
	root->rchild =LDR_creat(root->rchild);
	return root;
}



tree* LRD_creat(tree *root)
{
	printf("��0��ʾָ����ΪNULL\n");
	root = NULL;
	int n = 0;
	scanf("%d", &n);
	if (n == 0)
		return NULL;
	root = (tree *)malloc(sizeof(tree));
	judge_NULL(root);
	root->lchild = LRD_creat(root->lchild);
	root->rchild = LRD_creat(root->rchild);
	root->data = n;
	return root;
}


void DLR(tree const *root)
{
	if (root != NULL)
	{
		printf("%d  ", root->data);
		DLR(root->lchild);
		DLR(root->rchild);
	}
	return;
}

void LDR(tree const *root)
{
	if (root == NULL)
		return;
	LDR(root->lchild);
	printf("%d  ", root->data);
	LDR(root->rchild);
}

void LRD(tree const *root)
{
	if (root == NULL)
		return;
	LRD(root->lchild);
	LRD(root->rchild);
	printf("%d  ", root->data);
}


int leaf_node(tree const *root)                              //Ҷ�ӽڵ�ĸ���
{
	if (root == NULL)                                        //���ڵ�Ϊ�գ��򷵻�0
		return 0;
	if (root->lchild == NULL&&root->rchild == NULL)          //�����Ҷ�ӽڵ㣬�򷵻�1
		return 1;
	return leaf_node(root->lchild) + leaf_node(root->rchild);
}


int tree_node(tree const *root)                                      //���нڵ�ĸ���
{
	if (root == NULL)
		return 0;
	if (root->lchild == NULL&&root->rchild == NULL)                  //�����Ҷ�ӽ�㣬�򷵻�1
		return 1;
	return 1 + tree_node(root->lchild) + tree_node(root->rchild);     //�������Ҷ�ӽ�㣬���һ���ڵݹ�
}


tree *search_node(tree const *root, ElemType x)                    //����ֵΪx�Ľ��
{
	if (root == NULL)
	{
		printf("���ǿ���\n");
		return NULL;
	}
	tree *p = NULL; 
	if (root->data == x)                                           //���ж��ǲ��Ǹ��ڵ�
		return (tree *)root;
	if (root->lchild != NULL)                                      //��Ѱ������
	{
		p = search_node(root->lchild, x);                         
		if (p != NULL)                                              //����ҵ��򷵻�p
			return p;
	}
	if (root->rchild != NULL)
		return search_node(root->rchild, x);
	return NULL;                                                 //û�ҵ�����NULL
}

int tree_deep(tree *root)                         //�������
{
	int left = 0;
	int right = 0;
	int deep = 0;
	if (root)
	{

		left = tree_deep(root->lchild);                 //�ݹ�����
		right = tree_deep(root->rchild);                //�ݹ��Һ���
		deep = left > right ? left + 1 : right + 1;
	}
	return deep;
}


void output(tree const *root,void(*fun)(tree const *src))          //����ָ��fun
{
	if (root == NULL)
	{
		printf("���ǿ���\n");
		return;
	}
	else
	{
		fun(root);                                                 //funָ�������ʽ
		printf("\n");
	}
}



void init(tree *root)
{
	if (root == NULL)
		return;
	init(root->lchild);
	init(root->rchild);
	free(root);
	root = NULL;
}


//void insert(tree *root, ElemType x,ElemType data)
//{
//	if (root == NULL)
//	{
//		printf("���ǿ���\n");
//		return NULL;
//	}
//	tree *p = NULL;
//	if (root->data == x)                                           //���ж��ǲ��Ǹ��ڵ�{
//	{
//		p= (tree *)malloc(sizeof(tree));
//		judge_NULL(root);
//		p->data = data;
//		p->lchild=
//
//		return;
//	}
//	if (root->lchild != NULL)                                      //��Ѱ������
//	{
//		p = search_node(root->lchild, x);
//		if (p != NULL)                                              //����ҵ��򷵻�p
//			return p;
//	}
//	if (root->rchild != NULL)
//		return search_node(root->rchild, x);
//	return NULL;
//
//}

