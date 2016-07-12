#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LEN 200
#define SIZE 100
#define MAX 20
enum
{
	QUIT,
	CREATETREE,
	FINFALLCHILD,
	FINDPARENT,
	FINDPARSON,
	FINDCOLLAGE,
	DLr
};
typedef struct tree
{
	char Key[MAX];
	char data[SIZE];
	struct tree *lchild;
	struct tree *rchild;
	struct tree *parent;
}Tree,*pTree;


pTree CreateTRee(pTree root, pTree parent);
void FindAllCHild(pTree root);                                //找下属单位
void FindParent(pTree root);
void FindPerson(pTree root);                                  //查询教师信息
void FindCollege(pTree root);                                 //查找院系
void DLR(pTree root);
void Quit();
void Menu();

