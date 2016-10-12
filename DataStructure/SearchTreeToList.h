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
		//����һ������������
		for (index = 0; index < size; index++)
		{
			_Insert(_root,a[index]);
		}

		//����������
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
	Node*& Transfrom(Node* &head)    //head���������ĸ��ڵ�
	{
		Node* prev = NULL;
		_Transfrom(head,prev);       //ת����˫������
		while (head->_left)          //Ѱ�������ͷ
			head = head->_left;       
		return head;
	}

protected:
	//����������������˼�룬��left��Ϊǰ��ָ�룬right��Ϊ���ָ��
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