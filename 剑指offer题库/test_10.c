#include<stdio.h>
#include<stdlib.h>



int count_one(int n)
{
	int count = 0;
	while (n)
	{
		if (n&1)
		count++;
		n=n >> 1;
	}
	return count;
}
//
//int count_one(int n)
//{
//	int i = 0;
//	int count = 0;
//	for (i = 0; i < 32; i++)
//	{
//		count += ((n >>i) & 1);
//	}
//	return count;
//}
//
//
//
//
int count_one(int n)
{
	int count = 0;
	while (n)
	{
		n = n&(n - 1);
		count++;
	}
	return count;
}
int main()
{
	int n = 0;
	scanf("%d", &n);
	int ret = count_one(n);
	printf("%d\n", ret);
	system("pause");
	return 0;
}