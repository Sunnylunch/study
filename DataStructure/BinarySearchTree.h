#pragma once
#include<cassert>

template<typename T>
struct SearchTreeNode
{
	T _data;
	SearchTreeNode<T>* _left;
	SearchTreeNode<T>* _right;
	SearchTreeNode()
		:_left(NULL)
		, _right(NULL)
	{}
	SearchTreeNode(const T& data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};


template<typename T>
class BinarySearchTree
{
	typedef SearchTreeNode<T> Node;
public:
	BinarySearchTree()
		:_root(NULL)
	{}
	BinarySearchTree(const T* a, size_t size)
	{
		size_t index = 0;
		for (index = 0; index < size; index++)
		{
			Insert(a[index]);
		}
	}

	~BinarySearchTree()
	{
		_Destory(_root);
	}

	void MakeEmpty()
	{
		if (_root!=NULL)
		{
			BinarySearchTree<T> tmp;
			swap(tmp._root, _root);
		}
	}

	bool IsEmpty()
	{
		return _root == NULL;
	}

	void Insert(const T& x)
	{
		_Insert(_root, x);
	}

	void Remove(const T& x)
	{
		_Remove(_root,x);
	}

	void RemoveMin()
	{
		_Remove(_root,FindMin());
	}

	void RemoveMax()
	{
		_Remove(_root,FindMax());
	}

	const T& FindMin()
	{
		Node* tmp=_FindMin(_root);
		return tmp->_data;
	}

	const T& FindMax()
	{
		Node* tmp = _FindMax(_root);
		return tmp->_data;
	}

	const T& Find(int k)
	{
		assert(k>=1);
		assert(k<=_Size(_root));
		Node* tmp=_Find(_root,k);
		return tmp->_data;
	}
protected:
	void _Insert(Node* &cur,const T& x)
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
			_Insert(cur->_right,x);
		}
	}

	void _Destory(Node* root)
	{
		if (root == NULL)
			return;
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}

	void _Remove(Node* &cur,const T& x)
	{
		if (cur == NULL)
			return;
		if (x < cur->_data)
		{
			_Remove(cur->_left,x);
		}
		else if (cur->_data < x)
		{
			_Remove(cur->_right,x);
		}
		else
		{
			if (cur->_left != NULL&&cur->_right != NULL) //如果要删除的结点有两个孩子
			{
				Node* del = cur;
				cur->_data =_FindMin(cur->_right)->_data;
				_Remove(cur->_right,cur->_data);
			}
			else                   //如果要删除的结点是叶子结点或只有一个孩子的结点
			{
				Node* del = cur;
				cur = (cur->_left != NULL) ? cur->_left : cur->_right;
				delete del;
			}
		}
	}

	Node* _FindMin(Node* cur)
	{
		assert(cur);
		while (cur->_left)
		{
			cur = cur->_left;
		}
		return cur;
	}

	Node* _FindMax(Node* cur)
	{
		assert(cur);
		while (cur->_right)
			cur = cur->_right;
		return cur;
	}

	int _Size(Node* cur)
	{
		if (cur == NULL)
			return 0;
		return 1 + _Size(cur->_left) + _Size(cur->_right);  //当前结点加上左子树结点加上右子树结点
	}

	Node* _Find(Node* cur,int k)
	{
		int num =_Size(cur->_left);
		if (k == num + 1)
			return cur;
		else if (k <= num)
		{
			return _Find(cur->_left,k);
		}
		else
		{
			return _Find(cur->_right,k-num-1);
		}
	}
protected:
	Node* _root;
};