
//一组数据中只有一个数字出现一次，其余数字都出现三次，使用最快的方法找出这个单独出现的数

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
			bit[j] += ((arr[i] >> j) & 1);        //统计数组中所有元素每一位上1的个数之和
		}
	}
	for (i = 0; i < 32; i++)
	{
		ret += ((1 << i)&((bit[i] % 3) << i));         //出现三次的数，在bit[]中对应位上是3的倍数
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