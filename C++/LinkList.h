
#pragma once
#include<iostream>
#include<string>
#include<cassert>
using namespace std;


template<typename T>
struct Node
{
public:
	Node(const T& d)
		:_next(NULL)
		, _prev(NULL)
	    ,_data(d){}
	T _data;
	Node<T> *_next;
	Node<T> *_prev;
};

template<typename T>
class LinkList
{
public:
	LinkList()
		:_head(NULL)
		, _tail(NULL){}
	LinkList(const LinkList<T>& list);
	LinkList<T>& operator=(LinkList<T> list);
	~LinkList();
	void PushBack(const T& d);
	void PushFront(const T& d);
	void PopBack();
	void PopFront();
	void Insert(Node<T> *addr, const T& d);  //在当前结点后面插入元素
	Node<T>* Search(const T& d);
	void Remove(const T& d);
	void RemoveAll(const T& d);
	void Sort();
	void Display();
	size_t Size();
	T& GetFront()
	{
		assert(_head);
		return _head->_data;
	}
	T& GetBack()
	{
		assert(_tail);
		return _tail->_data;
	}
private:
	Node<T> *_head;
	Node<T> *_tail;
};




template<typename T>
size_t LinkList<T>::Size()
{
	Node<T> *cur = _head;
	size_t count = 0;
	while (cur)
	{
		count++;
		cur = cur->_next;
	}
	return count;
}


template<typename T>
LinkList<T>::LinkList(const LinkList<T>& list)
			:_head(NULL)
			, _tail(NULL)
{
	Node<T> *cur = list._head;
	while (cur)
	{
		PushBack(cur->_data);
		cur = cur->_next;
	}
}

template<typename T>
LinkList<T>& LinkList<T>::operator=(LinkList<T> list)
{

	std::swap(_head,list._head);
	std::swap(_tail,list._tail);
	return *this;
}

template<typename T>
LinkList<T>::~LinkList()
{
	Node<T> *cur = _head;
	while (cur)
	{
		_head = _head->_next;
		delete cur;
		cur = _head;
	}
	_tail = NULL;
}

template<typename T>
void LinkList<T>::PushBack(const T& d)
{
	Node<T> *NewHead = new Node<T>(d);
	if (NULL == _head)
	{
		_head = NewHead;
		_tail = NewHead;
	}
	else
	{
		_tail->_next = NewHead;
		NewHead->_prev = _tail;
		_tail = _tail->_next;
	}
}

template<typename T>
void LinkList<T>::PushFront(const T& d)
{
	Node<T> *NewHead = new Node<T>(d);
	if (NULL == _head)
	{
		_head = NewHead;
		_tail = NewHead;
	}
	else
	{
		NewHead->_next = _head;
		_head->_prev = NewHead;
		_head = NewHead;
	}
}

template<typename T>
void LinkList<T>::PopBack()
{
	if (NULL == _head)
	{
		return;
	}
	else if (NULL==_head->_next)
	{
		delete _tail;
		_head = NULL;
		_tail = NULL;
	}
	else
	{
		Node<T> *cur = _tail;
		_tail = _tail->_prev;
		_tail->_next = NULL;
		delete cur;
	}

}

template<typename T>
void LinkList<T>::PopFront()
{
	if (NULL == _head)
	{
		return;
	}
	else if (NULL == _head->_next)
	{
		delete _tail;
		_head = NULL;
		_tail = NULL;
	}
	else
	{
		Node<T> *cur = _head;
		_head = _head->_next;
		_head->_prev = NULL;
		delete cur;
	}
}

template<typename T>
void LinkList<T>::Insert(Node<T> *addr, const T& d)   //在当前结点后面插入元素
{
	Node<T> *NewNode = new Node<T>(d);
	if (_head == addr)
	{
		NewNode->_next = _head;
		_head->_prev = NewNode;
		_head = NewNode;
	}
	else if (_tail == addr)
	{
		PushBack(d);
	}
	else
	{
		NewNode->_next = addr->_next;
		addr->_next->_prev = NewNode;
		addr->_next = NewNode;
		NewNode->_prev = addr;
	}
}

template<typename T>
Node<T>* LinkList<T>::Search(const T& d)
{
	Node<T> *cur = _head;
	while (cur)
	{
		if (cur->_data == d)
		{
			return cur;
		}
		cur = cur->_next;
	}
	return NULL;
}

template<typename T>
void LinkList<T>::Remove(const T& d)
{
	Node<T> *cur =Search(d);
	if (cur == _head)
	{
		PopFront();
	}
	else if (cur == _tail)
	{
		PopBack();
	}
	else
	{
		cur->_prev->_next = cur->_next;
		cur->_next->_prev = cur->_prev;
		delete cur;
	}
}

template<typename T>
void LinkList<T>::RemoveAll(const T& d)
{
	while (Search(d) != NULL)
	{
		Remove(d);
	}
}

template<typename T>
void LinkList<T>::Sort()
{
	Node<T> *end = _tail;
	while (_head != end)
	{
		Node<T> *cur = _head;
		int flag = 1;
		while (cur!=end)
		{
			if (cur->_data > cur->_next->_data)
			{
				T tmp = cur->_data;
				cur->_data = cur->_next->_data;
				cur->_next->_data=tmp;
				flag = 0;
			}
			cur = cur->_next;
		}
		if (flag)
		{
			return;
		}
		end = end->_prev;
	}
}

template<typename T>
void LinkList<T>::Display()
{
	Node<T> *cur = _head;
	while (cur)
	{
		cout << cur->_data << " ";
		cur = cur->_next;
	}
	cout << endl;
}

