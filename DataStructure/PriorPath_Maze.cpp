#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cassert>
#include<queue>
using namespace std;


typedef struct NodePos
{
	int x;
	int y;
	NodePos(int row = 0, int col = 0)
		:x(row)
		, y(col){}
}Node;


//因为迷宫用的栈 是我自己的，为了方便验证，我将栈也给出
template<typename T>
class Stack
{
public:
	Stack()
		:_capacity(0)
		, _size(0)
		, _ptr(NULL)
	{}
	~Stack()
	{
		delete[] _ptr;
		_size = 0;
		_capacity = 0;
		_ptr = NULL;
	}
	void Push(const T& data);
	void Pop();
	T Top();
	int Size();
	bool Empty();
private:
	void CheckCapacity()
	{
		if (_size >= _capacity)
		{
			int NewCapacity = _capacity * 2 + 1;
			T* tmp = new T[NewCapacity];
			for (int i = 0; i < _size; i++)
			{
				tmp[i] = _ptr[i];
			}
			delete[] _ptr;
			_ptr = tmp;
			_capacity = NewCapacity;
		}
	}
private:
	T* _ptr;
	int _capacity;
	int _size;
};

template<typename T>
bool Stack<T>::Empty()
{
	if (_size == 0)
		return true;
	else
		return false;
}

template<typename T>
void Stack<T>::Push(const T& data)
{
	CheckCapacity();
	_ptr[_size++] = data;
}

template<typename T>
void Stack<T>::Pop()
{
	assert(_size>0);
	--_size;
}

template<typename T>
T Stack<T>::Top()
{
	return _ptr[_size - 1];
}

template<typename T>
int Stack<T>::Size()
{
	return _size;
}









//下面用到的栈是自己实现的栈
template<typename T>
class Maze
{
	typedef Node Pos;
public:
	Maze()
		:_row(0)
		, _col(0)
		, _start(0, 0)
		, _map(NULL)
		,_book(NULL)
	{}
	~Maze()
	{
		for (int i = 0; i < _row; i++)
		{
			delete[] _map[i];
			delete[] _book[i];
		}
		delete[] _map;
		delete[] _book;
	}
	bool SearchPath();            //查找迷宫路径
	void PrintMap();              //输出迷宫地图
	void PrintPath();             //打印路径的坐标
	void SetMap();                //设置地图
private:
	bool CheckNextAccess(Pos coor);        //判断下一个坐标能否通过
	bool CheckPrevAccess(Pos coor);         //判断前一个坐标能否通过
private:
	int _row;
	int _col;
	T **_map;
	T **_book;
	Stack<Pos> _s;
	Pos _start;
};

template<typename T>
bool Maze<T>::CheckNextAccess(Pos coor)    //判断该坐标能否通过
{
	if (coor.x >= 0 && coor.x < _row
		&&coor.y >= 0 && coor.y < _col
		&&_map[coor.x][coor.y] == 0)           //判断是否越界
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
bool Maze<T>::CheckPrevAccess(Pos coor)    //判断该坐标能否通过
{
	if (coor.x >= 0 && coor.x < _row
		&&coor.y >= 0 && coor.y < _col
		&&(_book[coor.x][coor.y] == (_book[_s.Top().x][_s.Top().y] - 1)))           //判断是否越界
	{
		return true;
	}
	else
	{
		return false;
	}
}





template<typename T>
bool Maze<T>::SearchPath()
{
	queue<Node> q;
	q.push(_start);               //起点入队
	Pos cur = _start;
	int step = 1;
	_book[cur.x][cur.y] = 0;     //将起点标记为0
	while (!q.empty())           //如果队列不空，广度优先查找
	{
		Pos next = q.front();
		cur = next;
		_map[cur.x][cur.y] = 2;                           //将走过的路径标记位2
		step = _book[q.front().x][q.front().y] + 1;       //在辅助数组中标记处当前结点到起点的步数
		if (((cur.x == _row - 1)&&cur.x!=_row-1)
			|| ((cur.y == _col- 1)&&cur.y != _col- 1) 
			|| (cur.x == 0 && _start.x != 0) 
			|| (cur.y == 0 && _start.y != 0))    //如果找到出口则跳出循环,出口与入口不再同一侧
		{
			break;
		}
		//上
		next.x--;
		if (CheckNextAccess(next))  //如果当前坐标能够通过，则加入坐标
		{
			q.push(next);
			_book[next.x][next.y] = step;
		}
		next.x++;

		//下
		next.x++;
		if (CheckNextAccess(next))
		{
			q.push(next);
			_book[next.x][next.y] = step;
		}
		next.x--;

		//左
		next.y--;
		if (CheckNextAccess(next))
		{
			q.push(next);
			_book[next.x][next.y] = step;
		}
		next.y++;

		//右
		next.y++;
		if (CheckNextAccess(next))
		{
			q.push(next);
			_book[next.x][next.y] = step;
		}
		next.y--;
		q.pop();   //如果都不能通，则将这点出队
	}

	if (!q.empty())        //如果队列不空，则将终点压入栈中
	{
		_s.Push(cur);
	}

	while (!_s.Empty())      //倒着将从终点到起点的坐标压入
	{
		Pos next = _s.Top();
		//上
		if (_book[next.x][next.y] == 0)     //如果找到起点
		{
			return true;
		}

		next.x--;
		if (CheckPrevAccess(next))  //如果当前坐标能够通过，则加入坐标
		{
			_s.Push(next);
			continue;
		}
		next.x++;

		//下
		next.x++;
		if (CheckPrevAccess(next))
		{
			_s.Push(next);
			continue;
		}
		next.x--;

		//左
		next.y--;
		if (CheckPrevAccess(next))
		{
			_s.Push(next);
			continue;
		}
		next.y++;

		//右
		next.y++;
		if (CheckPrevAccess(next))
		{
			_s.Push(next);
			continue;
		}
		next.y--;
	}
	return false;
}




template<typename T>
void Maze<T>::SetMap()
{
	char c;
	FILE *fp = fopen("MazeMap.txt", "r");      //打开文件读取地图
	assert(fp);
	//读取行
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_row = _row * 10 + (c - '0');
	}
	//读取迷宫列
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_col = _col * 10 + (c - '0');
	}
	//读取迷宫入口横坐标
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_start.x = _start.x * 10 + (c - '0');
	}
	//读取迷宫入口纵坐标
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_start.y = _start.y * 10 + (c - '0');
	}
	//开辟迷宫数组
	_map = new T*[_row];
	for (int i = 0; i < _row; i++)
	{
		_map[i] = new T[_col];
	}

	//开辟辅助数组
	_book = new T*[_row];
	for (int i = 0; i < _row; i++)
	{
		_book[i] = new T[_col];
	}
	//初始化辅助数组
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			_book[i][j] = -1;
		}
	}

	//读取迷宫地图
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col;)
		{
			c = getc(fp);
			if (c == '1' || c == '0')
			{
				_map[i][j] = c - '0';
				j++;
			}
		}
	}
	fclose(fp);     //关闭文件
}


template<typename T>
void Maze<T>::PrintMap()       //打印迷宫地图，但是必须先设置迷宫地图
{
	cout << "迷宫地图中所走过的路径" << endl;
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			cout << _map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;                  //打印辅助数组
	cout << "辅助数组中所有入队的坐标" << endl;
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			printf("%2d ",_book[i][j]);
		}
		cout << endl;
	}
}

template<typename T>
void Maze<T>::PrintPath()          //打印迷宫路径
{
	while (!_s.Empty())
	{
		cout << "(" << _s.Top().x << "," << _s.Top().y << ")" << endl;
		_s.Pop();
	}
}


void test()
{
	Maze<int> m;
	m.SetMap();
	cout << (m.SearchPath() != 0 ? "YES":"NO")<< endl;
	m.PrintMap();
	m.PrintPath();
}
int main()
{
	test();
	system("pause");
	return 0;
}