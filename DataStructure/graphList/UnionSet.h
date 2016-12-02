#pragma once
#include<iostream>
using namespace std;
//并查集
class UnionSet
{
public:
	UnionSet(int n)
		:_size(n + 1)
	{
		_a = new int[n + 1];
		memset(_a, -1, sizeof(int)*(n + 1));   //memset只有在0和-1的时候1个字节与4个字节所得到的结果是相同的
	}

	~UnionSet()
	{
		delete[] _a;
	}

	void Merge(int x1, int x2)
	{
		int root1 = GetRoot(x1);
		int root2 = GetRoot(x2);

		if (root1 != root2)           //如果这两个元素不再一个集合中
		{
			_a[root1] += _a[root2];    //把root2的值加到根节点处
			_a[root2] = root1;         //让root2处存放根节点的下标
		}
	}

	int CountSet()
	{
		int count = 0;
		for (size_t i = 0; i < _size; ++i)
		{
			if (_a[i] < 0)
				count++;
		}
		return count;
	}
	int GetRoot(int index)
	{
		int root = index;
		while (_a[root] >= 0)
		{
			root = _a[root];
		}
		return root;
	}
private:
	int *_a;
	size_t _size;
};
