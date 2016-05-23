#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

//第一种

void print(int arr[], int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (arr[i] != 0)
			break;
	}
	for (; i < n; i++)
	{
		printf("%d", arr[i]);
	}
	printf("\n");
}
int counts(int *p, int n)
{
	int i = 0;
	int num = 0;                                      //设置一个进位信号
	for (i = n - 1; i >= 0; i--)
	{
		p[i]+=num;                                    //如果num不为0则，给p[i]进位
		num = 0;                                      //进位完成后要将num置0
		if (i == n - 1)                               //给最低位自增
			p[i]++; 
		if (p[i]>= 10)                                //如果p[i]等于10，则有可能要进位
		{
			if (i > 0)                                //如果不是最高位，则进位
			{ 
				p[i] -= 10;                            //将p[i]清零
				num = 1;                               //将进位信号置
			}
			else
			{
				return 0;                              //如果是最高位，则程序结束
			}
		}
		else
		{
			break;                                      //如果不进位，则跳出循环进行打印
		}
	}
	return 1;                                           //返回1进行打印
}

void output(int *p, int n)
{
	while (counts(p, n))
	{
		print(p, n);
	}
}


int main()
{
	int n = 0;
	scanf("%d", &n);
	int *p = (int *)calloc(n, sizeof(int));
	output(p, n);
	free(p);
	p = NULL;
	system("pause");
	return 0;
}


//第二种
void print(int arr[], int n)
{
	int i = 0;
	for (i = 0; i < n; i++)                      //寻找到第一个不为0的数
	{
		if (arr[i] != 0)
			break;
	}
	for (; i < n; i++)                          //从这个数开始打印
	{
		printf("%d", arr[i]);
	}
	printf("\n");
}

void arrang(int *p, int n, int m)
{
	int i = 0;
	if (m == n - 1)
	{
		print(p, n);                                 //递归终止条件
		return;
	}
	for (i = 0; i < 10; i++)
	{
		p[m + 1] = i;
		arrang(p, n, m + 1);                            //对着n位数进行全排列，每一位都有0到9十种可能
	}
}

int main()
{
	int n = 0;
	scanf("%d", &n);
	int *p = (int *)calloc(n, sizeof(int));
	arrang(p, n, -1);
	free(p);
	system("pause");
	return 0;
}