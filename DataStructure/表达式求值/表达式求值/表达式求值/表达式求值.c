#include"expression.h"
int main()
{

	stack_num num_stack;
	creatstack_num(&num_stack);                      //����һ��������ջ
	stack_operation operator_stack;
	creatstack_operation(&operator_stack);           //����һ�������ջ
	int c;
	char symbol;
	int a = 0;
	int b = 0;
	int ret = 0;
	push_operation(&operator_stack, '#');            //����#����ջ����Ϊ�����ջ��ջ��
	c=getchar();
	while (c!='#'||*(operator_stack.esp-1)!='#')     //���ܱ��ʽ�����жϱ��ʽ�Ƿ��������
	{
		
		if (judge_num(c))                            //��������������������ջ
		{
			int num = 0;
			while (judge_num(c))                     //��������char���͵�����ȫ����ȡ��ת������Ӧ������
			{
				num = num * 10 + (c-'0');            //��Ϊ���ǵ���������char���ͣ�������Ҫת����int
				c = getchar();
			}
			push_num(&num_stack,num);                 //����������ջ
		}
		else                                                        
		{
			switch (judge_priority(&operator_stack,c))     //�ж϶�ȡ���������ջ�����ŵ����ȼ���ϵ
			{
			case '<':                                      //�����ȡ�ķ������ȼ��ߣ���ֱ�ӽ��������ջ
				push_operation(&operator_stack, c);
				c=getchar();
				break;
			case '>':                                    //�����ȡ�ķ������ȼ��ͣ���ջ��������ջ������������ջ
				pop_opreation(&operator_stack, &symbol); //��ջ��������ջ
				pop_num(&num_stack, &b);                
				pop_num(&num_stack, &a);                 // ��������ջջ��������Ԫ�ص���
				ret=operation(a, symbol, b);             //��������Ԫ�ؽ�������
				push_num(&num_stack, ret);               //����������ջ
				break;
			case '=':                                     //����ȡ��������ʱ��һֱ��ջֱ������������
				pop_opreation(&operator_stack, &symbol);
				c=getchar();
				break;
			default:
				break;
			}
		}		

	}
	printf("%d\n", *(num_stack.esp-1));                  //��������ջ���ʣ�µ������
	system("pause");
	free(num_stack.ebp);
	free(operator_stack.ebp);
	return 0;
}