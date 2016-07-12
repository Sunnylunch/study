#include"calculator.h"


void Menu()
{
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~0.Quit             1.Creat           ~~\n") ;
	printf("~~2.Transmit         3.Evaluate        ~~\n");
	printf("~~4.binary_system    5.octonary_system ~~\n");
	printf("~~6.Octal_decimal    7.octonary_system ~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("choice:>");
}

void test()
{
	DataType arr[100] = { 0 };
	int x= 0;
	int ret = 0;
	int k = 0;
	int num = 0;
	while (1)
	{
		Menu();
		scanf("%d", &x);
		switch (x)
			{
			case EXIT:
				Quit();
				break;
			case CREATE:
			    printf("请输入一个具有+-*/%^的表达式:>\n");
				CreatExpression(arr);
				break;
			case TRANSMIT:
				TransmitExpression(arr);
				break;
			case VALUATE:
				ret = EvaluateExpression();
				printf("%d\n", ret);
				break;
			case BINARY:
				printf("请输入数字：>");
				scanf("%d", &num);
				binary_system(num);
				break;
			case OCTONARY:
				printf("请输入数字：>");
				scanf("%d", &num);
				octonary_number_system(num);
				break;
			case B_DEC:
				ret=binary_decimal();
				printf("十进制数为：%d\n", ret);
				break;
			case OCT_DEC:
				ret=Octal_decimal();
				printf("十进制数为：%d\n", ret);
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