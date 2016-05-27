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
			if (i == 4)                                  //如果栈顶符号是‘（’，则它的优先级最小
			{
				if (j==5)                                 //'(',')'的优先级相同
				list[i][j] = '=';
				else
					list[i][j] = '<';
			}
			else
			{
				if (arr1[i] >= arr1[j])
					list[i][j] = '>';                        //栈顶优先级高
				else if (arr1[i] <= arr1[j])
					list[i][j] = '<';                        //读取的运算符优先级高
			}

		}
	}
}

int judge_type(char c)                             //判断读取的是数字还是字符
{
	int i = 0;
	for (i = 0; i < 6; i++)
	{
		if (dst[i] == c)
			return 0;                        //如果是数符号则返回0
	}
	if (c == ' ')
		return -1;                           //如果是空格则返回-1
	return 1;                                 //如果是数字则返回1
		                                 
}

char judge_priority(pStack S,char c)                  //判断栈顶运算符与读取的运算符的优先级
{                               
	int line = 0;
	int row = 0;
	for (line = 0; line < 6; line++)
	{
		if (dst[line] == *(S->esp - 1))         //将栈顶符号在dst[]中的位置作为行下标
			break;
	}
	for (row = 0; row < 6; row++)
	{
		if (dst[row] == c)                     //将读取的运算符在dst[]中的位置作为列下标
			break;
	}
	return list[line][row];                      //通过优先级表，返回优先级关系
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
				perror("除数不能为零。/n");
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
	CreateStack(&S);                                 //创建一个栈
	ElemType x= 0;
	int i = 0;
	int j = 0;
	while (arr[i] != '\0')
	{ 
		if (judge_type(arr[i]) == 1)                          //判断是不是数字
		{
			post[j++] = arr[i];                               //数字则直接存入post[]
			if (judge_type(arr[i+1]) != 1)
				post[j++]=' ';                                //以空格隔开
			i++;
		}
		else
		{
			if (S.ebp == S.esp)                            //如果栈为空，压栈
			{
				push(&S, arr[i]);
				i++;
			}
			else
			{
				switch (judge_priority(&S, arr[i]))
				{
				case '<':                              //如果栈顶的优先级低。则直接入栈
					push(&S, arr[i]);
					i++;
					break;
				case '>':                             //如果读取的优先级高，则栈顶先退栈
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
		case 0:                                     //读取的是符号
			pop_num(&S, &b);                        //取除数字栈的栈顶元素
			pop_num(&S,&a);                         //取除数字栈的栈顶元素
			ret=operation(a,post[i],b);           //对这两个数进行运算
			push_num(&S, ret);                      //将运算结果入站
			i++;
			ret = 0;
			break;
		case 1:       
			while(judge_type(post[i])==1)
			{
				ret = ret * 10 + post[i] - '0';        //将字符数字转换成对应的整数
				i++;
			}
			push_num(&S, ret);                        //将这个数字进行压栈
			ret = 0;
			break;
		case -1:                                    //读取的是空格
			i++;
			break;
		}
	}
	ret = *(--(S.esp));                            //弹出栈底数字
	free(S.ebp);
	return ret;
}



void CreateStack(pStack S)
{
	S->ebp = (ElemType *)malloc(sizeof(ElemType)* STACK_INIT_MEMORY);
	if (S->ebp == NULL)                      //判断动态内存是否开辟成功
		exit(1);
	S->size = STACK_INIT_MEMORY;
	S->esp = S->ebp;
}


void push(pStack S, ElemType x)
{
	if (S->esp - S->ebp >= S->size)         //判断当前栈是否已满
	{                                       //栈满追加空间
		S->ebp = (ElemType *)realloc(S->ebp, sizeof(ElemType)*(S->size + STACK_GROW_MEMORY));
		if (S->ebp == NULL)                 //判断内存是否开辟成功
			exit(1);
		S->esp = S->ebp + S->size;              //让栈顶指针向后偏移指向要入栈的位置
		S->size += STACK_GROW_MEMORY;
	}
	*(S->esp)++ = x;
}


int pop(pStack S,ElemType *x)
{
	if (S->esp == S->ebp)
	{
		return 0;     //栈已空
	}
	else
	{
		S->esp--;
		*x = *(S->esp);
		return 1;     //退栈成功
	}
}




void CreateStack_num(pStack_num S)
{
	S->ebp = (int *)malloc(sizeof(int)* STACK_INIT_MEMORY);
	if (S->ebp == NULL)                      //判断动态内存是否开辟成功
		exit(1);
	S->size = STACK_INIT_MEMORY;
	S->esp = S->ebp;
}


void push_num(pStack_num S, int x)
{
	if (S->esp - S->ebp >= S->size)         //判断当前栈是否已满
	{                                       //栈满追加空间
		S->ebp = (int *)realloc(S->ebp, sizeof(int)*(S->size + STACK_GROW_MEMORY));
		if (S->ebp == NULL)                 //判断内存是否开辟成功
			exit(1);
		S->esp = S->ebp + S->size;              //让栈顶指针向后偏移指向要入栈的位置
		S->size += STACK_GROW_MEMORY;
	}
	*(S->esp)++ = x;
}


int pop_num(pStack_num S,int *x)
{
	if (S->esp == S->ebp)
	{
		return 0;     //栈已空
	}
	else
	{
		*x = *(--S->esp);
		return 1;     //退栈成功
	}
}