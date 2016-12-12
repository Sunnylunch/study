#pragma once
#include"Construct.h"
#include"Allocator.h"
using namespace std;

template<typename T>
struct ListNode
{
	T _data;
	ListNode<T>* _next;
	ListNode<T>* _prev;
	ListNode(const T& data)
		:_data(data)
		, _next(NULL)
		, _prev(NULL)
	{}
};


template<typename T, typename Ref, typename  Ptr>
struct ListIterator
{
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ref, Ptr> Self;
public:
	ListIterator(Node* p)
		:_node(p)
	{}

	Self& operator++()                  //前置自增
	{
		_node = _node->_next;
		return *this;
	}

	Self operator++(int)                //后置自增
	{
		Node* tmp = _node;
		_node = _node->_next;
		return tmp;                     //掉构造函数构造一个临时变量返回
	}

	Self& operator--()
	{
		_node = _node->_prev;
		return _node;
	}

	Self operator--(int)
	{
		Node* tmp = _node;
		_node = _node->_prev;
		return tmp;                    //调用构造函数生成一个临时变量返回
	}

	bool operator!=(const ListIterator<T, Ref, Ptr>& Iter)
	{
		return _node != Iter._node;
	}

	bool operator==(const ListIterator<T, Ref, Ptr>& Iter)
	{
		return _node == Iter._node;
	}

	Node* _node;
};



template<typename T, typename _ALLOC = Alloc>
class List
{
	typedef ListNode<T> Node;
	typedef SimpleAlloc<Node, _ALLOC> ListNodeAlloc;
public:
	typedef ListIterator<T, T&, T*> Iterator;
	typedef ListIterator<const T, const T&, const T*> ConstIterator;

	List()
		:_head(BuyListNode(T()))       //开辟一个新结点
	{
		_head->_next = _head;        //双向循环链表
		_head->_prev = _head;
	}

	~List()
	{
		Clear();                                //析构之前将所有结点都删除掉
		DestoryNode(_head);                    //删除掉哨兵结点
	}

	void Clear()                         //清空链表上的结点，保留哨兵结点
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			Node* del = cur;
			cur = cur->_next;
			DestoryNode(del);
		}
		_head->_next = _head;
		_head->_prev = _head;
	}


	void PushBack(const T& value)
	{
		Insert(End(), value);
	}

	void PushFront(const T& value)
	{
		Insert(Begin(), value);
	}

	void PopBack()
	{
		Erase(--End());
	}

	void PopFront()
	{
		Erase(Begin());
	}

	Iterator Insert(Iterator pos, const T& value)
	{
		Node* newNode = BuyListNode(value);   //新创建一个结点

		Node* cur = pos._node;
		Node* prev = pos._node->_prev;

		prev->_next = newNode;
		newNode->_next = cur;

		cur->_prev = newNode;
		newNode->_prev = prev;

		return newNode;
	}

	Iterator Erase(Iterator pos)
	{
		Node* prev = pos._node->_prev;
		Node* next = pos._node->_next;

		prev->_next = next;
		next->_prev = prev;

		DestoryNode(pos._node);          //建这个结点销毁掉
		return next;
	}

	Iterator Begin()
	{
		return _head->_next;
	}

	Iterator Begin() const
	{
		return _head->_next;
	}

	Iterator End()
	{
		return _head;
	}

	Iterator End() const
	{
		return _head;
	}

protected:
	Node* BuyListNode(const T& value)                              //新开辟一个结点
	{
		Node* cur = ListNodeAlloc::Allocate();
		Construct(cur, value);        //初始化这个结点，这时候就会自动调用Node的构造函数
		return cur;
	}

	void DestoryNode(Node* ptr)
	{
		Destory(ptr);                             //析构空间
		ListNodeAlloc::DeAllocate(ptr);           //释放空间
	}
private:
	Node* _head;
};


void Test()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);

	List<int>::Iterator iter = l.Begin();
	iter = l.Insert(iter, 8);
	while (iter != l.End())
	{
		iter = l.Erase(iter);
	}
}