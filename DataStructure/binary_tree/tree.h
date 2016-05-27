
#ifndef  __TREE_H__                            //��������
#define __TREE_H__
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1000                          
typedef int ElemType;

typedef struct Tree                             //���н����Ϣ�Ľṹ��
{
	ElemType data;
	struct Tree *lchild;
	struct Tree *rchild;
}tree;

tree* tier_creat(tree *root);                   //���򴴽���
tree* DLR_creat(tree *root);                    //���򴴽���
tree* LDR_creat(tree *root);                    //���򴴽���
tree* LRD_creat(tree *root);                    //���򴴽���

void DLR(tree const *root);                     //�������
void LDR(tree const *root);                     //�������
void LRD(tree const *root);                     //�������

int leaf_node(tree const *root);                                   //��Ҷ�ӽ�����
int tree_node(tree const *root);                                   //���н�����
tree *search_node(tree const *root, ElemType x);                   //�������н��λ��
int tree_deep(tree *root);                                         //���������
void output(tree const *root, void(*fun)(tree const *src));        //��ӡ��
void init(tree *root);
#endif                                                             //__TREE_H__