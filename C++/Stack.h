#include"Seqlist.h"

template<typename T,template<class> class Container>
class Stack
{
public:
	bool Empty();
	void Push(const T& d);
	void Pop();
	T& Top();
	int Size();
	void Display()
	{
		while (!Empty())
		{
			cout << Top() << " ";
			Pop();
		}
		cout << endl;
	}
private:
	Container<T> _con;
};

template<typename T, template<class> class Container>
bool Stack<T,Container>::Empty()
{
	return _con.GetSize()==0;
}

template<typename T, template<class> class Container>
void Stack<T, Container>::Pop()
{
	_con.PopBack();
}

template<typename T, template<class> class Container>
void Stack<T,Container>::Push(const T& d)
{
	_con.PushBack(d);
}

template<typename T, template<class> class Container>
int Stack<T,Container>::Size()
{
	return _con.GetSize();
}

template<typename T, template<class> class Container>
T& Stack<T, Container>::Top()
{
	int sz=_con.GetSize()-1;
	return _con[sz];
}

