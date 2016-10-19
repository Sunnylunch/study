#pragma once
#include<cassert>
#include<queue>
using namespace std;

template<typename T>
struct SearchTreeNode
{
	SearchTreeNode<T>* _left;
	SearchTreeNode<T>* _right;
	T _key;
	SearchTreeNode(const T& key)
		:_left(NULL)
		, _right(NULL)
		, _key(key)
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

	BinarySearchTree(T* a,size_t size)
	{
		_root = NULL;
		for (int i = 0; i < (int)size; i++)
		{
			Insert(a[i]);
		}
	}

	BinarySearchTree(const BinarySearchTree<T>& tree)     //��������
		:_root(NULL)
	{
		queue<Node*> q;
		q.push(tree._root);
		while (!q.empty())
		{
			Node* cur = q.front();
			Insert(cur->_key);
			q.pop();
			if (cur->_left)
			{
				q.push(cur->_left);
			}
			if (cur->_right)
			{
				q.push(cur->_right);
			}
		}	
	}

	~BinarySearchTree()
	{
		_Destory(_root);
	}


	BinarySearchTree<T>& operator=(BinarySearchTree<T>& tree)  //��ֵ���������
	{
		if (this!=&tree)
		{
			BinarySearchTree<T> tmp(tree);
			swap(_root,tmp._root);
		}
		return *this;
	}

	bool Insert(const T& x)
	{
		if (_root == NULL)
		{
			_root = new Node(x);
			return true;
		}
		Node* cur = _root;
		Node* parent =NULL;
		while (cur)                     //�ҵ�Ҫ�����λ��
		{
			parent = cur;
			if (x > cur->_key)      //���Ҫ�����ֵ���ڵ�ǰ���
			{
				cur = cur->_right;
			}
			else if (x<cur->_key)     //���Ҫ�����ֵС�ڵ�ǰ���
			{
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		//�ж�һ��xҪ���뵽parent����߻����ұ�
		if (x>parent->_key)       //���뵽�ұ�
		{
			parent->_right = new Node(x);
		}
		else         //���뵽���
		{
			parent->_left = new Node(x);
		}
		return true;
	}

	bool Remove(const T& x)
	{
		Node* cur=_root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key < x)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>x)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				if (cur->_left == NULL)     //���cur������Ϊ�գ������Ҷ�Ϊ��
				{
					if (parent->_left==cur)
					{
						parent->_left = cur->_right;
					}
					else
					{
						parent->_right = cur->_right;
					}
					delete cur;
				}
				else if (cur->_right == NULL)    //���cur���Һ���Ϊ��
				{
					if (parent->_left == cur)
					{
						parent->_left = cur->_left;
					}
					else
					{
						parent->_right = cur->_left;
					}
					delete cur;
				}
				else           //������Ҷ���Ϊ�գ�Ѱ��cur���������������㣬��֮����
				{
					Node* tmp = cur->_right;
					Node* prev = cur;
					while (tmp->_left)
					{
						prev= tmp;
						tmp =tmp->_left;
					}
					swap(cur->_key,tmp->_key);      //��������������ֵ
					if (prev->_left == tmp)
					{
						prev->_left = NULL;
					}
					else
					{
						prev->_right = NULL;
					}
					delete tmp;					
				}
				return true;
			}
		}
		return false;
	}

	const Node* Find(const T& x)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < x)
			{
				cur = cur->_right;
			}
			else if (cur->_key>x)
			{
				cur = cur->_left;
			}
			else 
			{
				return cur;
			}
		}
		return cur;
	}
protected:
	void _Destory(Node* cur)
	{
		if (cur == NULL)
			return;
		_Destory(cur->_left);
		_Destory(cur->_right);
		delete cur;
	}

private:
	Node* _root;
};