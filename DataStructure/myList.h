#pragma once
template<typename T>
struct ListNode
{
	ListNode<T> *_prev;
	ListNode<T> *_next;
	T _data;
	ListNode(const T& data)
		:_prev(NULL)
		, _next(NULL)
		, _data(data){}
};


template<typename T,typename Ref,typename Ptr>
struct ListIterator
{
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ref, Ptr> Self;

	ListIterator(Node *node)
		:_node(node){}

	ListIterator()
	{}

	bool operator==(const Self& s)const
	{
		return _node == s._node;
	}

	bool operator!=(const Self& s)const
	{
		return _node != s._node;
	}

	Self& operator++()
	{
		_node = _node->_next;
		return *this;
	}

	Self* operator++(int)
	{
		Self *tmp = this;
		_node = _node->_next;
		return tmp;
	}

	Self& operator--()
	{
		_node = _node->_prev;
		return *this;
	}

	Self* operator--(int)
	{
		Self *tmp = this;
		_node = _node->_prev;
		return tmp;
	}

	T& operator *()
	{
		return _node->_data;
	}

	T* operator->()
	{
		return &(_node->_data)
	}

	Node *_node;
};

template<typename T>
class List
{
public:
	typedef ListNode<T> Node;
	typedef size_t size_type;
	typedef ListIterator<T, T&, T*> Iterator;
public:
	List()
		:_head(new Node(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}
	void PushBack(const T& data);
	void PushFront(const T& data);
	void PopBack();
	void PopFront();

	void Insert(Iterator pos, const T& data)
	{
		Node *NewNode = BuyNode(data);
		Node *tmp = pos._node->_prev;

		NewNode->_next = pos._node;
		NewNode->_prev = pos._node->_prev;
		pos._node->_prev = NewNode;
		tmp->_next = NewNode;
	}
	void Erase(Iterator pos)
	{
		Node *tmp = pos._node->_prev;

		tmp->_next = pos._node->_next;
		pos._node->_next->_prev = tmp;
	}

	Iterator Begin()
	{
		return Iterator(_head->_next);
	}
	Iterator End()
	{
		return Iterator(_head);
	}


	bool Empty() const
	{
		if (_head->_next == _head)
			return true;
		else
			return false;
	}

	size_type Size()
	{
		size_type count = 0;
		Node *cur = _head->_next;
		while (cur !=_head)
		{
			count++;
			cur = cur->_next;
		}
		return count;
	}

	size_type MaxSize()
	{
		return (size_type)(-1);
	}

	T& Front()
	{
		return _head->_next->_data;
	}

	T& Back()
	{
		return _head->_prev->_data;
	}

	Node* BuyNode(const T& data)
	{
		return (new Node(data));
	}
private:
	Node *_head;
};

template<typename T>
void List<T>::PushBack(const T& data)
{
	Node *NewNode = BuyNode(data);
	Node *tmp = _head->_prev;

	NewNode->_next = _head;
	NewNode->_prev = _head->_prev;
	_head->_prev = NewNode;
	tmp->_next= NewNode;
}

template<typename T>
void List<T>::PushFront(const T& data)
{
	Node *NewNode = BuyNode(data);
	Node *tmp = _head->_next;

	NewNode->_next = _head->_next;
	NewNode->_prev = _head;
	_head->_next = NewNode;
	tmp->_prev = NewNode;
}

template<typename T>
void List<T>::PopBack()
{
	Node *del = _head->_prev;

	del->_prev->_next = _head;
	_head->_prev = del->_prev;
	delete del;
}

template<typename T>
void List<T>::PopFront()
{
	Node *del = _head->_next;

	_head->_next = del->_next;
	del->_next->_prev = _head;
	delete del;
}

