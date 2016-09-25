#pragma once 
#include<cassert>
#include<iostream>
#include<queue>
using namespace std;

template<typename T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode *_left;
	BinaryTreeNode *_right;
	BinaryTreeNode(const T& data = T())
		:_data(data)
		, _left(NULL)
		, _right(NULL){}
};


template<typename T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root()
	{}

	BinaryTree(const T *array,size_t size,const T& invalid)
	{
		size_t index = 0;
		_root=_CreatTree(array,size,index,invalid);
	}

	BinaryTree(const BinaryTree<T>& t)
	{
		_root=_Copy(t._root);
	}

	BinaryTree& operator=(BinaryTree<T>& t)
	{
		if (this != &t)             //防止自赋值
		{
			BinaryTree<T> tmp(t);
			swap(_root,tmp._root);
		}
		return *this;
	}

	~BinaryTree()
	{
		_destory(_root);
	}

	size_t Leaf()         //求叶子结点的个数
	{
		return _leaf(_root);
	}

	size_t Size()    //求结点个数
	{
		return _Size(_root);
	}

	size_t Depth()          //求深度
	{
		return _Depth(_root);
	}

	void PrevOder()     //前序遍历
	{
		_PrevPrint(_root);
		cout << endl;
	}

	void InOder()      //中序遍历
	{
		_InPrint(_root);
		cout << endl;
	}

	void BackOder()      //后序遍历
	{
		_BackPrint(_root);
		cout << endl;
	}

	void TierOder()       //层序遍历
	{
		_TierPrint(_root);
		cout << endl;
	}

protected:
	Node* _CreatTree(const T *array, size_t size, size_t& index, const T& invalid)
	{
		assert(array);
		Node *root=NULL;
		if (index < size&&array[index] != invalid)
		{
			root = new Node(array[index]);                                  //创建根节点
			root->_left = _CreatTree(array,size,++index,invalid);           //递归创建左子树
			root->_right= _CreatTree(array,size,++index,invalid);           //递归创建右子树
		}
		return root;
	}

	void _PrevPrint(Node *root)
	{
		Node *cur =root;
		if (cur)
		{
			cout << cur->_data << " ";
			_PrevPrint(cur->_left);
			_PrevPrint(cur->_right);
		}
	}

	void _InPrint(Node *root)
	{
		Node *cur = root;
		if (cur)
		{
			_InPrint(cur->_left);
			cout << cur->_data << " ";
			_InPrint(cur->_right);
		}
	}

	void _BackPrint(Node *root)
	{
		Node *cur = root;
		if (cur)
		{
			_BackPrint(cur->_left);
			_BackPrint(cur->_right);
			cout << cur->_data << " ";
		}
	}

	void _TierPrint(Node *root)
	{
		queue<Node*> q;
		Node* cur=root;
		q.push(cur);
		while(!q.empty())
		{
			Node* tmp = q.front();
			cout << tmp->_data <<" ";

			if (tmp->_left)
			    q.push(tmp->_left);
			if (tmp->_right)
				q.push(tmp->_right);
			q.pop();
		}
	}

	size_t _Size(Node *root)
	{
		if (root == NULL)
			return 0;
		return 1 + _Size(root->_left) + _Size(root->_right);
	}

	size_t _Depth(Node *root)
	{
		Node *cur = root;
		if (NULL == cur)
			return 0;

		return 1 + (_Depth(cur->_left) > _Depth(cur->_right) 
			   ? _Depth(cur->_left) : _Depth(cur->_right));
	}

	void _destory(Node *root)
	{
		Node *cur =root;
		if (cur)
		{
			_destory(cur->_left);
			_destory(cur->_right);
			delete cur;
			cur = NULL;
		}
	}

	Node* _Copy(Node* node)
	{
		Node* cur= node;
		Node* root = NULL;
		if (cur)
		{
			root = new Node(cur->_data);
			root->_left =_Copy(cur->_left);
			root->_right=_Copy(cur->_right);
		}
		return root;
	}

	size_t _leaf(Node* root)
	{
		Node* cur = root;
		if (NULL==cur)
			return 0;
		if (cur->_left == NULL&&cur->_right == NULL)      //如果左右子树都为空，则返回1
			return 1;
		return _leaf(cur->_left ) + _leaf(cur->_right);
	}
protected:
	Node *_root;
};