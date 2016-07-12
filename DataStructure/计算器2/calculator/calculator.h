#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#define  _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

                                     //��ź�׺���ʽ����
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

typedef struct stack                    //����һ���ַ�ջ
{
	DataType *top;
	DataType *low;
	int i;
}Stack,*pStack;

typedef struct stack_figure                 //����һ������ջ
{
	int *top;
	int *low;
	int i;
}StackFigure, *pStackFigure;

void CreatExpression(char *arr);                 //������׺���ʽ
void TransmitExpression();                       //�����׺���ʽ
int EvaluateExpression();                        //����ʽ��ֵ
void CreatSatck(pStack p);                       //���������ַ���ջ
int pop(pStack p, DataType *x);                  //�׳��ַ�
void push(pStack p, DataType x);                 //ѹ���ַ�
void CreatSatckFigure(pStackFigure p);           //�����������ֵ�ջ
int pop_figure(pStackFigure p, int *x);          //�׳�ջ������
void push_figure(pStackFigure p, int x);         //ѹ������
void Quit();
void binary_system(int num);
void octonary_number_system(int num);
int binary_decimal();
int Octal_decimal();
#endif