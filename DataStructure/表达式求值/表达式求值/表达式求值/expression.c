#include"expression.h"

const char arr[7] = { '+', '-', '*', '/', '(', ')', '#' };     //通过arr[7]来查找list[][]中的优先级

void init_priority_list(char list[][7])                      //初始化优先级列表
{
	int arr2[7] = { 1, 1, 2, 2, 3, 0, -1 };                  //列作为栈顶元素，行代表读取的运算符
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if ((i == 4 && j == 5) || (i == 6 && j == 6))    //令'('与‘）’，‘#’与‘#’优先级相同
				list[i][j] = '=';
			else
			{
				if (arr2[i] >= arr2[j])
					list[i][j] = '>';                        //栈顶优先级高
				else if (arr2[i] <= arr2[j])
					list[i][j] = '<';                        //读取的运算符优先级高
			}

		}
	}
}

void creatstack_num(stack_num *S)                            //创建运算数栈
{
	S->ebp = (int *)malloc(sizeof(int)* STACK_INIT_MEMORY);
	if (S->ebp == NULL)                                      //判断动态内存是否开辟成功
		exit(1);
	S->size = STACK_INIT_MEMORY;             
	S->esp = S->ebp;                                          //空栈，让栈顶指针指向栈底
}
void push_num(stack_num *S, int x)
{
	if (S->esp - S->ebp >= S->size)                           //判断当前栈是否已满
	{                                                         //栈满追加空间
		S->ebp = (int *)realloc(S->ebp, sizeof(int)*(S->size + STACK_GROW_MEMORY));
		if (S->ebp == NULL)
			exit(1);
		S->esp = S->ebp + S->size;                            //让栈顶指针向后偏移指向要入栈的位置
		S->size += STACK_GROW_MEMORY;                         //更新栈size
	}
	*S->esp++ = x;
}
int pop_num(stack_num *S, int *x)               
{
	if (S->esp == S->ebp)
		return 0;                                             //如果是空栈，则返回0
	else
	{
		*x = *--S->esp;
		return 1;                                             //如果弹出成功，返回1，并将弹出的元素保存在x中带回
	}
}




void creatstack_operation(stack_operation *S)                  //创建运算符栈
{
	S->ebp = (char *)malloc(sizeof(char)*STACK_INIT_MEMORY);
	if (S->ebp == NULL)
		exit(1);                                               //判断动态内存是否开辟成功
	S->size = STACK_INIT_MEMORY;
	S->esp = S->ebp;
}
void push_operation(stack_operation *S, char symbol)
{
	if (S->esp - S->ebp >= S->size)                            //如果栈满则追加空间
	{
		S->ebp = (char *)realloc(S->ebp, sizeof(char)*(S->size += STACK_GROW_MEMORY));
		if (S->ebp == NULL)
			exit(1);
		S->ebp = S->ebp + S->size - STACK_GROW_MEMORY;
	}
	*S->esp++ = symbol;
}
int pop_opreation(stack_operation *S, char *top)
{
	if (S->esp == S->ebp)
		return 0;                                              //如果栈是空栈，则返回0
	else
		*top = *--S->esp;                                       //否则将弹出的匀速保存在top中带回
	return 1;
}


char judge_priority(stack_operation* S, char c)                  //判断栈顶运算符与读取的运算符的优先级
{
	char list[7][7];
	init_priority_list(list);                                    //初始化优先级表
	int line = 0;                                  
	int row = 0;
	for (line = 0; line < 7; line++)
	{
		if (arr[line] == *(S->esp - 1))                          //将栈顶符号在arr[]中的位置作为行下标
			break;
	}
	for (row = 0; row < 7; row++)
	{
		if (arr[row] == c)                                       //将读取的运算符在arr[]中的位置作为列下标
			break;
	}
	return list[line][row];                                      //通过优先级表，返回优先级关系
}


int operation(int a, char symbol, int b)        
{
	int ret = 0;
	switch (symbol)
	{
	case '+':
		ret = a + b;
		break;
	case '-':
		ret = a - b;
		break;
	case '*':
		ret = a*b;
		break;
	case '/':
		ret = a / b;
		break;
	default:
		break;
	}
	return ret;
}


int judge_num(char c)                             //判断读取的是不是数字
{
	int i = 0;
	for (i = 0; i < 7; i++)
	{
		if (arr[i] == c)                        
			break;
	}
	if (i == 7)
		return 1;                                 //如果是数字则返回1
	else
		return 0;                                 //如果不是数字则返回0
}