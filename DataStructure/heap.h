#pragma once
#include<cassert>
#include<vector>
using namespace std;

template<typename T>
struct Less
{
	bool operator()(const T& l,const T& r)
	{
		return l < r;
	}
};

template<typename T>
struct Great
{
	bool operator()(const T& l, const T& r)
	{
		return l>r;
	}
};



//通过仿函数，可以建最小堆也可以建最大堆
template<typename T,class Compare=Less<T>>
class Heap
{
public:
	Heap()
	{}
	Heap(T *a, int size)
	{
		_a.reserve(size);
		for (int i = 0; i < size; i++)
		{
			_a.push_back(a[i]);
		}

		//建堆
		for (int i =(size-2)/2;i>=0; --i)     //从最后一个非叶结点开始调整
		{
			AdjustDown(i,size);
		}
	}

	void Push(const T& x)
	{
		//插入到尾部，再从最后一个元素开始向上调整
		_a.push_back(x);
		AdjustUp(_a.size()-1);
	}

	void Pop()
	{
		//将堆顶与最后一个元素交换，再从堆顶下滑调整
		assert(!_a.empty());
		swap(_a[0],_a[_a.size()-1]);
		_a.pop_back();
		if (_a.size()>1)         //如果堆中的元素大于一个，再进行调整
		{
			AdjustDown(0, _a.size());
		}		
	}

	bool Empty()
	{
		return _a.empty();
	}

	const T& Top()
	{
		assert(!_a.empty());
		return _a[0];
	}
protected:
	void AdjustDown(int root,int size)      //向下调整算法
	{
		assert(!_a.empty());
		int parent=root;
		int child = parent * 2 + 1;
		while (child<size)
		{
			
			if ((child + 1) < size
				&&Compare()(_a[child + 1], _a[child]))  //找左右孩子中最大的下标
				child++;
			if (Compare()(_a[child],_a[parent]))
			{
				swap(_a[parent],_a[child]);
				parent=child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

	void AdjustUp(int child)    //向上调整算法
	{
		assert(!_a.empty());
		while (child>0)
		{
			int parent = (child - 1) / 2;
			if (Compare()(_a[child],_a[parent]))
			{
				swap(_a[parent], _a[child]);
				child = parent;
			}
			else
			{
				break;
			}
		}
	}
private:
	vector<T> _a;
};