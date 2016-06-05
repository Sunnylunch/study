#include"calculator.h"

char dst[] = { '+', '-', '*', '/', '(', ')' };
char list[6][6] = { 0 };
ElemType post[MAX] = {0};

void valuation()
{
	int arr1[6] = {1,1,2,2,3,0};                         
	int i = 0;
	int j = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i == 4)                                  //���ջ�������ǡ����������������ȼ���С
			{
				if (j==5)                                 //'(',')'�����ȼ���ͬ
				list[i][j] = '=';
				else
					list[i][j] = '<';
			}
			else
			{
				if (arr1[i] >= arr1[j])
					list[i][j] = '>';                        //ջ�����ȼ���
				else if (arr1[i] <= arr1[j])
					list[i][j] = '<';                        //��ȡ����������ȼ���
			}

		}
	}
}

int judge_type(char c)                             //�ж϶�ȡ�������ֻ����ַ�
{
	int i = 0;
	for (i = 0; i < 6; i++)
	{
		if (dst[i] == c)
			return 0;                        //������������򷵻�0
	}
	if (c == ' ')
		return -1;                           //����ǿո��򷵻�-1
	return 1;                                 //����������򷵻�1
		                                 
}

char judge_priority(pStack S,char c)                  //�ж�ջ����������ȡ������������ȼ�
{                               
	int line = 0;
	int row = 0;
	for (line = 0; line < 6; line++)
	{
		if (dst[line] == *(S->esp - 1))         //��ջ��������dst[]�е�λ����Ϊ���±�
			break;
	}
	for (row = 0; row < 6; row++)
	{
		if (dst[row] == c)                     //����ȡ���������dst[]�е�λ����Ϊ���±�
			break;
	}
	return list[line][row];                      //ͨ�����ȼ����������ȼ���ϵ
}





int operation(int a,ElemType symbol, int b)
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
			if (b == 0)
			{
				perror("��������Ϊ�㡣/n");
				exit(1);
			}
		ret = a / b;
		break;
	}
	return ret;
}



void CreateExpression(ElemType *arr)
{
	scanf("%s", arr);
}


void TransmitExpression(ElemType *arr)
{
	valuation();
	assert(arr);
	Stack S;
	CreateStack(&S);                                 //����һ��ջ
	ElemType x= 0;
	int i = 0;
	int j = 0;
	while (arr[i] != '\0')
	{ 
		if (judge_type(arr[i]) == 1)                          //�ж��ǲ�������
		{
			post[j++] = arr[i];                               //������ֱ�Ӵ���post[]
			if (judge_type(arr[i+1]) != 1)
				post[j++]=' ';                                //�Կո����
			i++;
		}
		else
		{
			if (S.ebp == S.esp)                            //���ջΪ�գ�ѹջ
			{
				push(&S, arr[i]);
				i++;
			}
			else
			{
				switch (judge_priority(&S, arr[i]))
				{
				case '<':                              //���ջ�������ȼ��͡���ֱ����ջ
					push(&S, arr[i]);
					i++;
					break;
				case '>':                             //�����ȡ�����ȼ��ߣ���ջ������ջ
					pop(&S, &x);
					post[j++] = x;
					post[j++] = ' ';
					break;
				case '=':
					pop(&S, &x);
					i++;
					break;
				}
			}
		}
	}
	while (pop(&S, &x))
	{
		if (x != '('&&x != ')')
		{
			post[j++] = x;
			post[j++] = ' ';
		}
	}
	printf("%s\n", post);
	free(S.ebp);
}


int EvaluateExpression()
{
	int i = 0;
	Stack_num S;
	int ret = 0;
	int a = 0;
	int b = 0;
	CreateStack_num(&S);
	while (post[i] != '\0')
	{
		switch (judge_type(post[i]))               
		{
		case 0:                                     //��ȡ���Ƿ���
			pop_num(&S, &b);                        //ȡ������ջ��ջ��Ԫ��
			pop_num(&S,&a);                         //ȡ������ջ��ջ��Ԫ��
			ret=operation(a,post[i],b);           //������������������
			push_num(&S, ret);                      //����������վ
			i++;
			ret = 0;
			break;
		case 1:       
			while(judge_type(post[i])==1)
			{
				ret = ret * 10 + post[i] - '0';        //���ַ�����ת���ɶ�Ӧ������
				i++;
			}
			push_num(&S, ret);                        //��������ֽ���ѹջ
			ret = 0;
			break;
		case -1:                                    //��ȡ���ǿո�
			i++;
			break;
		}
	}
	ret = *(--(S.esp));                            //����ջ������
	free(S.ebp);
	return ret;
}



void CreateStack(pStack S)
{
	S->ebp = (ElemType *)malloc(sizeof(ElemType)* STACK_INIT_MEMORY);
	if (S->ebp == NULL)                      //�ж϶�̬�ڴ��Ƿ񿪱ٳɹ�
		exit(1);
	S->size = STACK_INIT_MEMORY;
	S->esp = S->ebp;
}


void push(pStack S, ElemType x)
{
	if (S->esp - S->ebp >= S->size)         //�жϵ�ǰջ�Ƿ�����
	{                                       //ջ��׷�ӿռ�
		S->ebp = (ElemType *)realloc(S->ebp, sizeof(ElemType)*(S->size + STACK_GROW_MEMORY));
		if (S->ebp == NULL)                 //�ж��ڴ��Ƿ񿪱ٳɹ�
			exit(1);
		S->esp = S->ebp + S->size;              //��ջ��ָ�����ƫ��ָ��Ҫ��ջ��λ��
		S->size += STACK_GROW_MEMORY;
	}
	*(S->esp)++ = x;
}


int pop(pStack S,ElemType *x)
{
	if (S->esp == S->ebp)
	{
		return 0;     //ջ�ѿ�
	}
	else
	{
		S->esp--;
		*x = *(S->esp);
		return 1;     //��ջ�ɹ�
	}
}




void CreateStack_num(pStack_num S)
{
	S->ebp = (int *)malloc(sizeof(int)* STACK_INIT_MEMORY);
	if (S->ebp == NULL)                      //�ж϶�̬�ڴ��Ƿ񿪱ٳɹ�
		exit(1);
	S->size = STACK_INIT_MEMORY;
	S->esp = S->ebp;
}


void push_num(pStack_num S, int x)
{
	if (S->esp - S->ebp >= S->size)         //�жϵ�ǰջ�Ƿ�����
	{                                       //ջ��׷�ӿռ�
		S->ebp = (int *)realloc(S->ebp, sizeof(int)*(S->size + STACK_GROW_MEMORY));
		if (S->ebp == NULL)                 //�ж��ڴ��Ƿ񿪱ٳɹ�
			exit(1);
		S->esp = S->ebp + S->size;              //��ջ��ָ�����ƫ��ָ��Ҫ��ջ��λ��
		S->size += STACK_GROW_MEMORY;
	}
	*(S->esp)++ = x;
}


int pop_num(pStack_num S,int *x)
{
	if (S->esp == S->ebp)
	{
		return 0;     //ջ�ѿ�
	}
	else
	{
		*x = *(--S->esp);
		return 1;     //��ջ�ɹ�
	}
}