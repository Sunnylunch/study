#include"calculator.h"

void Menu()
{
	printf("***********************************\n");
	printf("*0.Quit             1.CreatExpr   *\n");
	printf("*2.TransmitExpr     3.EvaluateExpr*\n");
	printf("*4.transform                      *\n");
	printf("***********************************\n");
}

void text()
{

	ElemType arr[100] = { 0 };
	int x = 0;
	int ret = 0;
	int k = 0;
	int n = 0;
	Menu();
	while (1)
	{
		printf("\n\n��ѡ��:>");
		scanf("%d", &x);
		switch (x)
		{
		case 0:
			Quit();
			break;
		case 1:
			printf("������һ���Ϸ�����׺���ʽ,������+ - * / % ���� ^ & |����:>\n");
			CreatExpression(arr);
			break;
		case 2:
			if (arr[0] == '\0')
			{
				printf("���ȴ���һ����׺���ʽ\n");
				break;
			}
			TransmitExpression(arr);
			break;
		case 3:
			if (post[0] == 0)
			{
				printf("����ת����׺���ʽ\n");
				break;
			}
			ret = EvaluateExpression();
			printf("%d\n", ret);
			break;
		case 4:
			printf("���������֣�>");
			scanf("%d", &n);
			printf("����Ҫת���Ľ��ƣ�>");
			scanf("%d", &k);
			transform(n, k);
			break;
		default:
			printf("ѡ����Ч\n");
			break;
		}
	}
}
int main()
{
	text();
	system("pause");
	return 0;
}
