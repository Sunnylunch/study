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
			    printf("������һ������+-*/%^�ı��ʽ:>\n");
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
				printf("���������֣�>");
				scanf("%d", &num);
				binary_system(num);
				break;
			case OCTONARY:
				printf("���������֣�>");
				scanf("%d", &num);
				octonary_number_system(num);
				break;
			case B_DEC:
				ret=binary_decimal();
				printf("ʮ������Ϊ��%d\n", ret);
				break;
			case OCT_DEC:
				ret=Octal_decimal();
				printf("ʮ������Ϊ��%d\n", ret);
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