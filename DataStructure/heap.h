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



//ͨ���º��������Խ���С��Ҳ���Խ�����
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

		//����
		for (int i =(size-2)/2;i>=0; --i)     //�����һ����Ҷ��㿪ʼ����
		{
			AdjustDown(i,size);
		}
	}

	void Push(const T& x)
	{
		//���뵽β�����ٴ����һ��Ԫ�ؿ�ʼ���ϵ���
		_a.push_back(x);
		AdjustUp(_a.size()-1);
	}

	void Pop()
	{
		//���Ѷ������һ��Ԫ�ؽ������ٴӶѶ��»�����
		assert(!_a.empty());
		swap(_a[0],_a[_a.size()-1]);
		_a.pop_back();
		if (_a.size()>1)         //������е�Ԫ�ش���һ�����ٽ��е���
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
	void AdjustDown(int root,int size)      //���µ����㷨
	{
		assert(!_a.empty());
		int parent=root;
		int child = parent * 2 + 1;
		while (child<size)
		{
			
			if ((child + 1) < size
				&&Compare()(_a[child + 1], _a[child]))  //�����Һ����������±�
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

	void AdjustUp(int child)    //���ϵ����㷨
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