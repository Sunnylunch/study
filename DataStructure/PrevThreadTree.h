#pragma once 

enum
{
	LINK,
	THREAD,
};

template<typename T>
struct ThreadTreeNode
{
	T _data;
	ThreadTreeNode<T> *_left;
	ThreadTreeNode<T> *_right;
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
class ThreadBinaryTree
{
	typedef  ThreadTreeNode<T> Node;
public:
	ThreadBinaryTree()
		:_root(NULL)
	{}
	ThreadBinaryTree(const T* a, size_t size, const T& invalid)
	{
		size_t index = 0;
		_root = _CreatTree(a, size, index, invalid);      //构造一颗二叉树
		PrevThreadTree();                                  //前序线索化二叉树
	}

	//前序遍历 前序线索化二叉树
	void PrevOder()
	{
		if (_root == NULL)
			return;
		Node* cur = _root;
		while (cur)
		{
			while (cur->_leftTag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			cur = cur->_right;
		}
		cout << endl;
	}

protected:
	//前序线索化二叉树
	void PrevThreadTree()
	{
		Node* prev = NULL;
		_PrevThreadTree(_root, prev);
		prev->_rightTag = THREAD;
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

	//前序 线索化二叉树
	void _PrevThreadTree(Node* root, Node* &prev)
	{
		if (root == NULL)
			return;
		if (root->_left != NULL)
		{
			if (prev&&prev->_right == NULL)
			{
				prev->_right = root;
				prev->_rightTag = THREAD;
			}
			prev = root;
		}
		else
		{
			root->_leftTag = THREAD;
			root->_left = prev;
			if (prev->_right == NULL)
			{
				prev->_right = root;
				prev->_rightTag = THREAD;
			}
			prev = root;
		}

		if (root->_leftTag != THREAD)
		{
			_PrevThreadTree(root->_left, prev);
		}
		if (root->_rightTag != THREAD)
		{
			_PrevThreadTree(root->_right, prev);
		}
	}
protected:
	Node* _root;
};















