#include<stdio.h>
#include<stdlib.h>

int check(int arr[], int len)                               //��arr[]�е�����������Ȼ�󽫽������
{
	int num = 0;
	for (int i = 0; i < len; i++)
	{
		num ^= arr[i];
	}
	return num;
}
void bubble_sort(int arr[], int len)                         //ʹ��ð�����򣬶����������������
{
	int i = 0;
	int j = 0;
	int flag=0;
	for (i = 0; i < len - 1; i++)
	{
		flag = 1;
		for (j = 0; j < len - 1 - i; j++)
		{
			if (arr[j]>arr[j + 1])
			{
				arr[j] = arr[j] + arr[j + 1];
				arr[j + 1] = arr[j] - arr[j + 1];
				arr[j] = arr[j] - arr[j + 1];
				flag = 1;
			}
		}
		if (flag)
			return;
	}
}

void  check_alone(int arr[], int len, int *num1, int *num2)
{
	bubble_sort(arr, len);
	int i = 0;
	for (i = 0; i < len - 1; i+=2)                      //ÿ���ж�������
	{
		if (arr[i] != arr[i + 1])                       //���������������ȣ�����м�ֿ����ͽ�����ֳ���������
		{
			*num1 = check(arr, i + 1);
			*num2 = check(&arr[i + 1], len - i-1);
		}
	}
}



int check(int arr[],int len)
{
	int num = 0;
	for (int i = 0; i < len; i++)
	{
		num ^= arr[i];
	}
	return num;
}
void check_alone(int arr[],int len, int *num1, int *num2)
{
	int i = 0;
	int ret=check(arr, len);
	for (i = 0; i < 32;i++)                                   //���ҵ�һλΪ1��bitλ
	{
		if ((ret >> i) & 1)
			break;
	}
	while (len--)                                            //������һλ������ֳ������ֱַ����
	{
		if (((arr[len] >> i) & 1) == 0)
			*num1 ^= arr[len];
		else
			*num2 ^= arr[len];
	}
}
int main()
{
	int arr[10] = { 0 };
	int num1 = 0;
	int num2 = 0;
	int len=sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i <10; i++)
	{
		scanf("%d", &arr[i]);
	}
	check_alone(arr,len, &num1, &num2);
	printf("%d %d\n",num1,num2);
	system("pause");
	return 0;
}