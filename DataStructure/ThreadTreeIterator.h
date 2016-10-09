#pragma once
#include<cassert>


enum
{
	LINK,
	THREAD,
};

template<typename T>
struct ThreadTreeNode
{
	T _data;
	ThreadTreeNode<T> * _left;
	ThreadTreeNode<T>* _right;
	int _leftTag;
	int _rightTag;
	ThreadTreeNode(const T& data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{}
};


template<typename T>
class TreeIterator
{
	typedef ThreadTreeNode<T> Node;
	typedef TreeIterator<T> Iterator;
public:
	TreeIterator()
	{}
	TreeIterator(Node* root)
		:_cur(root)
	{}

	Iterator& operator++()
	{
		assert(_cur);
		if (_cur->_rightTag == THREAD)
			_cur = _cur->_right;
		else
		{
			_cur=_cur->_right;
			while (_cur->_leftTag == LINK)
				_cur = _cur->_left;
		}
		return *this;
	}

	Iterator& operator--()
	{
		assert(_cur);
		if (_cur->_leftTag== THREAD)
			_cur = _cur->_left;
		else
		{
			_cur = _cur->_left;
			while (_cur->_rightTag == LINK)         //找到_cur的左子树下最后一个访问的结点
				_cur = _cur->_right;
		}
		return *this;
	}

	Iterator operator++(int)
	{
		assert(_cur);
		Node* cur = _cur;
		if (_cur->_rightTag == THREAD)
			_cur = _cur->_right;
		else
		{
			_cur = _cur->_right;
			while (_cur->_leftTag == LINK)
				_cur = _cur->_left;
		}
		return cur;
	}

	Iterator operator--(int)
	{
		assert(_cur);
		Node* cur = _cur;
		if (_cur->_leftTag== THREAD)
			_cur = _cur->_left;
		else
		{
			_cur = _cur->_left;
			while (_cur->_rightTag == LINK)         //找到_cur的左子树下最后一个访问的结点
				_cur = _cur->_right;
		}
		return cur;
	}

	bool operator!=(const Iterator& it)const
	{
		return _cur!= it._cur;
	}

	bool operator==(const Iterator& it)const
	{
		return _cur == it._cur;
	}
	
	T& operator*()
	{
		assert(_cur);
		return _cur->_data;
	}

	T* operator->()
	{
		assert(_cur);
		return &(_cur->_data);
	}
protected:
	Node* _cur;
};


template<typename T>
class ThreadBinaryTree
{
	typedef  ThreadTreeNode<T> Node;
public:
	typedef TreeIterator<T> Iterator;
	ThreadBinaryTree()
		:_root(NULL)
	{}
	ThreadBinaryTree(const T* a, size_t size, const T& invalid)
	{
		size_t index = 0;
		_root = _CreatTree(a, size, index, invalid);

		//中序线索化二叉树
		Node* prev = NULL;
		_InThreadTree(_root, prev);
		prev->_rightTag = THREAD;
	}

	Iterator Begin()                   //获得这棵树第一个访问的结点
	{
		return Frist();
	}

	Iterator End()                      //获得这棵树最后一个访问的结点
	{
		return NULL;
	}

protected:
	Node* Frist()       //返回第一个访问的结点；
	{
		if (_root == NULL)
			return NULL;
		Node* cur = _root;
		while (cur->_leftTag == LINK)
			cur = cur->_left;
		return cur;
	}

	Node* _CreatTree(const T* a, size_t size, size_t& index, const T& invalid)
	{
		//创建一颗二叉树
		Node* root = NULL;
		if (index < size&&a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreatTree(a, size, ++index, invalid);
			root->_right = _CreatTree(a, size, ++index, invalid);
		}
		return root;
	}

	//中序线索化二叉树
	void _InThreadTree(Node* root, Node* &prev)
	{
		if (NULL == root)
			return;
		_InThreadTree(root->_left, prev);
		if (root->_left == NULL)                //线索化前驱
		{
			root->_leftTag = THREAD;
			root->_left = prev;
			prev = root;
		}
		if (prev != root&&prev->_right == NULL)      //线索化后继
		{
			prev->_rightTag = THREAD;
			prev->_right = root;
			prev = root;
		}
		_InThreadTree(root->_right, prev);
	}
protected:
	Node* _root;
};