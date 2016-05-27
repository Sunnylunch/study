//declaration
#define _CRT_SECURE_NO_WARNINGS 1

#ifndef  __ADDRESSBOOK_H__           //使用条件编译，防止重复引入头文件

#define  __ADDRESSBOOK_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define  NAME_MAX 20
#define  SEX_MAX 6
#define  TELE_MAX 20
#define  ADDR_MAX 40
#define INIT_SIZE 2
#define ADD_SIZE 10


typedef enum choice
{
	EXIT,
	ADD,
	DELETE,
	CHANGE,
	FIND,
	INIT,
	OUTPUT,
	SORT
}choice;


typedef struct                     //定义一个信息的结构体类型
{
	char name[NAME_MAX];
	char sex[SEX_MAX];
	int age;
	char tele[TELE_MAX];
	char address[ADDR_MAX];

}infor;

typedef struct                           //创建一个顺序表
{
	infor *data;
	int i;                               //表示联系人个数
	int size;                            //表示开辟空间的容量
}sequence;


void Add(sequence *book);
void delete(sequence *book, char *names);
void change(sequence *book, char *names);
void output(sequence const *book);
void init(sequence *book);
void sort(sequence *book);
void find(sequence *book, char *names);
void save_addressbook(sequence *book);         //向文件里面写入信息
void load_addressbook(sequence *book);         //从文件中读取信息
void memory(sequence *book);                   //动态内存开辟函数

#endif




//fun
#include"addressbook.h"

int find_place(sequence *book, char *names)
{
	int n = 0;
	while (n < book->i)
	{
		if (strcmp(book->data[n].name, names) == 0)
			break;
		n++;
	}
	if (n != book->i)
		return n;                       //如果找到则返回这个位置
	return -1;                           //没找到返回-1
}

void find(sequence *book, char *names)
{
	int ret = find_place(book, names);
	if (ret == -1)
		printf("查询无果\n");
	else
		printf("名字：%s 性别： %s 年龄： %d 电话： %s 地址： %s\n",
		book->data[ret].name,
		book->data[ret].sex,
		book->data[ret].age,
		book->data[ret].tele,
		book->data[ret].address);
}

void memory(sequence *book)
{
	infor *p = NULL;
	if (book->size == 0)                  //如果当前没有开辟空间，则开辟一块空间
	{
		p = (infor *)malloc(INIT_SIZE*sizeof(infor));
		if (p == NULL)
			exit(1);
		else
			book->data = p;
		book->size = INIT_SIZE;             
	}
	if (book->i == (book->size - 1))          //如果空间不够，则进行扩容
	{

		p = (infor *)realloc(book->data, (book->size = +ADD_SIZE)*sizeof(infor));
		if (p== NULL)
			exit(1);
		else
			book->data = p;
	}
}
void Add(sequence *book)
{
	memory(book);
	printf("请输入名字:");
	scanf("%s", book->data[book->i].name);
	printf("请输入性别：");
	scanf("%s", book->data[book->i].sex);
	printf("请输入年龄：");
	scanf("%d", &book->data[book->i].age);
	printf("请输入电话：");
	scanf("%s", book->data[book->i].tele);
	printf("请输入地址：");
	scanf("%s", book->data[book->i].address);
	++book->i;
	printf("添加成功\n");
}


void delete(sequence *book, char *names)
{
	if (book->i <= 0)
	{
		printf("通讯录已空\n");
	}
	else
	{
		int n = 0;
		n = find_place(book, names);                       //根据名字查找
		if (n< 0)
		{
			printf("没有此人\n");
		}
		else
		{
			book->data[n] = book->data[book->i - 1];//如果找到，则将最后一条记录放到这个位置
			book->i--;                     //删除一个，则记录位置的book->i也要减一
			printf("删除成功\n");
		}
	}
}

void change(sequence *book, char *names)
{
	int ret = 0;
	ret = find_place(book, names);              //先找到这个人的位置
	if (ret == -1)
	{
		printf("没有此人\n");
	}
	else
	{
		printf("请输入名字:");
		scanf("%s", book->data[ret].name);
		printf("请输入性别：");
		scanf("%s", book->data[ret].sex);
		printf("请输入年龄：");
		scanf("%d", &book->data[ret].age);
		printf("请输入电话：");
		scanf("%s", book->data[ret].tele);
		printf("请输入地址：");
		scanf("%s", book->data[ret].address);
		printf("修改成功\n");
	}
}


void output(sequence const *book)
{
	if (book->i <= 0)
	{
		printf("通讯录为空\n");
	}
	else
	{
		int n = 0;
		printf("%5s %5s %5s %11s %11s\n", "名字", "性别", "年龄", "电话", "地址");
		while (n < book->i)
		{
			printf("%5s %5s %5d %11s %11s\n",
				book->data[n].name,
				book->data[n].sex,
				book->data[n].age,
				book->data[n].tele,
				book->data[n].address);
			n++;
		}

	}
}



void init(sequence *book)
{
	book->i = 0;            //只要将记录位置的book->i置0
	printf("初始化成功\n");
}



void sort(sequence *book)
{
	if (book->i >1)                  //当通讯录中有1个以上记录再进行排序
	{
		int i = 0;
		int j = 0;
		int flag = 0;
		for (i = 0; i < book->i - 1; i++)
		{
			flag = 1;
			for (j = 0; j < book->i - i - 1; j++)
			{
				if (strcmp(book->data[j].name, book->data[j + 1].name) > 0)  //根据名字进行排序
				{
					infor tmp = book->data[j];
					book->data[j] = book->data[j + 1];
					book->data[j + 1] = tmp;
					flag = 0;
				}        //if 结束
			}
			if (flag)     //如果已经有序，则flag为真
				break;
		}
	}
	printf("排序成功\n");
}




void save_addressbook(sequence *book)
{
	int i = 0;
	FILE *pfwrite = fopen("test.txt","w");  //首先打开文件 
	if (pfwrite == NULL)
	{
		perror("open file pfwrite");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < book->i; i++)                                //将当前结构体数组中的信息全部写入
	{
		fwrite(&(book->data[i]), sizeof(infor), 1, pfwrite);     //使用二进制流的方式写入
	}
	fclose(pfwrite);                                              //关闭文件
}


void load_addressbook(sequence *book)
{
	int n = 0;
	infor tmp = { 0 };                           //创建临时变量用来保存每次读取的信息
	FILE *pfread = fopen("test.txt", "r");       //首先打开文件 （test.txt 自己在当前目录底下创建）
	if (pfread == NULL)
	{
		perror("open file pfread");
		exit(EXIT_FAILURE);
	}
	while (fread(&tmp, sizeof(infor), 1, pfread))  //每次读取一条信息，当读取完成后，fread返回0
	{
		memory(book);                              //要加载信息首先要开辟内存，或者内存不够时就要扩容
		book->data[n] = tmp;
		n++;
		book->i++;                              //同时book->i也要增长
	}
	fclose(pfread);
}








//test

#include"addressbook.h"
void meau()
{
	printf("*******************************\n");
	printf("*0.exit              1.Add    *\n");
	printf("*2.deletel           3.change *\n");
	printf("*4.find              5.init   *\n");
	printf("*6.output            7.sort   *\n\n");
}
void execute(sequence *book)
{
	load_addressbook(book);
	char name[20];
	while (1)
	{
		int n = 0;
		meau();
		printf("请选择：");
		scanf("%d", &n);
		switch (n)
		{
		case EXIT:
			save_addressbook(book);
			free(book->data);
			exit(1);
			break;
		case ADD:
			Add(book);
			break;
		case DELETE:
			printf("请输入姓名：");
			scanf("%s", name);
			delete(book, name);
			break;
		case CHANGE:
			printf("请输入姓名：");
			scanf("%s", name);
			change(book, name);
			break;
		case FIND:
			printf("请输入姓名：");
			scanf("%s", name);
			find(book, name);
			break;
		case INIT:
			init(book);
			break;
		case OUTPUT:
			output(book);
			break;
		case SORT:
			sort(book);
			break;
		default:
			printf("选择无效\n");
			break;
		}
	}

}

int main()
{
	sequence book;
	book.i = 0;
	book.size = 0;
	book.data = NULL;
	execute(&book);
	system("pause");
	return 0;
}
