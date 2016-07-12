#include"expression.h"
int main()
{

	stack_num num_stack;
	creatstack_num(&num_stack);                      //建立一个运算数栈
	stack_operation operator_stack;
	creatstack_operation(&operator_stack);           //建立一个运算符栈
	int c;
	char symbol;
	int a = 0;
	int b = 0;
	int ret = 0;
	push_operation(&operator_stack, '#');            //将‘#’入栈，作为运算符栈的栈底
	c=getchar();
	while (c!='#'||*(operator_stack.esp-1)!='#')     //接受表达式并且判断表达式是否输入完毕
	{
		
		if (judge_num(c))                            //如果是数字则进入运算数栈
		{
			int num = 0;
			while (judge_num(c))                     //把连续的char类型的数字全部读取并转化成相应的整数
			{
				num = num * 10 + (c-'0');            //因为这是的运算数是char类型，所以先要转换成int
				c = getchar();
			}
			push_num(&num_stack,num);                 //将运算数入栈
		}
		else                                                        
		{
			switch (judge_priority(&operator_stack,c))     //判断读取的运算符与栈顶符号的优先级关系
			{
			case '<':                                      //如果读取的符号优先级高，则直接进入运算符栈
				push_operation(&operator_stack, c);
				c=getchar();
				break;
			case '>':                                    //如果读取的符号优先级低，则栈顶符号退栈，将运算结果入栈
				pop_opreation(&operator_stack, &symbol); //则栈顶符号退栈
				pop_num(&num_stack, &b);                
				pop_num(&num_stack, &a);                 // 将运算数栈栈顶的两个元素弹出
				ret=operation(a, symbol, b);             //将这两个元素进行运算
				push_num(&num_stack, ret);               //将运算结果入栈
				break;
			case '=':                                     //当读取到“）”时则一直退栈直到遇到“（”
				pop_opreation(&operator_stack, &symbol);
				c=getchar();
				break;
			default:
				break;
			}
		}		

	}
	printf("%d\n", *(num_stack.esp-1));                  //将运算数栈最后剩下的数输出
	system("pause");
	free(num_stack.ebp);
	free(operator_stack.ebp);
	return 0;
}