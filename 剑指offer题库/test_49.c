//#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int num = 1;
	num = ~1;
	printf("%d\n", num);
	system("pause");
	return 0;
}
//#include<assert.h>
//int state=0;                 //用来记录是不是正常返回
//long my_atoi(char *arr)
//{
//	assert(arr);
//	long num = 0;             
//	int flag = 1;             //设置标记
//	while (*arr==' ')              //跳过字符串开头的空格
//	{
//		arr++;
//	}
//	if (*arr == '\0')         //如果全部字符串中都是空格
//	{
//		state = 1;            //将state设置成1，表示异常返回
//		return 0;
//	}
//	if (*arr == '-')          //如果跳过空格，再判断有没有正负
//	{
//		flag = -1;            //如果是-，则将flag设置成-1
//		arr++;
//	}
//	else if (*arr == '+')
//	{
//		arr++;
//	}
//	while (*arr >= '0'&&*arr <= '9'&&*arr)          //判断是不是数字字符
//	{
//		if ((num>=(signed long)0x80000000) && (num<=(signed long)0x7FFFFFFF)) //判断有没有溢出
//		{
//			num = num * 10 + flag*(*arr - '0');      //将标记位加上去
//			arr++;
//		}
//		else                                         //如果溢出，则跳出
//			break;
//	}
//	if (*arr != '/0')
//	{
//		state = 1;                                    //state=1,异常返回
//	}
//	return num;
//}
//
//int main()
//{
//	char arr[30] = { 0 };
//    scanf("%s", arr);
//	long ret=my_atoi(arr);
//	if (state == 1)
//	{
//		printf("异常返回\n");
//		state = 0;
//	}
//	printf("%ld\n",ret);
//	system("pause");
//	return 0;
//}