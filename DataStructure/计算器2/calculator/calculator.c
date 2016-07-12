#include"calculator.h"

DataType arr2[8] = { '+', '-', '%', '*', '/', '^', '(', ')' };      //����һ����������
DataType from[8][8] = { 0 };                                         //���ȼ���ϵ���
DataType data[50] = { 0 };

void SymbolList()                                            //��ʼ�����ȼ����
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
				if (p[i] >= p[j])               //���ջ�����ŵ����ȼ����ڶ�����ţ�from��Ϊ>
				    from[i][j] = '>';
				else if (p[i] <= p[j])          //���ջ�����ŵ����ȼ�С�ڶ�����ţ�from��Ϊ<
					from[i][j] = '<';
			}
		}
	}
}


DataType check(pStack p, DataType x)                        //�������ȼ���ϵ
{
	char c = 0;
	pop(p, &c);
	int i = 0;
	int j = 0;
	for (i = 0; i < 8; i++)                       //from�����±�
	{
		if (arr2[i] == c)
			break;
	}
	for (j = 0;j < 8; j++)                         //from���±�
	{
		if (arr2[j] == x)
			break;
	}
	push(p, c);
	return from[i][j];                              //�������ȼ���ϵ
}





int JudgeType(DataType c)                           //�ж����ַ�����
{
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		if (arr2[i] == c)
			return 0;                               //����Ƿ��ţ�����0
	}
	if (c == ' ')
		return -1;
	return 1;                                       //��������ַ���1
}


int opreation(int a, char c, int b)             //����
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
		if (JudgeType(arr[i]))                 //��ȡ��������
		{
			data[j++] = arr[i];                 //����ֱ�ӱ�����data����
			if (JudgeType(arr[i + 1]) != 1)
				data[j++] = ' ';                 //�ո����
			i++;
		}
		else
		{
			if (p.low == p.top)                //ջ�ǿ�ջ����ֱ��ѹջ
			{
				push(&p,arr[i]);
				i++;
			}
			else
			{
				switch (check(&p, arr[i]))     
				{
				case '>':                        //ջ�����ŵ����ȼ���,��ջ
					if(pop(&p, &x))
					{
						data[j++] = x;
						data[j++] = ' ';         //�Կո����
					}
					break;
				case '<':                        //��ȡ�����ȼ��ߣ�ֱ��ѹջ
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
	while (pop(&p, &x))                                     //��ʣ�µķ���ȫ����ջ
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
	while (data[i] != '\0')                    //��ȡ��׺���ʽ�����еķ��� 
	{
		switch (JudgeType(data[i]))
		{
		case 0:                                 //��ȡ���Ƿ���
			pop_figure(&p, &b);                 //������ջ��������������ջ
			pop_figure(&p, &a);
			sum = opreation(a,data[i],b);       //���������������㣬�����������
			push_figure(&p, sum);               //�������ջ
			sum = 0;
			i++;
			break;
		case 1:
			while (data[i] != ' ')                 //������������ȫ����ȡ����ת��Ϊ��Ӧ������
			{
				sum = sum * 10 + data[i]-'0';
				i++;
			}
			push_figure(&p,sum);                 //��������ѹջ
			sum= 0;
			break;
		default:
			i++;
			break;
		}
	}
	pop_figure(&p, &sum);
	return sum;                                   //������ջʣ�µ�Ԫ�ط���
	free(p.low);
}


void CreatSatckFigure(pStackFigure p)
{
	p->low = (int *)malloc(INIT_SIZE*sizeof(int));
	if (p->low == NULL)
	{
		exit(1);
	}
	p->top = p->low;                            //��ʼ��
	p->i = INIT_SIZE;
}

int pop_figure(pStackFigure p, int *x)
{
	if (p == NULL)
		exit(1);
	if (p->low == p->top)
	{
		return  0;                //����0�׳�ʧ��
	}
	p->top--;
	*x = *p->top;
	return 1;                    //����1��ʾ�ɹ��׳�
}

void push_figure(pStackFigure p, int x)
{
	if (p == NULL)
		exit(1);
	if (p->top - p->low >= p->i)            //ջ����׷�ӿռ�
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
		return  0;                //����0�׳�ʧ��
	}
	p->top--;
	*x = *p->top;
	return 1;                    //����1��ʾ�ɹ��׳�
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



void binary_system(int num)                                    //������ת��
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
	printf("ת�����ƺ��ֵΪ:");
	while (!(p.low == p.top))
	{
		pop_figure(&p, &ret);	
		printf("%d", ret);
	}
	printf("\n");
}


void octonary_number_system(int num)                          //�˽���ת��
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
	printf("ת�����ƺ��ֵΪ:");
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
	printf("������32λ���ڵĶ��������У�");
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
	printf("������˽������У�");
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