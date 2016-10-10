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
	ThreadBinaryTree(const T* a,size_t size,const T& invalid)
	{
		size_t index = 0;
		_root =_CreatTree(a,size,index,invalid);
	    InThreadTree();
	}
	
	//中序遍历 中序线索化 二叉树
	/*void InOder()
	{
		if (_root == NULL)
			return;
		Node* cur = _root;
		while (cur)
		{
			while (cur->_leftTag == LINK)
				cur = cur->_left;
			cout << cur->_data << " ";
			while (cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			cur = cur->_right;
		}
		cout << endl;
	}*/
	//中序遍历 （2）
	void InOder()
	{
		Node* cur = NULL;
		for (cur = Frist(_root); cur != NULL; cur = Next(cur))
		{
			cout << cur->_data << " ";
		}
		cout << endl;
	}


	//先序遍历   中序线索化二叉树
	void PrevOder()
	{
		if (_root == NULL)
		{
			return;
		}
		Node* cur = _root;
		while (cur)
		{
			while (cur->_leftTag!=THREAD)
			{
				cout << cur->_data<<" ";
				cur = cur->_left;
			}
			cout << cur->_data<<" ";
			if (cur->_rightTag == LINK)
			{
				cur = cur->_right;
			}
			else
			{
				while (cur&&cur->_rightTag == THREAD)
				{
					cur = cur->_right;
				}
				if (cur != NULL)
				{
					cur = cur->_right;
				}		
			}
		}
		cout << endl;
	}

	//后序遍历 中序线索化二叉树
	void PostOder()
	{
		if (_root == NULL)
			return;
		Node* cur = _root;
		while (cur->_leftTag == LINK || cur->_rightTag == LINK)       //寻找第一个访问的结点
		{
			if (cur->_leftTag == LINK)
				cur = cur->_left;
			else if (cur->_rightTag==LINK)
			    cur = cur->_right;		
		}
		cout << cur->_data << " ";           //访问第一个结点
		Node* p = NULL;
		while ((p=Parent(cur))&&p!=NULL)
		{
			if (p->_right == cur||p->_rightTag==THREAD)  //如果已经访问完了右子树,或者右子树是线索
				cur = p;                                  //cur跳转到父节点
			else
			{
				cur =p->_right;
				while (cur->_leftTag == LINK                //找到右子树下第一个访问的结点
					|| cur->_rightTag == LINK)   
				{
					if (cur->_leftTag == LINK)
						cur = cur->_left;
					else if (cur->_rightTag==LINK)
						cur = cur->_right;
				}			
			}
			cout << cur->_data << " ";
		}
		cout << endl;
	}

protected:
	//中序线索化二叉树
	void InThreadTree()
	{
		Node* prev = NULL;
		_InThreadTree(_root, prev);
		prev->_rightTag = THREAD;
	}

	Node* Parent(Node* root)          //寻找root结点的父节点
	{
		if (root == NULL || root == _root) //如果root是空结点或根结点，则返回NULL
			return NULL;
		Node* cur =root;
		while (cur->_leftTag != THREAD)
			cur = cur->_left;
		if (cur->_left != NULL)
		{
			for (cur = cur->_left;
				cur&&cur->_left!=root&&cur->_right!= root;
				cur = cur->_right);
		}
		if (cur == NULL|| cur->_left == NULL)
		{
			cur = root;
			while (cur->_rightTag != THREAD)
			{
				cur = cur->_right;
			}
			for (cur = cur->_right;
				cur&&cur->_left != root&&cur->_right != NULL;
				cur=cur->_left);
		}
		return cur;
	}

	Node* Frist(Node* root)        //寻找以root为根节点的树,中序遍历下的第一个结点
	{
		if (root == NULL)
			return NULL;
		Node* cur = root;
		while (cur->_leftTag != THREAD)
		{
			cur = cur->_left;
		}
		return cur;
	}

	Node* Next(Node *root)          //寻找中序遍历下root的后继结点
	{
		if (root == NULL)
			return NULL;
		Node* cur = root;
		if(cur->_rightTag ==THREAD)
			return cur->_right;                   //直接返回后继
		return Frist(cur->_right);                 //返回右子树下访问的第一个结点
	}

	Node* Last(Node *root)         //寻找以root为根节点的树,中序遍历下的最后一个结点
	{
		if (root == NULL)
			return NULL;
		Node* cur = root;
		while (cur->_right==LINK)
			cur = cur->_right;
		return cur;
	}

	Node* Prior(Node *root)        //寻找中序遍历下root的前继结点
	{
		if (root == NULL)
			return NULL;
		Node* cur = root;
		if (cur->_leftTag == THREAD)
			return cur->_left;              //直接返回前继几点
		return Last(cur->_left);            //返回左子树下最后一个访问的结点
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