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
	ThreadTreeNode<T> *_parent;
	int _leftTag;
	int _rightTag;
	ThreadTreeNode(const T& data)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{}
};


template<typename T>
class ThreadBinaryTree
{
	typedef ThreadTreeNode<T> Node;
public:
	ThreadBinaryTree()
		:_root(NULL)
	{}
	ThreadBinaryTree(const T* a,size_t size,const T& invalid)
	{
		size_t index = 0;
		Node* prev = NULL;
		_root = _CreatTree(a,size,index,invalid,prev);
		PostThreadTree();
	}

	void PostOder()          //后序遍历  后序线索化二叉树
	{
		if (_root == NULL)
			return;
		Node* cur = _root;
		while (cur->_leftTag == LINK || cur->_rightTag == LINK) //找到左子树后序遍历下的第一个结点
		{
			if (cur->_leftTag == LINK)
				cur = cur->_left;
			else if (cur->_rightTag == LINK)
				cur = cur->_right;
		}
		cout << cur->_data << " ";
		Node* p = NULL;
		while ((p = cur->_parent) != NULL)
		{
			if (p->_right == cur || p->_rightTag == THREAD)
				cur = p;
			else
			{
				cur = p->_right;
				while (cur->_leftTag == LINK || cur->_rightTag == LINK)
				{
					if (cur->_leftTag == LINK)
						cur = cur->_left;
					else if (cur->_rightTag == LINK)
						cur = cur->_right;
				}
			}
			cout << cur->_data << " ";
		}
		cout << endl;
	}
protected:
	Node* _CreatTree(const T* a,size_t size,size_t& index,const T& invalid,Node* prev)
	{
		Node* root = NULL;
		if (index <size&&a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_parent = prev;
			prev = root;
			root->_left = _CreatTree(a,size,++index,invalid,prev);
			root->_right = _CreatTree(a,size,++index,invalid,prev);
		}
		return root;
	}

	void PostThreadTree()        //后序线索化二叉树
	{
		Node* prev = NULL;
		_PostThreadTree(_root,prev);
		if (prev->_right == NULL)
			prev->_rightTag = THREAD;
	}

	void _PostThreadTree(Node* root,Node* &prev)
	{
		if (root == NULL)
			return;
		_PostThreadTree(root->_left, prev);
		_PostThreadTree(root->_right, prev);
		if (root->_left == NULL)             //线索化前驱
		{
			root->_left = prev;
			root->_leftTag = THREAD;
			if (prev&&prev->_right == NULL)
			{
				prev->_right = root;
				prev->_rightTag = THREAD;
			}
			prev = root;
		}
		else if(prev&&prev->_right==NULL)                 //线索化后继
		{
			prev->_right = root;
			prev->_rightTag = THREAD;
			prev = root;
		}	
	}
protected:
	Node* _root;
};