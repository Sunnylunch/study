
#include"calculator.h"

ElemType arr2[10] = { '&','|','+', '-', '%', '*', '/', '^', '(', ')' };              //����һ����������
ElemType list[10][10] = { 0 };                                         //����һ�����ȼ���ϵ��
ElemType post[100] = { 0 };

void init_list()                                                   //��ʼ�����ȼ���ϵ
{
	int p[10] = { 0,-1,1, 1, 2, 3, 3, 4, 5, -1 };
	int i = 0;
	int j = 0;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (i == 8|| i == 9)
			{
				if (i == 8)
				{
					if (j == 9)
						list[i][j] = '=';
					else
						list[i][j] = '<';
				}
				else
				{
					list[i][j] = '>';
				}

			}
			else
			{
				if (p[i] >= p[j])               //���ջ�����ŵ����ȼ����ڶ�����ţ�list��Ϊ>
					list[i][j] = '>';
				else if (p[i] <= p[j])          //���ջ�����ŵ����ȼ�С�ڶ�����ţ�list��Ϊ<
					list[i][j] = '<';
			}
		}
	}
}


ElemType priority(pStack S, ElemType x)                         //�������ȼ���ϵ
{
	char c = 0;
	int line = 0;
	int row = 0;
	pop(S, &c);
	for (line = 0; line < 10; line++)                             //��ջ����������λ��Ϊlist�����±�
	{
		if (arr2[line] == c)
			break;
	}
	for (row = 0; row < 10; row++)                                //�Զ�ȡ��������λ��Ϊlist�����±�
	{
		if (arr2[row] == x)
			break;
	}
	push(S, c);
	return list[line][row];                                     //�������ȼ���ϵ
}





int judge_type(ElemType c)               //�ж��Ƿ��Ż��� ����
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		if (arr2[i] == c)
			return 0;             //����Ƿ��ţ�����0
	}
	if (c == ' ')
		return -1;
	return 1;                       //��������ַ���1
}


int opreation(int a, char symbol, int b)             //��������
{
	int ret = 0;
	switch (symbol)
	{
	case'+':
		ret = a + b;
		break;
	case'-':
		ret = a - b;
		break;
	case'*':
		ret = a*b;
		break;
	case'/':
		if (!b)
		{
			printf("Divisor of 0\n");
			system("pause");
			exit(1);
		}
		else
			ret = a / b;
		break;
	case'%':
		ret = a%b;
		break;
	case '&':
		ret = a&b;
		break;
	case '|':
		ret = a|b;
		break;
	case'^':
		ret = (int)pow((double)a, (double)b);
		break;
	}
	return ret;
}


void CreatExpression(ElemType *arr)
{
	scanf("%s", arr);
}



void TransmitExpression(ElemType *arr)
{
	Stack S;
	int i = 0;
	int j = 0;
	ElemType x = 0;
	init_list();
	CreatSatck(&S);
	while (arr[i] != '\0')
	{
		if (judge_type(arr[i]))                 //�����ȡ��������
		{
			post[j++] = arr[i];                //����ֱ�ӱ�����post����
			if (judge_type(arr[i + 1]) != 1)
				post[j++] = ' ';                //�Կո����
			i++;
		}
		else
		{
			if (S.ebp == S.esp)                //���ջ�ǿ�ջ����ֱ��ѹջ
			{
				push(&S, arr[i]);
				i++;
			}
			else
			{
				switch (priority(&S, arr[i]))
				{
				case '>':                        //���ջ�����ŵ����ȼ��ߣ�������ջ
					if (pop(&S, &x))
					{
						post[j++] = x;
						post[j++] = ' ';         //�Կո����
					}
					break;
				case '<':                        //�����ȡ�����ȼ��ߣ���ֱ��ѹջ
					push(&S, arr[i]);
					i++;
					break;
				case '=':
					pop(&S, &x);
					i++;
					break;
				}
			}
		}
	}
	while (pop(&S, &x))                                     //��ʣ�µķ���ȫ����ջ
	{
		post[j++] = ' ';
		post[j++] = x;
	}
	printf("%s\n", post);
	free(S.ebp);
}



int EvaluateExpression()
{
	Stack_num S;
	int ret = 0;
	int i = 0;
	int a = 0;
	int b = 0;
	CreatSatck_num(&S);
	while (post[i] != '\0')                    //��ȡ��׺���ʽ�����еķ��� 
	{
		switch (judge_type(post[i]))
		{
		case 0:                              //�����ȡ���Ƿ���
			pop_num(&S, &b);                 //������ջ��������������ջ
			pop_num(&S, &a);
			ret = opreation(a, post[i], b);    //���������������㣬�����������
			push_num(&S, ret);               //�������ջ
			ret = 0;
			i++;
			break;
		case 1:
			while (post[i] != ' ')            //������������ȫ����ȡ����ת��Ϊ��Ӧ������
			{
				ret = ret * 10 + post[i] - '0';
				i++;
			}
			push_num(&S, ret);                 //�����ѹջ
			ret = 0;
			break;
		default:
			i++;
			break;
		}
	}
	return *S.ebp;                            //������ջ��Ԫ�ط���
	free(S.ebp);
}



void CreatSatck(pStack S)               //����һ��ջ
{
	S->ebp = (ElemType *)malloc(STACK_INIT_MEMORY*sizeof(ElemType));
	if (S->ebp == NULL)
	{
		printf("out of memory\n");
		exit(1);
	}
	S->esp = S->ebp;                   //��ʼ��
	S->sz = STACK_INIT_MEMORY;
}

int pop(pStack S, ElemType *x)
{
	assert(S);
	if (S->ebp == S->esp)
	{
		return  0;                //����0�׳�ʧ��
	}
	*x = *(--S->esp);
	return 1;                    //����1��ʾ�ɹ��׳�
}

void  push(pStack S, ElemType x)
{
	assert(S);
	if (S->esp - S->ebp >= S->sz)                //���ջ����׷�ӿռ�
	{
		ElemType *tmp = NULL;
		tmp = (ElemType  *)realloc(S->ebp, (S->sz + ADD_MEMORY)*sizeof(ElemType));
		if (tmp == NULL)
		{
			printf("out of memory\n");
			exit(1);
		}
		S->ebp = tmp;
		S->esp = S->ebp + S->sz;
		S->sz += ADD_MEMORY;
	}
	*(S->esp) = x;
	S->esp++;
}

void CreatSatck_num(pStack_num S)
{
	S->ebp = (int *)malloc(STACK_INIT_MEMORY*sizeof(int));
	if (S->ebp == NULL)
	{
		printf("out of memory\n");
		exit(1);
	}
	S->esp = S->ebp;                            //��ʼ��
	S->sz = STACK_INIT_MEMORY;
}

int pop_num(pStack_num S, int *x)
{
	assert(S);
	if (S->ebp == S->esp)
	{
		return  0;                //����0�׳�ʧ��
	}
	*x = *(--S->esp);
	return 1;                    //����1��ʾ�ɹ��׳�
}

void  push_num(pStack_num S, int x)
{
	int *tmp = NULL;
	assert(S);
	if (S->esp - S->ebp >= S->sz)            //ջ����׷�ӿռ�
	{
		tmp = (int *)realloc(S->ebp, (S->sz + ADD_MEMORY)*sizeof(int));
		if (tmp == NULL)
		{
			printf("out of memory\n");
			exit(1);
		}
		S->ebp = tmp;
		S->esp = S->ebp + S->sz;
		S->sz += ADD_MEMORY;
	}
	*(S->esp) = x;
	S->esp++;
}
void Quit()
{
	exit(1);
}


void transform(int n, int k)
{
	Stack_num S;
	int m = 0, r = 0;
	int x = 0;
	CreatSatck_num(&S);
	r = n;
	while (r)
	{
		m = r % k;
		push_num(&S, m);
		r = r / k;
	}
	printf("ת�����ƺ��ֵΪ:");
	while (!(S.ebp == S.esp))
	{
		pop_num(&S, &x);
		if (x<10)
			printf("%d", x);
		else
		{
			printf("%c", x - 10 + 'a');
		}
	}
	printf("\n");
}
