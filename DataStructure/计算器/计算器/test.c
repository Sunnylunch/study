#include"calculator.h"


void Menu()
{
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("*0.exit                 1.Create_Expr   *\n");
	printf("*2.Transmit_Expr        3.Evaluate_Expr *\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("请选择：>");
}

void test()
{
	ElemType arr[MAX] = { 0 };
	int n = 0;
	int ret = 0;
	ElemType *p = NULL;
	while (1)
	{
		Menu();
		scanf("%d", &n);
		switch (n)
		{
		case 0:
			exit(1);
			break;
		case 1:
			printf("请输入一个合法的中缀表达式\n");
			CreateExpression(arr);
			printf("%s\n", arr);
			break;
		case 2:
			TransmitExpression(arr);

			break;
		case 3:
			ret=EvaluateExpression();
			printf("%d\n",ret);
			break;
		default:
			printf("选择无效\n");
			break;
		}

	}
}



int main()
{
	test();
	system("pause");
	return 0;
}