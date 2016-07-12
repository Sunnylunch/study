
#include"calculator.h"

ElemType arr2[10] = { '&','|','+', '-', '%', '*', '/', '^', '(', ')' };              //创建一个索引数组
ElemType list[10][10] = { 0 };                                         //创建一个优先级关系表
ElemType post[100] = { 0 };

void init_list()                                                   //初始化优先级关系
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
				if (p[i] >= p[j])               //如果栈顶符号的优先级高于读入符号，list中为>
					list[i][j] = '>';
				else if (p[i] <= p[j])          //如果栈顶符号的优先级小于读入符号，list中为<
					list[i][j] = '<';
			}
		}
	}
}


ElemType priority(pStack S, ElemType x)                         //查找优先级关系
{
	char c = 0;
	int line = 0;
	int row = 0;
	pop(S, &c);
	for (line = 0; line < 10; line++)                             //以栈顶符号所在位置为list中行下标
	{
		if (arr2[line] == c)
			break;
	}
	for (row = 0; row < 10; row++)                                //以读取符号所在位置为list中列下标
	{
		if (arr2[row] == x)
			break;
	}
	push(S, c);
	return list[line][row];                                     //返回优先级关系
}





int judge_type(ElemType c)               //判断是符号还是 数字
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		if (arr2[i] == c)
			return 0;             //如果是符号，返回0
	}
	if (c == ' ')
		return -1;
	return 1;                       //如果是数字返回1
}


int opreation(int a, char symbol, int b)             //进行运算
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
		if (judge_type(arr[i]))                 //如果读取的是数字
		{
			post[j++] = arr[i];                //数字直接保存在post里面
			if (judge_type(arr[i + 1]) != 1)
				post[j++] = ' ';                //以空格隔开
			i++;
		}
		else
		{
			if (S.ebp == S.esp)                //如果栈是空栈，则直接压栈
			{
				push(&S, arr[i]);
				i++;
			}
			else
			{
				switch (priority(&S, arr[i]))
				{
				case '>':                        //如果栈顶符号的优先级高，则先退栈
					if (pop(&S, &x))
					{
						post[j++] = x;
						post[j++] = ' ';         //以空格隔开
					}
					break;
				case '<':                        //如果读取的优先级高，则直接压栈
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
	while (pop(&S, &x))                                     //将剩下的符号全部退栈
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
	while (post[i] != '\0')                    //读取后缀表达式数组中的符号 
	{
		switch (judge_type(post[i]))
		{
		case 0:                              //如果读取的是符号
			pop_num(&S, &b);                 //将数字栈上面两个数字退栈
			pop_num(&S, &a);
			ret = opreation(a, post[i], b);    //将这两个数字运算，并将结果返回
			push_num(&S, ret);               //将结果入栈
			ret = 0;
			i++;
			break;
		case 1:
			while (post[i] != ' ')            //将连续的数字全部读取，并转化为相应的整数
			{
				ret = ret * 10 + post[i] - '0';
				i++;
			}
			push_num(&S, ret);                 //将结果压栈
			ret = 0;
			break;
		default:
			i++;
			break;
		}
	}
	return *S.ebp;                            //将数字栈底元素返回
	free(S.ebp);
}



void CreatSatck(pStack S)               //创建一个栈
{
	S->ebp = (ElemType *)malloc(STACK_INIT_MEMORY*sizeof(ElemType));
	if (S->ebp == NULL)
	{
		printf("out of memory\n");
		exit(1);
	}
	S->esp = S->ebp;                   //初始化
	S->sz = STACK_INIT_MEMORY;
}

int pop(pStack S, ElemType *x)
{
	assert(S);
	if (S->ebp == S->esp)
	{
		return  0;                //返回0抛出失败
	}
	*x = *(--S->esp);
	return 1;                    //返回1表示成功抛出
}

void  push(pStack S, ElemType x)
{
	assert(S);
	if (S->esp - S->ebp >= S->sz)                //如果栈满则追加空间
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
	S->esp = S->ebp;                            //初始化
	S->sz = STACK_INIT_MEMORY;
}

int pop_num(pStack_num S, int *x)
{
	assert(S);
	if (S->ebp == S->esp)
	{
		return  0;                //返回0抛出失败
	}
	*x = *(--S->esp);
	return 1;                    //返回1表示成功抛出
}

void  push_num(pStack_num S, int x)
{
	int *tmp = NULL;
	assert(S);
	if (S->esp - S->ebp >= S->sz)            //栈满则追加空间
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
	printf("转换进制后的值为:");
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
