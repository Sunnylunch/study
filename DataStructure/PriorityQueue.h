#pragma once
#include"heap.h"
template<typename T,class Compare=Less<T> >
class PriQueue
{
public:
	void Push(const T& x)
	{
		h.Push(x);
	}

	void Pop()
	{
		h.Pop();
	}

	const T& Top()
	{
		return h.Top();
	}
private:
	Heap<T, Compare> h;
};