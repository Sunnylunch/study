
#ifndef __MANAGE_H__
#define __MANAGE_H__
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<Windows.h>

#define MAXSIZE 20
#define MAX_NEWS 100
typedef struct news
{
	char name[MAXSIZE];
	char intro[MAX_NEWS];
}news;
typedef struct tree
{
	news data;
	struct tree *lchild;
	struct tree *rchild;
	struct tree *parent;

}Tr, *pT;

pT CreateTRee(pT root, pT parent);
void FindAllCHild(pT root);                                //��������λ
void FindParent(pT root);
void FindPerson(pTroot);                                  //��ѯ��ʦ��Ϣ
void FindCollege(pT root);                                 //����Ժϵ
void DLR(pT root);
void Quit(pT root);
void Menu();
void  Login();

#endif // __MANAGE_H__