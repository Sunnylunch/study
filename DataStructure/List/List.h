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

	Self& operator++()                  //ǰ������
	{
		_node = _node->_next;
		return *this;
	}

	Self operator++(int)                //��������
	{
		Node* tmp = _node;
		_node = _node->_next;
		return tmp;                     //�����캯������һ����ʱ��������
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
		return tmp;                    //���ù��캯������һ����ʱ��������
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
		:_head(BuyListNode(T()))       //����һ���½��
	{
		_head->_next = _head;        //˫��ѭ������
		_head->_prev = _head;
	}

	~List()
	{
		Clear();                                //����֮ǰ�����н�㶼ɾ����
		DestoryNode(_head);                    //ɾ�����ڱ����
	}

	void Clear()                         //��������ϵĽ�㣬�����ڱ����
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
		Node* newNode = BuyListNode(value);   //�´���һ�����

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

		DestoryNode(pos._node);          //�����������ٵ�
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
	Node* BuyListNode(const T& value)                              //�¿���һ�����
	{
		Node* cur = ListNodeAlloc::Allocate();
		Construct(cur, value);        //��ʼ�������㣬��ʱ��ͻ��Զ�����Node�Ĺ��캯��
		return cur;
	}

	void DestoryNode(Node* ptr)
	{
		Destory(ptr);                             //�����ռ�
		ListNodeAlloc::DeAllocate(ptr);           //�ͷſռ�
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