#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

//��һ��

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
	int num = 0;                                      //����һ����λ�ź�
	for (i = n - 1; i >= 0; i--)
	{
		p[i]+=num;                                    //���num��Ϊ0�򣬸�p[i]��λ
		num = 0;                                      //��λ��ɺ�Ҫ��num��0
		if (i == n - 1)                               //�����λ����
			p[i]++; 
		if (p[i]>= 10)                                //���p[i]����10�����п���Ҫ��λ
		{
			if (i > 0)                                //����������λ�����λ
			{ 
				p[i] -= 10;                            //��p[i]����
				num = 1;                               //����λ�ź���
			}
			else
			{
				return 0;                              //��������λ����������
			}
		}
		else
		{
			break;                                      //�������λ��������ѭ�����д�ӡ
		}
	}
	return 1;                                           //����1���д�ӡ
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


//�ڶ���
void print(int arr[], int n)
{
	int i = 0;
	for (i = 0; i < n; i++)                      //Ѱ�ҵ���һ����Ϊ0����
	{
		if (arr[i] != 0)
			break;
	}
	for (; i < n; i++)                          //���������ʼ��ӡ
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
		print(p, n);                                 //�ݹ���ֹ����
		return;
	}
	for (i = 0; i < 10; i++)
	{
		p[m + 1] = i;
		arrang(p, n, m + 1);                            //����nλ������ȫ���У�ÿһλ����0��9ʮ�ֿ���
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