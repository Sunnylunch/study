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
//int state=0;                 //������¼�ǲ�����������
//long my_atoi(char *arr)
//{
//	assert(arr);
//	long num = 0;             
//	int flag = 1;             //���ñ��
//	while (*arr==' ')              //�����ַ�����ͷ�Ŀո�
//	{
//		arr++;
//	}
//	if (*arr == '\0')         //���ȫ���ַ����ж��ǿո�
//	{
//		state = 1;            //��state���ó�1����ʾ�쳣����
//		return 0;
//	}
//	if (*arr == '-')          //��������ո����ж���û������
//	{
//		flag = -1;            //�����-����flag���ó�-1
//		arr++;
//	}
//	else if (*arr == '+')
//	{
//		arr++;
//	}
//	while (*arr >= '0'&&*arr <= '9'&&*arr)          //�ж��ǲ��������ַ�
//	{
//		if ((num>=(signed long)0x80000000) && (num<=(signed long)0x7FFFFFFF)) //�ж���û�����
//		{
//			num = num * 10 + flag*(*arr - '0');      //�����λ����ȥ
//			arr++;
//		}
//		else                                         //��������������
//			break;
//	}
//	if (*arr != '/0')
//	{
//		state = 1;                                    //state=1,�쳣����
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
//		printf("�쳣����\n");
//		state = 0;
//	}
//	printf("%ld\n",ret);
//	system("pause");
//	return 0;
//}