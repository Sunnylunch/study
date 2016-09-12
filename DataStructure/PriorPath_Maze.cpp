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
	bool SearchPath();            //�����Թ�·��
	void PrintMap();              //����Թ���ͼ
	void PrintPath();             //��ӡ·��������
	void SetMap();                //���õ�ͼ
private:
	bool CheckNextAccess(Pos coor);        //�ж���һ�������ܷ�ͨ��
	bool CheckPrevAccess(Pos coor);         //�ж�ǰһ�������ܷ�ͨ��
private:
	int _row;
	int _col;
	T **_map;
	T **_book;
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
bool Maze<T>::CheckPrevAccess(Pos coor)    //�жϸ������ܷ�ͨ��
{
	if (coor.x >= 0 && coor.x < _row
		&&coor.y >= 0 && coor.y < _col
		&&(_book[coor.x][coor.y] == (_book[_s.Top().x][_s.Top().y] - 1)))           //�ж��Ƿ�Խ��
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
	q.push(_start);               //������
	Pos cur = _start;
	int step = 1;
	_book[cur.x][cur.y] = 0;     //�������Ϊ0
	while (!q.empty())           //������в��գ�������Ȳ���
	{
		Pos next = q.front();
		cur = next;
		_map[cur.x][cur.y] = 2;                           //���߹���·�����λ2
		step = _book[q.front().x][q.front().y] + 1;       //�ڸ��������б�Ǵ���ǰ��㵽���Ĳ���
		if (((cur.x == _row - 1)&&cur.x!=_row-1)
			|| ((cur.y == _col- 1)&&cur.y != _col- 1) 
			|| (cur.x == 0 && _start.x != 0) 
			|| (cur.y == 0 && _start.y != 0))    //����ҵ�����������ѭ��,��������ڲ���ͬһ��
		{
			break;
		}
		//��
		next.x--;
		if (CheckNextAccess(next))  //�����ǰ�����ܹ�ͨ�������������
		{
			q.push(next);
			_book[next.x][next.y] = step;
		}
		next.x++;

		//��
		next.x++;
		if (CheckNextAccess(next))
		{
			q.push(next);
			_book[next.x][next.y] = step;
		}
		next.x--;

		//��
		next.y--;
		if (CheckNextAccess(next))
		{
			q.push(next);
			_book[next.x][next.y] = step;
		}
		next.y++;

		//��
		next.y++;
		if (CheckNextAccess(next))
		{
			q.push(next);
			_book[next.x][next.y] = step;
		}
		next.y--;
		q.pop();   //���������ͨ����������
	}

	if (!q.empty())        //������в��գ����յ�ѹ��ջ��
	{
		_s.Push(cur);
	}

	while (!_s.Empty())      //���Ž����յ㵽��������ѹ��
	{
		Pos next = _s.Top();
		//��
		if (_book[next.x][next.y] == 0)     //����ҵ����
		{
			return true;
		}

		next.x--;
		if (CheckPrevAccess(next))  //�����ǰ�����ܹ�ͨ�������������
		{
			_s.Push(next);
			continue;
		}
		next.x++;

		//��
		next.x++;
		if (CheckPrevAccess(next))
		{
			_s.Push(next);
			continue;
		}
		next.x--;

		//��
		next.y--;
		if (CheckPrevAccess(next))
		{
			_s.Push(next);
			continue;
		}
		next.y++;

		//��
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
	FILE *fp = fopen("MazeMap.txt", "r");      //���ļ���ȡ��ͼ
	assert(fp);
	//��ȡ��
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_row = _row * 10 + (c - '0');
	}
	//��ȡ�Թ���
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_col = _col * 10 + (c - '0');
	}
	//��ȡ�Թ���ں�����
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_start.x = _start.x * 10 + (c - '0');
	}
	//��ȡ�Թ����������
	while ((c = getc(fp)) != ' '&&c != '\n')
	{
		_start.y = _start.y * 10 + (c - '0');
	}
	//�����Թ�����
	_map = new T*[_row];
	for (int i = 0; i < _row; i++)
	{
		_map[i] = new T[_col];
	}

	//���ٸ�������
	_book = new T*[_row];
	for (int i = 0; i < _row; i++)
	{
		_book[i] = new T[_col];
	}
	//��ʼ����������
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			_book[i][j] = -1;
		}
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
void Maze<T>::PrintMap()       //��ӡ�Թ���ͼ�����Ǳ����������Թ���ͼ
{
	cout << "�Թ���ͼ�����߹���·��" << endl;
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			cout << _map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;                  //��ӡ��������
	cout << "����������������ӵ�����" << endl;
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
void Maze<T>::PrintPath()          //��ӡ�Թ�·��
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