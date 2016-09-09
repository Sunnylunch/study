#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cassert>

using namespace std;


typedef struct NodePos
{
	int x;
	int y;
	NodePos(int row=0, int col=0)
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
		, _start(0,0)
		, _map(NULL)
	{}
	~Maze()
	{
		for (int i = 0; i < _row; i++)
		{
			delete[] _map[i];
		}
		delete[] _map;
	}
	bool SearchPath();            //查找迷宫路径
	void PrintMap();              //输出迷宫地图
	void PrintPath();             //打印路径的坐标
	void SetMap();                //设置地图
private:
	bool CheckNextAccess(Pos coor);        //判断该坐标能否通过
private:
	int _row;
	int _col;
	T **_map;
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
void Maze<T>::SetMap()
{
	char c;
	FILE *fp = fopen("MazeMap.txt", "r");      //打开文件读取地图
	assert(fp);
	//读取行
	while ((c = getc(fp))!= ' '&&c != '\n')
	{
		_row=_row*10+(c-'0');
	}
	//读取迷宫列
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_col=_col*10+(c - '0');
	}
	//读取迷宫入口横坐标
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_start.x = _start.x*10+(c - '0');
	}
	//读取迷宫入口纵坐标
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_start.y = _start.y*10+(c - '0');
	}
	//开辟迷宫数组
	_map = new T*[_row];
	for (int i = 0; i < _row; i++)
	{
		_map[i] = new T[_col];
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
bool Maze<T>::SearchPath()
{
	Pos cur = _start;
	_s.Push(_start);                   //将起点坐标压入栈
	_map[_start.x][_start.y] = 2;      //走过的路径设置为2
	while (!_s.Empty())                //如果栈以空，则说明又回到入口，则迷宫无解
	{
		Pos next=_s.Top();
		cur = next;
		_map[cur.x][cur.y] = 2;           //将坐标设置为已走过
		if (next.x==_row-1||next.y==_col-1)     //判断是否走到出口
		{
			return true;
		}
		//上
		next.x--;
		if (CheckNextAccess(next))  //如果当前坐标能够通过，则加入坐标
		{
			_s.Push(next);
			continue;
		}
		next.x++;

		//下
		next.x++;
		if (CheckNextAccess(next))
		{
			_s.Push(next);
			continue;
		}
		next.x--;

		//左
		next.y--;
		if (CheckNextAccess(next))
		{
			_s.Push(next);
			continue;
		}
		next.y++;

		//右
		next.y++;
		if (CheckNextAccess(next))
		{
			_s.Push(next);
			continue;
		}

		_s.Pop();                     //如果当前坐标不通，则退栈
		_map[next.x][next.y]= 3;      //并将这个坐标标记为不通
	}
	return false;
}

template<typename T>
void Maze<T>::PrintMap()       //打印迷宫地图，但是必须先设置迷宫地图
{
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			cout << _map[i][j] <<" ";
		}
		cout << endl;
	}
}

template<typename T>
void Maze<T>::PrintPath()          //打印迷宫路径
{
	Stack<Pos> coor;
	while (!_s.Empty())
	{
		coor.Push(_s.Top());
		_s.Pop();
	}
	while (!coor.Empty())
	{
		cout << "(" << coor.Top().x << "," << coor.Top().y << ")" << endl;
		coor.Pop();
	}
}

