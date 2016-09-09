#include<iostream>
#include<cassert>
using namespace std;


template<typename T>
struct QueueNode
{
	QueueNode(const T& data)
		:_data(data)
		, _next(NULL){}
	T _data;
	QueueNode<T> * _next;
};

template<typename T>
class Queue
{
	typedef struct QueueNode<T> Node;
public:
	Queue()
		:_head(NULL)
		, _tail(NULL){}
	~Queue()
	{
		Node *cur = _head;
		while (cur)
		{
			Node *del = cur;
			cur= cur->_next;
			delete del;
		}
		_head = NULL;
		_tail = NULL;
	}
	bool Empty();
	T& Front();
	T& Back();
	void Push(const T& data);
	void Pop();
	int Size();
protected:
	Node *_head;
	Node *_tail;
};

template<typename T>
bool Queue<T>::Empty()
{
	if (_head == NULL)
		return true;
	else
		return false;
}

template<typename T>
T& Queue<T>::Front()
{
	assert(_head);
	return _head->_data;
}

template<typename T>
T& Queue<T>::Back()
{
	assert(_tail);
	return _tail->_data;
}

template<typename T>
void Queue<T>::Push(const T& data)      //Î²²å
{
	Node *NewNode = new Node(data);
	if (_head == NULL)                   //¿Õ¶ÓÁÐ
	{
		_tail=_head = NewNode;
	}
	else
	{
		_tail->_next = NewNode;
		_tail = _tail->_next;
	}
}

template<typename T>
void Queue<T>::Pop()               //Í·É¾
{
	assert(_head);
	Node *del = _head;
	_head = _head->_next;
	delete del;
	if (NULL == _head)
	{
		_tail = NULL;
	}
}

template<typename T>
int Queue<T>::Size()
{

	int count = 0;
	Node *cur = _head;
	while (cur)
	{
		++count;
		cur = cur->_next;
	}
	return count;
}