#include"expression.h"

const char arr[7] = { '+', '-', '*', '/', '(', ')', '#' };     //ͨ��arr[7]������list[][]�е����ȼ�

void init_priority_list(char list[][7])                      //��ʼ�����ȼ��б�
{
	int arr2[7] = { 1, 1, 2, 2, 3, 0, -1 };                  //����Ϊջ��Ԫ�أ��д����ȡ�������
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if ((i == 4 && j == 5) || (i == 6 && j == 6))    //��'('�롮��������#���롮#�����ȼ���ͬ
				list[i][j] = '=';
			else
			{
				if (arr2[i] >= arr2[j])
					list[i][j] = '>';                        //ջ�����ȼ���
				else if (arr2[i] <= arr2[j])
					list[i][j] = '<';                        //��ȡ����������ȼ���
			}

		}
	}
}

void creatstack_num(stack_num *S)                            //����������ջ
{
	S->ebp = (int *)malloc(sizeof(int)* STACK_INIT_MEMORY);
	if (S->ebp == NULL)                                      //�ж϶�̬�ڴ��Ƿ񿪱ٳɹ�
		exit(1);
	S->size = STACK_INIT_MEMORY;             
	S->esp = S->ebp;                                          //��ջ����ջ��ָ��ָ��ջ��
}
void push_num(stack_num *S, int x)
{
	if (S->esp - S->ebp >= S->size)                           //�жϵ�ǰջ�Ƿ�����
	{                                                         //ջ��׷�ӿռ�
		S->ebp = (int *)realloc(S->ebp, sizeof(int)*(S->size + STACK_GROW_MEMORY));
		if (S->ebp == NULL)
			exit(1);
		S->esp = S->ebp + S->size;                            //��ջ��ָ�����ƫ��ָ��Ҫ��ջ��λ��
		S->size += STACK_GROW_MEMORY;                         //����ջsize
	}
	*S->esp++ = x;
}
int pop_num(stack_num *S, int *x)               
{
	if (S->esp == S->ebp)
		return 0;                                             //����ǿ�ջ���򷵻�0
	else
	{
		*x = *--S->esp;
		return 1;                                             //��������ɹ�������1������������Ԫ�ر�����x�д���
	}
}




void creatstack_operation(stack_operation *S)                  //���������ջ
{
	S->ebp = (char *)malloc(sizeof(char)*STACK_INIT_MEMORY);
	if (S->ebp == NULL)
		exit(1);                                               //�ж϶�̬�ڴ��Ƿ񿪱ٳɹ�
	S->size = STACK_INIT_MEMORY;
	S->esp = S->ebp;
}
void push_operation(stack_operation *S, char symbol)
{
	if (S->esp - S->ebp >= S->size)                            //���ջ����׷�ӿռ�
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
		return 0;                                              //���ջ�ǿ�ջ���򷵻�0
	else
		*top = *--S->esp;                                       //���򽫵��������ٱ�����top�д���
	return 1;
}


char judge_priority(stack_operation* S, char c)                  //�ж�ջ����������ȡ������������ȼ�
{
	char list[7][7];
	init_priority_list(list);                                    //��ʼ�����ȼ���
	int line = 0;                                  
	int row = 0;
	for (line = 0; line < 7; line++)
	{
		if (arr[line] == *(S->esp - 1))                          //��ջ��������arr[]�е�λ����Ϊ���±�
			break;
	}
	for (row = 0; row < 7; row++)
	{
		if (arr[row] == c)                                       //����ȡ���������arr[]�е�λ����Ϊ���±�
			break;
	}
	return list[line][row];                                      //ͨ�����ȼ����������ȼ���ϵ
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


int judge_num(char c)                             //�ж϶�ȡ���ǲ�������
{
	int i = 0;
	for (i = 0; i < 7; i++)
	{
		if (arr[i] == c)                        
			break;
	}
	if (i == 7)
		return 1;                                 //����������򷵻�1
	else
		return 0;                                 //������������򷵻�0
}