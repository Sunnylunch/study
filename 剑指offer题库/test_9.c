#include<stdio.h>
#include<stdlib.h>


//�ݹ�
int fib(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	return fib(n - 1) + fib(n - 2);
}



//�ǵݹ�
int fib(int n)
{
	int num1 = 0;
	int num2 = 1;
	for (int i = 0; i < n; i++)
	{
		num1 = num1 + num2;                //��num1��num2�ĺ�һ���ֵ���浽num1����
		num2 = num1 - num2;                //�ٽ�num2����ԭ��num1��ֵ
	}
	return num1;
}



//test
int main()
{
	int n = 0;
	scanf("%d", &n);
	int ret = fib(n);
	printf("%d\n", ret);
	system("pause");
	return 0;
}