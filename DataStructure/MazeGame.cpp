#include<iostream>
#include<cassert>
#include<conio.h>
#include<Windows.h>
#include<time.h>
using namespace std;


void move(int x, int y)
{
	COORD cd;
	cd.X = x;
	cd.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, cd);
}


//声明一个坐标类型
typedef struct
{
	int x;
	int y;
}Coor;



void InitMap(char **map, int line, int row)
{
	Coor start, end;        //start是起点坐标  end是终点坐标
	start.x = 1;
	start.y = 0;
	end.x = line - 2;
	end.y = row - 1;
	//初始化地图
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < row; j++)
		{
			map[i][j] = ' ';
		}
	}
	//打印边框墙
	for (int i = 0; i < line; i++)
	{
		map[i][0] = '#';
		map[i][row - 1] = '#';
	}
	for (int i = 0; i <row; i++)
	{
		map[0][i] = '#';
		map[line - 1][i] = '#';
	}
	//产生随机障碍物
	int count = (line*row) / 3;
	srand((unsigned)time(NULL));
	while (--count)
	{
		int i = 0;
		int j = 0;
		i = rand() % (line - 3) + 1;
		j = rand() % (row - 3) + 1;
		map[i][j] = '#';
	}
	//保证起点和终点不被占用
	map[start.x][start.y] = ' ';
	map[end.x][end.y] = ' ';

	map[start.x][start.y + 1] = ' ';
	map[start.x][start.y + 2] = ' ';
	map[end.x][end.y - 1] = ' ';
	//打印地图
	move(0, 0);
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j <row; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}


void PlayGame(char **map, int line, int row)
{
	Coor start, end;        //start是起点坐标  end是终点坐标
	start.x = 0;
	start.y = 1;
	end.x = row - 1;
	end.y = line - 2;
	InitMap(map, line, row);             //初始化地图
	//初始化猪脚
	int x = start.x;
	int y = start.y;
	move(x, y);
	cout << 'T';
	//开始玩游戏
	while (1)
	{
		int a1 = _getch();
		if (a1 == 48)
		{
			return;
		}
		int a2 = _getch();
		move(x, y);
		cout << ' ';
		switch (a2)
		{
		case 72:
			y--;
			if (y < 1 || map[y][x] == '#')
			{
				y++;
			}
			break;
		case 80:
			y++;
			if ((y>line - 2) || map[y][x] == '#')
			{
				y--;
			}
			break;
		case 75:
			x--;
			if (x < 1 || map[y][x] == '#')
			{
				x++;
			}
			break;
		case 77:
			x++;
			if (map[y][x] == '#')
			{
				x--;
			}
			break;
		default:
			break;
		}
		if ((end.x == x) && (end.y == y))
		{
			break;
		}
		move(x, y);
		cout << 'T';
	}
	move(row, line);
	cout << "you are Win!!!" << endl;
	Sleep(1000);
}

void menu()
{
	cout << "******************************" << endl;
	cout << "***Welecom to labyrinth maze**" << endl;
	cout << "说明：" << endl;
	cout << "移动：上下左右" << endl;
	cout << "#：墙壁,猪脚无法穿墙" << endl;
	cout << "若迷宫无法通过" << endl;
	cout << "按0重新生成地图" << endl;
	cout << "处于菜单选项时按0退出" << endl;
	Sleep(1000);
	cout << "    Please choose model" << endl << endl;
	cout << "    -->1、classic model" << endl;
	cout << "    -->2、difficulty model" << endl;
}

char** Capacity(int line, int row)
{
	char **map = (char**)malloc(line*sizeof(char*));
	for (int i = 0; i <line; i++)
	{
		map[i] = (char *)malloc(row*sizeof(char));
	}
	return map;
}

void DesMap(char** map, int line, int row)
{
	move(0, 0);
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j <row; j++)
		{
			cout << " ";
		}
		cout << endl;
	}
	free(map);
}

void test()
{
	int line = 0;
	int row = 0;
	char** map = NULL;
	int n = 1;
	while (1)
	{
		menu();
		cin >> n;
		switch (n)
		{
		case 0:
			exit(1);
			break;
		case 1:
			line = 20;
			row = 40;
			map = Capacity(line, row);
			break;
		case 2:
			line = 40;
			row = 60;
			map = Capacity(line, row);
			break;
		default:
			line = 40;
			row = 60;
			map = Capacity(line, row);
			break;
		}
		PlayGame(map, line, row);
		Sleep(1000);
		DesMap(map, line, row);
	}
}
int main()
{
	test();
	system("pause");
	return 0;
}