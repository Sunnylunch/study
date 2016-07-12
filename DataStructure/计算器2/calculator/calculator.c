#include"calculator.h"

DataType arr2[8] = { '+', '-', '%', '*', '/', '^', '(', ')' };      //创建一个索引数组
DataType from[8][8] = { 0 };                                         //优先级关系表格
DataType data[50] = { 0 };

void SymbolList()                                            //初始化优先级表格
{
	int p[8] = {1,1,2,3,3,4,5,0};
	int i = 0;
	int j = 0;                        
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (i == 6 || i == 7)
			{
				if (i == 6)
				{
					if (j == 7)
						from[i][j] = '=';
					else
						from[i][j] = '<';
				}
				else
				{
					from[i][j] = '>';
				}

			}
			else
			{
				if (p[i] >= p[j])               //如果栈顶符号的优先级高于读入符号，from中为>
				    from[i][j] = '>';
				else if (p[i] <= p[j])          //如果栈顶符号的优先级小于读入符号，from中为<
					from[i][j] = '<';
			}
		}
	}
}


DataType check(pStack p, DataType x)                        //查找优先级关系
{
	char c = 0;
	pop(p, &c);
	int i = 0;
	int j = 0;
	for (i = 0; i < 8; i++)                       //from中行下标
	{
		if (arr2[i] == c)
			break;
	}
	for (j = 0;j < 8; j++)                         //from列下标
	{
		if (arr2[j] == x)
			break;
	}
	push(p, c);
	return from[i][j];                              //返回优先级关系
}





int JudgeType(DataType c)                           //判断是字符类型
{
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		if (arr2[i] == c)
			return 0;                               //如果是符号，返回0
	}
	if (c == ' ')
		return -1;
	return 1;                                       //如果是数字返回1
}


int opreation(int a, char c, int b)             //运算
{
	int ret = 0;
	switch (c)
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
		if (b==0)
			exit(1);
		else
			ret = a / b;
		break;
	case'%':
		ret = a%b;
		break;
	case'^':
		ret = (int)pow((double)a,(double) b);
		break;
	}
	return ret;
}


void CreatExpression(DataType *arr)
{
	scanf("%s",arr);
}



void TransmitExpression(DataType *arr)
{
	SymbolList();
	Stack p;
	DataType x = 0;
	CreatSatck(&p);
	int i = 0;
	int j = 0;
	while (arr[i] != '\0')
	{
		if (JudgeType(arr[i]))                 //读取的是数字
		{
			data[j++] = arr[i];                 //数字直接保存在data里面
			if (JudgeType(arr[i + 1]) != 1)
				data[j++] = ' ';                 //空格隔开
			i++;
		}
		else
		{
			if (p.low == p.top)                //栈是空栈，则直接压栈
			{
				push(&p,arr[i]);
				i++;
			}
			else
			{
				switch (check(&p, arr[i]))     
				{
				case '>':                        //栈顶符号的优先级高,退栈
					if(pop(&p, &x))
					{
						data[j++] = x;
						data[j++] = ' ';         //以空格隔开
					}
					break;
				case '<':                        //读取的优先级高，直接压栈
					push(&p,arr[i]);
					i++;
					break;
				case '=':
					pop(&p, &x);
					i++;
					break;
				}
			}
		}
	}
	while (pop(&p, &x))                                     //将剩下的符号全部退栈
	{
		data[j++] = ' ';
		data[j++] =x;
	}
	printf("%s\n", data);
	free(p.low);
}



int EvaluateExpression()
{
	StackFigure p;
	int sum = 0;
	CreatSatckFigure(&p);
	int i = 0;
	int a = 0;
	int b = 0;
	while (data[i] != '\0')                    //读取后缀表达式数组中的符号 
	{
		switch (JudgeType(data[i]))
		{
		case 0:                                 //读取的是符号
			pop_figure(&p, &b);                 //将数字栈上面两个数字退栈
			pop_figure(&p, &a);
			sum = opreation(a,data[i],b);       //将这两个数字运算，并将结果返回
			push_figure(&p, sum);               //将结果入栈
			sum = 0;
			i++;
			break;
		case 1:
			while (data[i] != ' ')                 //将连续的数字全部读取，并转化为相应的整数
			{
				sum = sum * 10 + data[i]-'0';
				i++;
			}
			push_figure(&p,sum);                 //将运算结果压栈
			sum= 0;
			break;
		default:
			i++;
			break;
		}
	}
	pop_figure(&p, &sum);
	return sum;                                   //将数字栈剩下的元素返回
	free(p.low);
}


void CreatSatckFigure(pStackFigure p)
{
	p->low = (int *)malloc(INIT_SIZE*sizeof(int));
	if (p->low == NULL)
	{
		exit(1);
	}
	p->top = p->low;                            //初始化
	p->i = INIT_SIZE;
}

int pop_figure(pStackFigure p, int *x)
{
	if (p == NULL)
		exit(1);
	if (p->low == p->top)
	{
		return  0;                //返回0抛出失败
	}
	p->top--;
	*x = *p->top;
	return 1;                    //返回1表示成功抛出
}

void push_figure(pStackFigure p, int x)
{
	if (p == NULL)
		exit(1);
	if (p->top - p->low >= p->i)            //栈满则追加空间
	{
		int *dst = NULL;
		dst = (int *)realloc(p->low, (p->i + ADD_SIZE)*sizeof(int));
		if (dst == NULL)
		{
			exit(1);
		}
		p->low = dst;
		p->top = p->low + p->i;
		p->i += ADD_SIZE;
	}
	*(p->top) = x;
	p->top++;
}

void CreatSatck(pStack p)               
{
	p->low = (DataType *)malloc(INIT_SIZE*sizeof(DataType));
	if (p->low == NULL)
	{
		exit(1);
	}
	p->top = p->low;                   
	p->i =INIT_SIZE;
}

int pop(pStack p, DataType *x)
{
	if (p == NULL)
		exit(1);
	if (p->low == p->top)
	{
		return  0;                //返回0抛出失败
	}
	p->top--;
	*x = *p->top;
	return 1;                    //返回1表示成功抛出
}

void  push(pStack p, DataType x)
{
	if (p== NULL)
		exit(1);
	if (p->top - p->low >= p->i)             
	{
		DataType *tmp = NULL;
		tmp = (DataType  *)realloc(p->low, (p->i + ADD_SIZE)*sizeof(DataType));
		if (tmp == NULL)
		{
			exit(1);
		}
		p->low = tmp;
		p->top = p->low + p->i;
		p->i +=ADD_SIZE;
	}
	*(p->top)= x;
    p->top++;
}



void binary_system(int num)                                    //二进制转换
{
	StackFigure p;
	int tmp = 0;
	int ret = 0;
	CreatSatckFigure(&p);
	while (num)
	{
		tmp =num % 2;
	    push_figure(&p, tmp);
		num= num / 2;
	}
	printf("转换进制后的值为:");
	while (!(p.low == p.top))
	{
		pop_figure(&p, &ret);	
		printf("%d", ret);
	}
	printf("\n");
}


void octonary_number_system(int num)                          //八进制转换
{
	StackFigure p;
	int tmp = 0;
	int ret = 0;
	CreatSatckFigure(&p);
	while (num)
	{
		tmp = num % 8;
		push_figure(&p, tmp);
		num = num / 8;
	}
	printf("转换进制后的值为:");
	while (!(p.low == p.top))
	{
		pop_figure(&p, &ret);
		printf("%d", ret);
	}
	printf("\n");
}


int binary_decimal()
{
	int i = 0;
	int x = 0;
	int sum = 0;
	StackFigure p;
	CreatSatckFigure(&p);
	DataType src[50] = { 0 };
	printf("请输入32位以内的二进制序列：");
	scanf("%s", src);
	while (src[i])
	{
		switch (src[i])
		{
		case '0':
			push_figure(&p, 0);
			break;
		case '1':
			push_figure(&p, 1);
			break;
		default:
			exit(EXIT_FAILURE);
			break;
		}
		i++;
	}
	i = 0;
	while (p.low != p.top)
	{
		pop_figure(&p, &x);
		sum = sum + x*(int)pow((double)2, (double)i);
		i++;
	}
	return sum;
}



int Octal_decimal()
{
	int i = 0;
	int x = 0;
	int sum = 0;
	StackFigure p;
	CreatSatckFigure(&p);
	DataType src[50] = { 0 };
	printf("请输入八进制序列：");
	scanf("%s", src);
	while (src[i])
	{
		if (src[i] >= '0'&&src[i] <= '7')
		{
			push_figure(&p,src[i]-'0');
		}
		else
		{
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (p.low != p.top)
	{
		pop_figure(&p,&x);
		sum = sum + x*(int)pow((double)8, (double)i);
		i++;
	}
	return sum;
}

void Quit()
{
	exit(EXIT_FAILURE);
}