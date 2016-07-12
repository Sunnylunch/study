#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#define  _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

                                     //存放后缀表达式的数
#define INIT_SIZE  20
#define ADD_SIZE   20
#define SIZE 100;

enum status
{
	EXIT,
	CREATE,
	TRANSMIT,
	VALUATE,
	BINARY,
	OCTONARY,
	B_DEC,
	OCT_DEC
};

typedef char DataType;

typedef struct stack                    //创建一个字符栈
{
	DataType *top;
	DataType *low;
	int i;
}Stack,*pStack;

typedef struct stack_figure                 //创建一个数字栈
{
	int *top;
	int *low;
	int i;
}StackFigure, *pStackFigure;

void CreatExpression(char *arr);                 //输入中缀表达式
void TransmitExpression();                       //输出后缀表达式
int EvaluateExpression();                        //求表达式的值
void CreatSatck(pStack p);                       //创建保存字符的栈
int pop(pStack p, DataType *x);                  //抛出字符
void push(pStack p, DataType x);                 //压入字符
void CreatSatckFigure(pStackFigure p);           //创建保存数字的栈
int pop_figure(pStackFigure p, int *x);          //抛出栈顶数字
void push_figure(pStackFigure p, int x);         //压入数字
void Quit();
void binary_system(int num);
void octonary_number_system(int num);
int binary_decimal();
int Octal_decimal();
#endif