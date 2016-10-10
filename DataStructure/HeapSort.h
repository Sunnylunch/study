#pragma once
#include<cassert>
template<typename T>
struct UpOder
{
	bool operator()(const T& l,const T& r)    //����
	{
		return l < r;
	}
};

template<typename T>            //����
struct DownOder
{
	bool operator()(const T& l, const T& r)
	{
		return l>r;
	}
};

//Ĭ�϶����������򣬿�ͨ���º������ݲ�������Ϊ����
template<typename T,class Compare=UpOder<T>>
class HeapSort
{
public:
	HeapSort()
	{}
	void Sort(T* a, int size)
	{
		//����
		assert(a);
		for (int i = (size - 2) / 2; i >= 0; --i)
		{
			AdjustDown(a, i, size);
		}

		//������
		while (size >1)   
		{
			swap(a[0],a[size-1]);
			--size;
			AdjustDown(a,0,size);			
		}
	}
protected:
	//�»�����
	void AdjustDown(T* a,int root,int size)
	{
		assert(size>0);
		int parent = root;
		int child = parent * 2 + 1;
		while (child < size)
		{
			if ((child + 1) < size&&Compare()(a[child],a[child+1]))
				child++;
			if (Compare()(a[parent], a[child]))
			{
				swap(a[parent],a[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
};