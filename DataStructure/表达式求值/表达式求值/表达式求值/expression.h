#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_MEMORY 20                  //��ʼʱ����ջ���ڴ��С
#define STACK_GROW_MEMORY 10                  //��ջ��ʱ��׷���ڴ�Ĵ�С

const char arr[7];                            //����һ������������һά���飬��Ϊ����
void init_priority_list(char list[][7]);      //��ʼ�����ű�

typedef struct stack_num                      //����һ������������Ľṹ������
{
	int *esp;                                 //ջ��ָ��
	int *ebp;                                 //ջ��ָ��
	int size;                                 //��¼��ǰջ�ռ�����ܴ漸��Ԫ��
}stack_num;
void creatstack_num(stack_num *S);            //���������������ջ
void push_num(stack_num *S, int x);           //������x�е���ѹ��������ջ��
int pop_num(stack_num *S, int *x);            //����ջ��Ԫ�أ���ͨ���β�x����

typedef struct stackpop_opreation             //����һ�����������Ľṹ������
{
	char *esp;                                //ջ��ָ��
	char *ebp;                                //ջ��ָ��
	int size;                                 //��¼��ǰջ�ռ�����ܴ漸��Ԫ��
}stack_operation;
void creatstack_operation(stack_operation *S);         //����һ������������ջ
void push_operation(stack_operation *S, char symbol);  //������ѹ�������ջ��
int pop_opreation(stack_operation *S, char *top);      //�������ջ�е�ջ��Ԫ�ص���



char judge_priority(stack_operation* S, char c);       //�ж϶�ȡ���������ջ�����ŵ����ȼ�,������
int operation(int a, char symbol, int b);              //������������������㣬�����������
int judge_num(char c);                                 //�ж϶�ȡ���Ƿ��Ż������֣���������ַ���1