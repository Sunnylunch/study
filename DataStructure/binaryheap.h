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
		:_Heap(v.size()+1)                               //为了便于计算，多开辟一个空间
		, _Size(v.size())
	{
		for (int i = 1; i <=_Size; i++)                //_Heap[0]不存放
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
		for (; i/2>0; i /= 2)       //i这点的结点要有父亲节点
		{
			parent = i / 2;           //父亲结点的位置
			if (_Heap[parent] < data)  //如果父亲结点比插入的值小，则有序
			{
				break;
			}
			else                        //如果父亲结点比插入值大
			{
				_Heap[i] = _Heap[parent];
			}
		}
		_Heap[i] = data;
	}

	void DeleteMin(Node& data=Node())          //删除最小元素，可以通过参数返回最小值
	{
		assert(_Size>0);
		data = findMin();
		_Heap[1] = _Heap[_Size--];
		int i = 0;
		percolate(1);                             //从根结点处开始下滑调整顺序
	}

	void MakeHeap()                            //置空堆
	{
		BinaryHeap<T> tmp;
		swap(tmp._Heap ,_Heap);
		_Size = 0;
	}

	bool IsEmpty()const                        //判断堆是不是为空
	{
		return _Size == 0;
	}

	const Node& findMin()const                 //查找堆中的最小元素
	{
		assert(_Size>0);
		return _Heap[1];
	}
protected:

	void buildHeap()                            //恢复堆的顺序
	{
		for (int i =_Size; i > 0; i--)
		{
			percolate(i);
		}
	}

	void percolate(int hole)                           //从hole开始下滑调整
	{
		int child=0;
		Node tmp = _Heap[hole];
		for (;hole*2<=_Size;hole=child)                 //如果有左孩子则下滑调整
		{
			child = hole * 2;
			if (child !=_Size&&_Heap[child]> _Heap[child + 1])   //找出左右孩子中值最小的
				child++;
			if (tmp < _Heap[child])                 //如果tmp小于孩子的值，则调整结束
			{
				break;
			}
			else                                    //如果tmp大于等于孩子的值，则继续调整
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

