#pragma once
#include<vector>
#include<cassert>
using namespace std;


template<typename T>
struct SmallNum                  //����С����,������
{
	bool operator()(const T& l,const T& r)
	{
		return l < r;
	}
};

template<typename T>
struct GreatNum                 //��������������С��
{
	bool operator()(const T& l,const T& r)
	{
		return l>r;
	}
};



template<typename T,class Compare=SmallNum<T>>      //Ĭ������С��k����
class HeapSearch
{
public:
	HeapSearch()
	{}
	HeapSearch(T* a, int size,int k)
	{
		assert(size>=k);
		assert(k>0);
		//��һ��k�����Ķѣ��������С��k���������ѣ���֮����С��
		_a.reserve(k);
		for (int i = 0; i < k; ++i)
		{
			_a.push_back(a[i]);
		}

		for (int i = (k - 2) / 2; i >= 0; --i)
		{
			//���µ����㷨
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
		int parent= root;    //���һ����Ҷ�ӽ��
		int child = parent * 2 + 1;      //�����ӽ����±�
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