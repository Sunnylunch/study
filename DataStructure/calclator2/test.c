#include"calculator.h"


void Menu()
{
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("*0.exit                 1.Create_Expr   *\n");
	printf("*2.Transmit_Expr        3.Evaluate_Expr *\n\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
	printf("��ѡ��>");
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
			printf("������һ���Ϸ�����׺���ʽ\n");
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
			printf("ѡ����Ч\n");
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