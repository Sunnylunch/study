#pragma once


template<typename T>
struct Node
{
	T _data;
	Node<T> *_left;
	Node<T> *_right;
	int _leftTag;
	int _rightTag;
	Node(const T& data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};


template<typename T>
class BinarySearchTree
{
	typedef  Node<T> Node;
public:
	BinarySearchTree()
		:_root(NULL)
	{}
	BinarySearchTree(const T* a, size_t size)
	{
		size_t index = 0;
		//创建一颗搜索二叉树
		for (index = 0; index < size; index++)
		{
			_Insert(_root,a[index]);
		}

		//中序线索化
		//InThreadTree();
	}

	Node* root()
	{
		return _root;
	}
protected:
	void _Insert(Node* &cur, const T& x)
	{
		if (cur == NULL)
		{
			cur = new Node(x);
			return;
		}
		if (x < cur->_data)
		{
			_Insert(cur->_left, x);
		}
		else if (cur->_data < x)
		{
			_Insert(cur->_right, x);
		}
	}
protected:
	Node* _root;
};


template<typename T>
class TreeToList
{
	typedef Node<T> Node;
public:
	TreeToList()
	{}
	Node*& Transfrom(Node* &head)    //head是搜索树的根节点
	{
		Node* prev = NULL;
		_Transfrom(head,prev);       //转换成双向链表
		while (head->_left)          //寻找链表的头
			head = head->_left;       
		return head;
	}

protected:
	//采用中序线索化的思想，将left变为前驱指针，right变为后继指针
	void _Transfrom(Node* root,Node* &prev)         
	{
		if (root == NULL)
			return;
		Node* cur = root;
		_Transfrom(cur->_left ,prev);
		if (prev)
		{
			prev->_right = cur;
		}
		cur->_left = prev;
		prev = cur;
		_Transfrom(cur->_right ,prev);
	}
};