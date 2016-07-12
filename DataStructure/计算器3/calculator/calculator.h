#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#define STACK_INIT_MEMORY  10
#define ADD_MEMORY         10
#define SIZE 100;
typedef char ElemType;

typedef struct stack
{
	ElemType *esp;
	ElemType *ebp;
	int sz;
}Stack, *pStack;

extern ElemType post[100];
typedef struct stack_num
{
	int *esp;
	int *ebp;
	int sz;
}Stack_num, *pStack_num;

void CreatExpression(char *arr);      //������׺���ʽ
void TransmitExpression();            //ת����׺���ʽ
int EvaluateExpression();             //�����׺���ʽ��ֵ
void CreatSatck(pStack S);            //����һ���ַ�ջ
int pop(pStack S, ElemType *x);
void push(pStack S, ElemType x);
void CreatSatck_num(pStack_num S);     //����һ������ջ
int pop_num(pStack_num S, int *x);
void push_num(pStack_num S, int x);
void Quit();
void transform(int n, int k);
