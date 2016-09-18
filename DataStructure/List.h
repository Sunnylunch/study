#pragma once
#include<iostream>
#include<cassert>
using namespace std;

template<typename T>
struct ListNode
{
	T _data;
	ListNode<T> *_next;
	ListNode<T> *_prev;
	ListNode(const T& data=T())
		:_data(data)
		, _next(NULL)
		, _prev(NULL)
	{}
};

template<typename T,typename Ref,typename Ptr>
struct ListIterator
{
	typedef ListNode<T> Node;

	ListIterator(Node* ptr=NULL)
		:_Node(ptr){}

	Ref operator*()
	{
		return _Node->_data;
	}

	Ptr operator->()
	{
		//return &(operator*);
		return (&(_Node->_data));
	}

	bool operator==(ListIterator iter)
	{
		return _Node ==iter._Node;
	}

	bool operator!=(ListIterator iter)
	{
		return _Node!= iter._Node;
	}

	ListIterator& operator++()
	{
		_Node = _Node->_next;
		return *this;
	}

	ListIterator operator++(int)
	{
		Node *tmp = _Node;
		_Node = _Node->_next;
		return tmp;
	}

	ListIterator& operator--()
	{
		_Node = _Node->_prev;
		return *this;
	}

	ListIterator operator--(int)
	{
		Node *tmp = _Node;
		_Node = _Node->_prev;
		return tmp;
	}

	Node *_Node;
};


template<typename T>
class List
{
public:
	typedef ListIterator<T, T&, T*>  Iterator;
	typedef ListIterator<T, const T&,const T* > ConstIterator;
	typedef ListNode<T> Node;
	typedef Iterator Self;
	
	List()
		:_head(new Node)
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	void PushBack(const T& data)
	{
		/*Node *tmp = BuyNode(data);
		Node *tail= _head->_prev;
		tail->_next = tmp;
		tmp->_prev =tail;

		tmp->_next = _head;
		_head->_prev = tmp;*/

		Insert(Self(_head), data);
	}

	void PushFront(const T& data)
	{
		/*Node *tmp = BuyNode(data);
		Node *first= _head->_next;
		_head->_next = tmp;
		tmp->_prev = _head;

		tmp->_next = first;
		first->_prev = tmp;*/

		Insert(_head->_next, data);
	}


	void PopBack()
	{
		assert(_head->_next!=_head->_prev);
		Erase(Self(_head->_prev));
	}

	void PopFront()
	{
		assert(_head->_next != _head->_prev);
		Erase(Self(_head->_next));
	}

	Self Erase(Self Pos)
	{
		assert((Pos._Node!=_head));        //不能删除哨兵
		Node *prev = Pos._Node->_prev;
		Node *cur = Pos._Node;
		Node *next = Pos._Node->_next;

		prev->_next = next;
		next->_prev = prev;

		delete cur;
		return next;      //调用Iterator的缺省构造函数生成临时变量返回
	}

	Self Insert(Self Pos, const T& data)
	{
		Node *tmp = BuyNode(data);
		Node *prev = Pos._Node->_prev;
		Node *cur = Pos._Node;
		
		prev->_next = tmp;
		tmp->_prev = prev;

		cur->_prev = tmp;
		tmp->_next = cur;

		return cur;         //调用Iterator的缺省构造函数生成临时变量返回
	}

	T& Front()
	{
		assert(_head->_next != _head->_prev);
		return _head->_next->_data;
	}

	T& Back()
	{
		assert(_head->_next != _head->_prev);
		return _head->_prev->_data;
	}

	size_t Size()
	{
		Node *cur = _head->_next;
		size_t count = 0;
		while (cur != _head)
		{
			count++;
			cur = cur->_next;
		}
		return count;
	}

	bool Empty()
	{
		return _head->_next == _head->_prev;
	}

	size_t MaxSize()
	{
		return -1;
	}

	Self Begin()
	{
		return _head->_next;    //调用Iterator的默认构造函数生成临时变量返回
	}

	Self End()
	{
		return _head;        //调用Iterator的默认构造函数生成临时变量返回
	}

	ConstIterator Begin()const
	{
		return _head->_next;    //调用Iterator的默认构造函数生成临时变量返回
	}

	ConstIterator End()const
	{
		return _head;        //调用Iterator的默认构造函数生成临时变量返回
	}

private:
	Node* BuyNode(const T& data)
	{
		Node *tmp = new Node(data);
		return tmp;
	}
private:
	Node *_head;
};



