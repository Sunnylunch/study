#pragma once
#include<vector>
#include<cassert>
using namespace std;


template<typename T>
struct SmallNum                  //求最小的数,建最大堆
{
	bool operator()(const T& l,const T& r)
	{
		return l < r;
	}
};

template<typename T>
struct GreatNum                 //求最大的数，建最小堆
{
	bool operator()(const T& l,const T& r)
	{
		return l>r;
	}
};



template<typename T,class Compare=SmallNum<T>>      //默认求最小的k个数
class HeapSearch
{
public:
	HeapSearch()
	{}
	HeapSearch(T* a, int size,int k)
	{
		assert(size>=k);
		assert(k>0);
		//建一个k个数的堆，如果求最小的k个数则建最大堆，反之建最小堆
		_a.reserve(k);
		for (int i = 0; i < k; ++i)
		{
			_a.push_back(a[i]);
		}

		for (int i = (k - 2) / 2; i >= 0; --i)
		{
			//向下调整算法
			AdjustDown(i,k);
		}
		
		FindKNum(a,size,k);
	}

	void Display()
	{
		for (size_t i = 0; i < _a.size(); i++)
		{
			cout << _a[i] << " ";
		}
		cout << endl;
	}

protected:
	void AdjustDown(int root,int k)
	{
		assert(!_a.empty());
		int parent= root;    //最后一个非叶子结点
		int child = parent * 2 + 1;      //求左孩子结点的下标
		while (child<k)
		{
			if ((child + 1) < k&&Compare()(_a[child],_a[child+1]))
				child++;
			if (Compare()(_a[parent], _a[child]))
			{
				swap(_a[parent],_a[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

	void  FindKNum(T*a ,int size,int k)
	{
		for (int i = k; i < size;i++)
		{
			if (Compare()(a[i], _a[0]))
			{
				_a[0] = a[i];
				AdjustDown(0,k);
			}
		}
	}
private:
	vector<T> _a;
};