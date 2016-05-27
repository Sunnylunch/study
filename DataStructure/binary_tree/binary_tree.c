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
	printf("层序创建树，以0表示虚结点，-1表示结束\n");
	tree *s = NULL;
	root = NULL;
	ElemType n = 0;
	tree *quene[MAXSIZE] = { 0 };                //创建一个队列
	int fornt = 1;
	int rear = 0;
	scanf("%d", &n);
	while (n != -1)                              //-1表示创建结束
	{
		s = NULL;                               
		if (n != 0)                              //如果不是虚结点，则创建
		{
			s = (tree *)malloc(sizeof(tree));
			judge_NULL(s);
			s->data = n;
			s->lchild = NULL;
			s->rchild = NULL;
		}
		rear++;                                  
		quene[rear] = s;                         //在队尾处添加结点
		if (rear == 1)
			root = s;                            //将第一个结点作为树根
		else
		{
			if (s&&quene[fornt])                 //如果s和quene[fornt]不是虚结点
			{
				if (rear % 2 == 0)
					quene[fornt]->lchild = s;          //如果队尾是偶数，则s为左孩子
				else
					quene[fornt]->rchild = s;          //如果队尾是奇数，则s为右孩子
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
	printf("以0表示指针域为NULL\n");
	root = NULL;
	int n = 0;
	scanf("%d", &n);
	if (n == 0)                       //n==0递归结束
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
	printf("以0表示指针域为NULL\n");
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
	printf("以0表示指针域为NULL\n");
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


int leaf_node(tree const *root)                              //叶子节点的个数
{
	if (root == NULL)                                        //根节点为空，则返回0
		return 0;
	if (root->lchild == NULL&&root->rchild == NULL)          //如果是叶子节点，则返回1
		return 1;
	return leaf_node(root->lchild) + leaf_node(root->rchild);
}


int tree_node(tree const *root)                                      //树中节点的个数
{
	if (root == NULL)
		return 0;
	if (root->lchild == NULL&&root->rchild == NULL)                  //如果是叶子结点，则返回1
		return 1;
	return 1 + tree_node(root->lchild) + tree_node(root->rchild);     //如果不是叶子结点，则加一，在递归
}


tree *search_node(tree const *root, ElemType x)                    //查找值为x的结点
{
	if (root == NULL)
	{
		printf("树是空树\n");
		return NULL;
	}
	tree *p = NULL; 
	if (root->data == x)                                           //先判断是不是根节点
		return (tree *)root;
	if (root->lchild != NULL)                                      //先寻找左孩子
	{
		p = search_node(root->lchild, x);                         
		if (p != NULL)                                              //如果找到则返回p
			return p;
	}
	if (root->rchild != NULL)
		return search_node(root->rchild, x);
	return NULL;                                                 //没找到返回NULL
}

int tree_deep(tree *root)                         //树的深度
{
	int left = 0;
	int right = 0;
	int deep = 0;
	if (root)
	{

		left = tree_deep(root->lchild);                 //递归左孩子
		right = tree_deep(root->rchild);                //递归右孩子
		deep = left > right ? left + 1 : right + 1;
	}
	return deep;
}


void output(tree const *root,void(*fun)(tree const *src))          //函数指针fun
{
	if (root == NULL)
	{
		printf("树是空树\n");
		return;
	}
	else
	{
		fun(root);                                                 //fun指向遍历方式
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
//		printf("树是空树\n");
//		return NULL;
//	}
//	tree *p = NULL;
//	if (root->data == x)                                           //先判断是不是根节点{
//	{
//		p= (tree *)malloc(sizeof(tree));
//		judge_NULL(root);
//		p->data = data;
//		p->lchild=
//
//		return;
//	}
//	if (root->lchild != NULL)                                      //先寻找左孩子
//	{
//		p = search_node(root->lchild, x);
//		if (p != NULL)                                              //如果找到则返回p
//			return p;
//	}
//	if (root->rchild != NULL)
//		return search_node(root->rchild, x);
//	return NULL;
//
//}

