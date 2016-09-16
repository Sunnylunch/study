#include<iostream>
#include<vector>
#include<cstdio>
#include<time.h>
#include<conio.h>
#include<Windows.h>
using namespace std;

enum
{
	U,
	D,
	L,
	R
};

typedef struct Coor
{
	int _x = 0;
	int _y = 0;
	Coor(int x = 0, int y = 0)
		:_x(x)
		, _y(y){}
}Coor;



void move(int x, int y)
{
	COORD cd;
	cd.X = x;
	cd.Y = y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, cd);
}


class Snake
{
public:
	Snake(int row, int col)
		:_row(row)
		, _col(col)
	{
		_map = new char*[_row];
		for (int i = 0; i < _row; i++)
		{
			_map[i] = new char[_col];
		}
	}

	~Snake()
	{
		for (int i = 0; i < _row; i++)
		{
			delete[] _map[i];
		}
		delete[] _map;
	}
private:
	void SetMap()          //初始化地图
	{
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _col; j++)
			{
				_map[i][j] = ' ';
			}
		}

		for (int i = 0; i < _row; i++)
		{
			_map[i][0] = '#';
			_map[i][_col - 1] = '#';
		}

		for (int i = 0; i < _col; i++)
		{
			_map[0][i] = '#';
			_map[_row - 1][i] = '#';
		}
	}
	bool CheckEatFood()                       //查看是否吃到食物
	{
		if (_array[0]._x == food._x &&_array[0]._y == food._y)
		{
			return true;                      //吃到食物
		}
		else
		{
			return false;
		}
	}


	bool CheckAccess()                   //判断蛇是否能够通过
	{
		if ((_array[0]._x > 0) && (_array[0]._x<(_col - 1))
			&& (_array[0]._y>0) && (_array[0]._y <(_row - 1)))
		{
			for (int i = 1; i < (int)_array.size(); i++)
			{
				if ((_array[0]._x == _array[i]._x) && (_array[0]._y == _array[i]._y))
				{
					return false;
				}
			}
			return true;
		}
		else
			return false;
	}

	void SetFood()               //随机产生食物
	{
		int x = 0;
		int y = 0;
		while ((_map[x][y] != ' '))
		{
			srand((unsigned)time(NULL));
			x = rand() % (_row - 3) + 1;
			y = rand() % (_col - 3) + 1;
		}
		move(y, x);
		printf("%c", 3);
		food._x = y;                  //记录食物的位置
		food._y = x;
	}



	void PrintMap()                                 //打印地图
	{
		SetMap();                                    //设置地图
		for (int i = 0; i < _row; i++)
		{
			for (int j = 0; j < _col; j++)
			{
				printf("%c", _map[i][j]);
			}
			cout << endl;
		}

		int x = 1;
		int y = 1;
		_array.push_back(Coor(x, y));          //将蛇头放到数组中	
		move(y, x);
		cout << '0';                           //打印蛇头
		status = R;                            //初始化蛇头的方向
	}

        void DrawSnake(int status)                        //绘制蛇的图形
	{
		//先擦除蛇
		for (int i = 0; i< (int)_array.size(); i++)
		{
			move(_array[i]._x, _array[i]._y);
			cout << ' ';
		}

		//获得蛇的下一个位置的坐标
		switch (status)
		{
		case U:                        //上
			for (int i = (int)_array.size() - 1; i>0; i--)
			{
				_array[i]._x = _array[i - 1]._x;
				_array[i]._y = _array[i - 1]._y;
			}
			_array[0]._y -= 1;
			break;
		case D:                        //下
			for (int i = (int)_array.size() - 1; i>0; i--)
			{
				_array[i]._x = _array[i - 1]._x;
				_array[i]._y = _array[i - 1]._y;
			}
			_array[0]._y += 1;
			break;
		case L:                        //左
			for (int i = (int)_array.size() - 1; i>0; i--)
			{
				_array[i]._x = _array[i - 1]._x;
				_array[i]._y = _array[i - 1]._y;
			}
			_array[0]._x -= 1;
			break;
		case R:                        //右
			for (int i = (int)_array.size() - 1; i>0; i--)
			{
				_array[i]._x = _array[i - 1]._x;
				_array[i]._y = _array[i - 1]._y;
			}
			_array[0]._x += 1;
			break;
		}
		if (!CheckAccess())
		{
			exit(1);
		}

		//重新绘制出蛇的图像
		for (int i = 0; i<(int)_array.size(); i++)
		{
			move(_array[i]._x, _array[i]._y);
			cout << '0';
		}
	}

public:
	void PlayGame()
	{
		PrintMap();                         //打印出地图
		int i = 6;
		SetFood();
		while (1)
		{
			if (GetAsyncKeyState(VK_UP) && status != 'U')
			{
				status = U;
			}
			else if (GetAsyncKeyState(VK_DOWN) && status != 'D')
			{
				status = D;
			}
			else if (GetAsyncKeyState(VK_LEFT) && status != 'L')
			{
				status = L;
			}
			else if (GetAsyncKeyState(VK_RIGHT) && status != 'R')
			{
				status = R;
			}
			if (_array[0]._x == food._x&&_array[0]._y == food._y)
			{
				Coor pos = _array.back();
				_array.push_back(pos);
				SetFood();
			}
			DrawSnake(status);                    //画出图像
			Sleep(300);
		}
	}


private:
	vector<Coor> _array;
	char** _map;
	int _row;
	int _col;
	Coor food;
	int status;
};

void test()
{
	Snake s(20, 40);
	s.PlayGame();
}

int main()
{
	test();
	system("pause");
	return 0;
}







