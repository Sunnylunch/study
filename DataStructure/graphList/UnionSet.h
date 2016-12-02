#pragma once
#include<iostream>
using namespace std;
//���鼯
class UnionSet
{
public:
	UnionSet(int n)
		:_size(n + 1)
	{
		_a = new int[n + 1];
		memset(_a, -1, sizeof(int)*(n + 1));   //memsetֻ����0��-1��ʱ��1���ֽ���4���ֽ����õ��Ľ������ͬ��
	}

	~UnionSet()
	{
		delete[] _a;
	}

	void Merge(int x1, int x2)
	{
		int root1 = GetRoot(x1);
		int root2 = GetRoot(x2);

		if (root1 != root2)           //���������Ԫ�ز���һ��������
		{
			_a[root1] += _a[root2];    //��root2��ֵ�ӵ����ڵ㴦
			_a[root2] = root1;         //��root2����Ÿ��ڵ���±�
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
