#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_MEMORY 20                  //初始时开辟栈的内存大小
#define STACK_GROW_MEMORY 10                  //当栈满时，追加内存的大小

const char arr[7];                            //声明一个存放运算符的一维数组，作为索引
void init_priority_list(char list[][7]);      //初始化符号表

typedef struct stack_num                      //声明一个存放运算数的结构体类型
{
	int *esp;                                 //栈顶指针
	int *ebp;                                 //栈底指针
	int size;                                 //记录当前栈空间最多能存几个元素
}stack_num;
void creatstack_num(stack_num *S);            //创建存放运算数的栈
void push_num(stack_num *S, int x);           //将参数x中的数压入运算数栈中
int pop_num(stack_num *S, int *x);            //弹出栈顶元素，并通过形参x带回

typedef struct stackpop_opreation             //声明一个存放运算符的结构体类型
{
	char *esp;                                //栈顶指针
	char *ebp;                                //栈底指针
	int size;                                 //记录当前栈空间最多能存几个元素
}stack_operation;
void creatstack_operation(stack_operation *S);         //创建一个存放运算符的栈
void push_operation(stack_operation *S, char symbol);  //将符号压入运算符栈中
int pop_opreation(stack_operation *S, char *top);      //将运算符栈中的栈顶元素弹出



char judge_priority(stack_operation* S, char c);       //判断读取的运算符与栈顶符号的优先级,并返回
int operation(int a, char symbol, int b);              //对运算数进行相的运算，并将结果返回
int judge_num(char c);                                 //判断读取的是符号还是数字，如果是数字返回1