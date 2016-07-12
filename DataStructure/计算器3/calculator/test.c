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
		printf("\n\n请选择:>");
		scanf("%d", &x);
		switch (x)
		{
		case 0:
			Quit();
			break;
		case 1:
			printf("请输入一个合法的中缀表达式,包含“+ - * / % （） ^ & |运算:>\n");
			CreatExpression(arr);
			break;
		case 2:
			if (arr[0] == '\0')
			{
				printf("请先创建一个中缀表达式\n");
				break;
			}
			TransmitExpression(arr);
			break;
		case 3:
			if (post[0] == 0)
			{
				printf("请先转换后缀表达式\n");
				break;
			}
			ret = EvaluateExpression();
			printf("%d\n", ret);
			break;
		case 4:
			printf("请输入数字：>");
			scanf("%d", &n);
			printf("请输要转化的进制：>");
			scanf("%d", &k);
			transform(n, k);
			break;
		default:
			printf("选择无效\n");
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
