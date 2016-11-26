#pragma once
#include<iostream>

//���鼯
class UnionSet
{
public:
	UnionSet(int n)
		:_size(n+1)
	{
		_a = new int[n+1];
		memset(_a,-1,sizeof(int)*(n+1));   //memsetֻ����0��-1��ʱ��1���ֽ���4���ֽ����õ��Ľ������ͬ��
	}

	~UnionSet()
	{
		delete[] _a;
	}

	void Merge(int x1,int x2)
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
		return count - 1;
	}
protected:
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

void TestUnionSet()
{
	const int n = 5;
	const int m = 6;
	int r[m][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 }, { 1, 3 }, { 5, 4 }, {3,5} };
	UnionSet set(n);

	for (int i = 0; i < m;i++)
	{
		set.Merge(r[i][0],r[i][1]);
	}
	cout << set.CountSet() << endl;
}
