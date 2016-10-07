#pragma once
#include<cassert>
#include<vector>

template<typename T>
struct HeapNode
{
	T _data;
	size_t _key;
	HeapNode()
	{}
	HeapNode(const T& data,size_t key)
		:_data(data)
		, _key(key)
	{}
	friend ostream& operator<<(ostream& os,const HeapNode<T>& heap)
	{
		os << heap._data;
		return os;
	}
	friend bool operator>(const HeapNode<T>& h1,const HeapNode<T>& h2)
	{
		if (h1._key  > h2._key)
			return true;
		else
			return false;
	}
	friend bool operator<(const HeapNode<T>& h1, const HeapNode<T>& h2)
	{
		if (h1._key < h2._key)
			return true;
		else
			return false;
	}
};


template<typename T>
class BinaryHeap
{
	typedef HeapNode<T> Node;
public:
	BinaryHeap()
		:_Heap(0)
		, _Size(0)
	{}
	BinaryHeap(const vector<Node> &v)
		:_Heap(v.size()+1)                               //Ϊ�˱��ڼ��㣬�࿪��һ���ռ�
		, _Size(v.size())
	{
		for (int i = 1; i <=_Size; i++)                //_Heap[0]�����
		{
			_Heap[i] = v[i-1];
		}
		buildHeap();
	}

	void Insert(const Node& data)
	{
		_Heap.push_back(data);
		_Size++;
		int i = _Size;
		int parent= 0;
		for (; i/2>0; i /= 2)       //i���Ľ��Ҫ�и��׽ڵ�
		{
			parent = i / 2;           //���׽���λ��
			if (_Heap[parent] < data)  //������׽��Ȳ����ֵС��������
			{
				break;
			}
			else                        //������׽��Ȳ���ֵ��
			{
				_Heap[i] = _Heap[parent];
			}
		}
		_Heap[i] = data;
	}

	void DeleteMin(Node& data=Node())          //ɾ����СԪ�أ�����ͨ������������Сֵ
	{
		assert(_Size>0);
		data = findMin();
		_Heap[1] = _Heap[_Size--];
		int i = 0;
		percolate(1);                             //�Ӹ���㴦��ʼ�»�����˳��
	}

	void MakeHeap()                            //�ÿն�
	{
		BinaryHeap<T> tmp;
		swap(tmp._Heap ,_Heap);
		_Size = 0;
	}

	bool IsEmpty()const                        //�ж϶��ǲ���Ϊ��
	{
		return _Size == 0;
	}

	const Node& findMin()const                 //���Ҷ��е���СԪ��
	{
		assert(_Size>0);
		return _Heap[1];
	}
protected:

	void buildHeap()                            //�ָ��ѵ�˳��
	{
		for (int i =_Size; i > 0; i--)
		{
			percolate(i);
		}
	}

	void percolate(int hole)                           //��hole��ʼ�»�����
	{
		int child=0;
		Node tmp = _Heap[hole];
		for (;hole*2<=_Size;hole=child)                 //������������»�����
		{
			child = hole * 2;
			if (child !=_Size&&_Heap[child]> _Heap[child + 1])   //�ҳ����Һ�����ֵ��С��
				child++;
			if (tmp < _Heap[child])                 //���tmpС�ں��ӵ�ֵ�����������
			{
				break;
			}
			else                                    //���tmp���ڵ��ں��ӵ�ֵ�����������
			{
				_Heap[hole] = _Heap[child];
			}
		}
		_Heap[child] = tmp;
	}

protected:
	vector<Node> _Heap;
	int _Size;
};

