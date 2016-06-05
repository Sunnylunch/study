
#ifndef _CALCULATOR_H__
#define _CALCULATOR_H__
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define MAX 100
typedef char ElemType;
#define STACK_INIT_MEMORY 100
#define STACK_GROW_MEMORY 10

typedef struct stack
{
	ElemType *esp;
	ElemType *ebp;
	int size;                           //记录当前栈内空间最多能存几个元素
}Stack,*pStack;

typedef struct stack_num
{
	int *esp;
	int *ebp;
	int size;                           //记录当前栈内空间最多能存几个元素
}Stack_num, *pStack_num;

void CreateExpression(ElemType *arr);
void TransmitExpression(ElemType *arr);
int EvaluateExpression();
void CreateStack(pStack S);
void push(pStack S, ElemType x);
int pop(pStack S, ElemType *x);
void valuation();
int judge_type(char c);
char judge_priority(pStack S, char c);
int operation(int a, ElemType symbol, int b);

void CreateStack_num(pStack_num S);
void push_num(pStack_num S,int x);
int pop_num(pStack_num S, int *x);


#endif 