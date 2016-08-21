#include<iostream>
#include<string.h>
using namespace std;
typedef int DataType;

class Seqlist
{
	friend ostream& operator<<(ostream&,Seqlist&);
public:
	Seqlist()
		:_size(0)
		, _capacity(0)
		, _data(NULL)
	{}
	Seqlist(const Seqlist& seq)
	{
		_data = new DataType[seq._capacity];
		memcpy(_data,seq._data,sizeof(DataType)*(size_t)seq._size);
		_size = seq._size;
		_capacity = seq._capacity;
	}

	Seqlist& operator=(Seqlist seq)
	{
		swap(_data,seq._data);
		_size = seq._size;
		_capacity = seq._capacity;
		return *this;
	}

	~Seqlist()
	{
		if (_data != NULL)
		{
			delete[] _data;
			_data = NULL;
			_size = 0;
			_capacity = 0;
		}
	}
public:
	void PushBack(const DataType& data)
	{
		CheckCapacity();
		_data[_size++] = data;
	}
	void PushFront(const DataType& data)
	{
		CheckCapacity();
		memmove(_data+1,_data,sizeof(DataType)*(size_t)_size);   //将数据整体向后偏移一个整形
		_size++;
		_data[0] = data;
	}
	void PopBack()
	{
		if (_size == 0)
		{
			cout << "没有数据" << endl;
		}
		else
		{
			_size--;
		}
	}
	void PopFront()
	{
		if (_size == 0)
		{
			cout << "没有数据" << endl;
		}
		else
		{
			--_size;
			memmove(_data, _data + 1, sizeof(DataType)*(size_t)_size);  //将数据整体向后偏移一个整形
		}
	}
	void Insert(int index, const DataType& data)
	{
		if (index<0 || index>(_size - 1))
		{
			cout << "位置异常" << endl;
			return;
		}
		CheckCapacity();
		_size++;
		memmove(_data+index+1,_data+index,sizeof(DataType)*(size_t)(_size-index-1));  //从index位置开始数据整体向后偏移一个元素大小
		_data[index] = data;
	}

	void Clear()
	{
		_size = 0;
	}

	void Erase(int index)
	{
		if (index<0 || index>(_size - 1))
		{
			cout << "位置异常" << endl;
			return;
		}
		memmove(_data+index,_data+index+1,sizeof(DataType)*(size_t)(_size-index-1));
		_size--;
	}
	int Find(DataType data)
	{
		int i = 0;
		while (i < _size&&_data[i]!=data)
		{
			i++;
		}
		if (i == _size)
		{
			return -1;               //如果没找到，则返回-1
		}
		else
		{
			return i;
		}
	}
	void Remove(const DataType& data)
	{
		int i = Find(data);
		if (i == -1)
		{
			return;
		}
		else
		{
			Erase(i);
		}
	}
	void RemoveAll(const DataType& data)
	{
		while (Find(data) != -1)
		{
			Remove(data);
		}
	}
	void BubbleSort()
	{
		int i = 0;
		int j = 0;
		for (i = 0; i < _size-1;i++)
		{
			int flag =1;
			for (j = 0; j<_size - i-1;j++)
			{
				if (_data[j]>_data[j + 1])
				{
					DataType tmp = _data[j];
					_data[j] = _data[j + 1];
					_data[j + 1] = tmp;
					flag = 0;
				}
			}
			if (flag)        //如果flag为真，则排序结束
			{
				return;
			}
		}
	}

	void InsertSort()
	{
		int i = 0;
		int j = 0;
		for (i = 1; i < _size; i++)
		{
			DataType tmp = _data[i];
			//找到一个合适的位置
			for (j = i; j>0&&_data[j-1]>tmp; j--)
			{
				_data[j] = _data[j-1];
			}
			_data[j] = tmp;
		}
	}

	void SelectSort()
	{
		int i = 0;
		int j = 0;
		for (i = 0; i < _size-1; i++)
		{
			int Min= i;                    //Min记录最小元素的下标
			for (j = i+1; j < _size; j++)
			{
				if (_data[j] < _data[Min])
				{
					Min = j;
				}
			}
			if (Min!= i)
			{
				DataType tmp = _data[Min];
				_data[Min] = _data[i];
				_data[i] = tmp;
			}
		}
	}
private:
	void CheckCapacity()            //查看容量是否足够
	{
		if (_size == _capacity)
		{
			DataType *tmp = new DataType[_capacity += 10];
			memmove(tmp,_data,sizeof(DataType)*(size_t)_size);
			delete[] _data;
			_data = tmp;
		}
	}
	DataType  *_data;
	int _size;
	int _capacity;
};

ostream& operator<<(ostream& os, Seqlist& seq)
{
	for (int i =0; i < seq._size; i++)
	{
		os << seq._data[i] << " ";
	}
	return os;
}

//void test()
//{
//	Seqlist seq;
//	seq.PushBack(1);
//	/*seq.PushBack(2);
//	seq.PushBack(3);
//	seq.PushBack(4);
//	seq.PushBack(5);
//	seq.PushBack(6);
//	seq.PushFront(0);*/
//	//cout << seq << endl;
//	//seq.PopBack();
//	//cout << seq << endl;
//	seq.PopFront();
//	cout << seq << endl;
//}

//void test2()
//{
//	Seqlist seq;
//	seq.PushBack(1);
//	seq.PushBack(2);
//	seq.PushBack(3);
//	seq.PushBack(4);
//	seq.PushBack(5);
//	cout << seq << endl;
//	seq.Insert(5,6);
//	cout << seq << endl;
//	seq.Insert(-1,6);
//	cout << seq << endl;
//}
//
//void test3()
//{
//	Seqlist seq;
//	seq.PushBack(1);
//	seq.PushBack(2);
//	seq.PushBack(3);
//	seq.PushBack(4);
//	seq.PushBack(5);
//	/*cout << seq << endl;
//	seq.Clear();
//	cout << seq << endl;*/
//	cout << seq << endl;
//	//seq.Erase(2);
//	//seq.Erase(0);
//	seq.Erase(4);
//	cout << seq << endl;
//}


void test4()
{
	Seqlist seq;
	seq.PushBack(1);
	seq.PushBack(4);
	seq.PushBack(3);
	seq.PushBack(5);
	seq.PushBack(2);
	seq.PushFront(0);
	cout << seq<< endl;
	//seq.BubbleSort();
	//seq.InsertSort();
	seq.SelectSort();
	cout << seq <<endl;
}


int main()
{
	test4();
	system("pause");
	return 0;
}