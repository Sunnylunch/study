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


//��Ϊ�Թ��õ�ջ �����Լ��ģ�Ϊ�˷�����֤���ҽ�ջҲ����
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

//�����õ���ջ���Լ�ʵ�ֵ�ջ
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
	bool SearchPath();            //�����Թ�·��
	void PrintMap();              //����Թ���ͼ
	void PrintPath();             //��ӡ·��������
	void SetMap();                //���õ�ͼ
private:
	bool CheckNextAccess(Pos coor);        //�жϸ������ܷ�ͨ��
private:
	int _row;
	int _col;
	T **_map;
	Stack<Pos> _s;
	Pos _start;
};

template<typename T>
bool Maze<T>::CheckNextAccess(Pos coor)    //�жϸ������ܷ�ͨ��
{
	if (coor.x >= 0 && coor.x < _row
		&&coor.y >= 0 && coor.y < _col
		&&_map[coor.x][coor.y] == 0)           //�ж��Ƿ�Խ��
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
	FILE *fp = fopen("MazeMap.txt", "r");      //���ļ���ȡ��ͼ
	assert(fp);
	//��ȡ��
	while ((c = getc(fp))!= ' '&&c != '\n')
	{
		_row=_row*10+(c-'0');
	}
	//��ȡ�Թ���
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_col=_col*10+(c - '0');
	}
	//��ȡ�Թ���ں�����
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_start.x = _start.x*10+(c - '0');
	}
	//��ȡ�Թ����������
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_start.y = _start.y*10+(c - '0');
	}
	//�����Թ�����
	_map = new T*[_row];
	for (int i = 0; i < _row; i++)
	{
		_map[i] = new T[_col];
	}

	//��ȡ�Թ���ͼ
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
	fclose(fp);     //�ر��ļ�
}



template<typename T>
bool Maze<T>::SearchPath()
{
	Pos cur = _start;
	_s.Push(_start);                   //���������ѹ��ջ
	_map[_start.x][_start.y] = 2;      //�߹���·������Ϊ2
	while (!_s.Empty())                //���ջ�Կգ���˵���ֻص���ڣ����Թ��޽�
	{
		Pos next=_s.Top();
		cur = next;
		_map[cur.x][cur.y] = 2;           //����������Ϊ���߹�
		if (next.x==_row-1||next.y==_col-1)     //�ж��Ƿ��ߵ�����
		{
			return true;
		}
		//��
		next.x--;
		if (CheckNextAccess(next))  //�����ǰ�����ܹ�ͨ�������������
		{
			_s.Push(next);
			continue;
		}
		next.x++;

		//��
		next.x++;
		if (CheckNextAccess(next))
		{
			_s.Push(next);
			continue;
		}
		next.x--;

		//��
		next.y--;
		if (CheckNextAccess(next))
		{
			_s.Push(next);
			continue;
		}
		next.y++;

		//��
		next.y++;
		if (CheckNextAccess(next))
		{
			_s.Push(next);
			continue;
		}

		_s.Pop();                     //�����ǰ���겻ͨ������ջ
		_map[next.x][next.y]= 3;      //�������������Ϊ��ͨ
	}
	return false;
}

template<typename T>
void Maze<T>::PrintMap()       //��ӡ�Թ���ͼ�����Ǳ����������Թ���ͼ
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
void Maze<T>::PrintPath()          //��ӡ�Թ�·��
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

