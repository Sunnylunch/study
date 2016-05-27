
#ifndef  __TREE_H__                            //条件编译
#define __TREE_H__
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1000                          
typedef int ElemType;

typedef struct Tree                             //树中结点信息的结构体
{
	ElemType data;
	struct Tree *lchild;
	struct Tree *rchild;
}tree;

tree* tier_creat(tree *root);                   //层序创建树
tree* DLR_creat(tree *root);                    //先序创建树
tree* LDR_creat(tree *root);                    //中序创建树
tree* LRD_creat(tree *root);                    //后序创建树

void DLR(tree const *root);                     //先序遍历
void LDR(tree const *root);                     //中序遍历
void LRD(tree const *root);                     //后序遍历

int leaf_node(tree const *root);                                   //求叶子结点个数
int tree_node(tree const *root);                                   //树中结点个数
tree *search_node(tree const *root, ElemType x);                   //查找数中结点位置
int tree_deep(tree *root);                                         //求树的深度
void output(tree const *root, void(*fun)(tree const *src));        //打印树
void init(tree *root);
#endif                                                             //__TREE_H__