#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


char check(char const *src)
{
	assert(src);
	char const *psrc1 = src;
	char const *psrc2 = src;
	char flag = 0;
	int count = 0;
	while (*psrc1)
	{
		flag = *psrc1++;
		while (*psrc2)
		{
			if (*psrc2++ == flag)       //统计flag出现的次数
				count++;
		}
		psrc2 = src;
		if (count == 1)
			return flag;
		else
			count = 0;
	}
	return 0;
}

char check(char const *src)
{
	assert(src);
	char const *psrc = src;
	int dst[256] = { 0 };
	while (*psrc)
	{
		dst[*psrc++]++;            //将字符串中各个字符出现的次数统计出来
	}
	while (*src)
	{
		if (dst[*src] == 1)                  //以字符串中字符作为下标，查找其对应的数组元素值为1，找到就输出这个下标
			break;
		else
			src++;
	}
	return *src;;
}
int main()
{
	char arr[50] = { 0 };
	scanf("%s", arr);
	//char c = check(arr);
	char c = check(arr);
	if (c != '\0')
		printf("%c\n", c);
	else
		printf("不存在！！！\n");
	system("pause");
	return 0;
}