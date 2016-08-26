#include"LinkList.h"


template<typename T,template<class> class Container>
class Queue
{
public:
	void Push(const T& d);
	void Pop();
	T& Front();
	T& Back();
	size_t Size();
	bool Empty();
	void Display()
	{
		while (!Empty())
		{
			cout << Front() << " ";
			Pop();
		}
		cout << endl;
	}
private:
	Container<T> _con;
};

template<typename T,template<class> class Container>
void Queue<T,Container>::Push(const T& d)
{
	_con.PushBack(d);
}

template<typename T,template<class> class Container>
void Queue<T,Container>::Pop()
{
	_con.PopFront();
}

template<typename T,template<class> class Container>
T& Queue<T,Container>::Front()
{
	return _con.GetFront();
}

template<typename T,template<class> class Container>
T& Queue<T,Container>::Back()
{
	return _con.GetBack();
}

template<typename T,template<class> class Container>
size_t Queue<T,Container>::Size()
{
	return _con.Size();
}

template<typename T,template<class> class Container>
bool Queue<T,Container>::Empty()
{
	return _con.Size()== 0;
}