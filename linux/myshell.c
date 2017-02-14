#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<wait.h>
#include<pwd.h>
#include<string.h>

void GetLoginName()                //获取登录名
{
	struct passwd *pwd;
	pwd = getpwuid(getuid());
	printf("[%s@", pwd->pw_name);
}

void GetHostName()           //获取登录主机名
{ 
	char name[100] = { 0 };
	gethostname(name, sizeof(name)-1);
	printf("%s", name);
}

void GetDir()               //获取当前工作路径
{
	char pwd[100] = { 0 };
	getcwd(pwd, sizeof(pwd)-1);    //pwd保存的是绝对路径，所以要对他进行处理
	int len = strlen(pwd);
	char* p = pwd + len;
	while (*p != '/'&&len--)
	{
		p--;
	}
	p++;
	printf(" %s]#", p);
}


void myShell()
{
	while (1)
	{
		GetLoginName();
		GetHostName();
		GetDir();
		fflush(stdout);

		char line[1024];                  //解析输入的指令
		ssize_t s = read(0, line, 1024);
		char* myArgv[10];
		char* start = line;
		myArgv[0] = start;
		int i = 1;
		if (s>0)
		{
			while (*start)
			{
				if (isspace(*start))
				{
					while (isspace(*start))
					{
						*start = '\0';
						start++;
					}
					myArgv[i++] = start;
				}
				else
				{
					start++;
				}

			}
		}
		else
		{
			continue;
		}
		myArgv[i - 1] = NULL;


		pid_t id = vfork();
		if (id == 0)
		{

			execvp(myArgv[0], myArgv);
			perror("error ");
		}
		else
		{
			sleep(1);
			wait(NULL);
		}
		printf("\n");
	}
}

int main()
{
	myShell();
	return 0;
}