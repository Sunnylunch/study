
//һ��������ֻ��һ�����ֳ���һ�Σ��������ֶ��������Σ�ʹ�����ķ����ҳ�����������ֵ���

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


int check_along_num(int *arr, int len)
{
	assert(arr);
	int bit[32] = { 0 };
	int i = 0;
	int j = 0;
	int ret = 0;
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < 32; j++)
		{
			bit[j] += ((arr[i] >> j) & 1);        //ͳ������������Ԫ��ÿһλ��1�ĸ���֮��
		}
	}
	for (i = 0; i < 32; i++)
	{
		ret += ((1 << i)&((bit[i] % 3) << i));         //�������ε�������bit[]�ж�Ӧλ����3�ı���
	}
	return ret;
}
int main()
{
	int arr[10];
	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &arr[i]);
	}
	int sz = sizeof(arr) / sizeof(arr[0]);
	int ret = check_along_num(arr, sz);
	printf("%d\n", ret);
	system("pause");
	return 0;
}