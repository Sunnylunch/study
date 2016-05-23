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
			if (*psrc2++ == flag)       //ͳ��flag���ֵĴ���
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
		dst[*psrc++]++;            //���ַ����и����ַ����ֵĴ���ͳ�Ƴ���
	}
	while (*src)
	{
		if (dst[*src] == 1)                  //���ַ������ַ���Ϊ�±꣬�������Ӧ������Ԫ��ֵΪ1���ҵ����������±�
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
		printf("�����ڣ�����\n");
	system("pause");
	return 0;
}