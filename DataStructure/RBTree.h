#pragma once

enum {BLACK,RED};

template<typename K,typename V>
struct RBTreeNode
{
	int _color;
	K _key;
	V _value;
	RBTreeNode<K, V> *_left;
	RBTreeNode<K, V> *_right;
	RBTreeNode<K, V> *_parent;
	RBTreeNode(K key, V value)
		:_color(RED)               //默认结点是红色
		, _key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}

};


template<typename K,typename V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	RBTree(const RBTree<K, V>& tree)
	{
		_Copy(tree._root, _root);
	}

	RBTree<K, V>& operator=(const RBTree<K, V>& tree)
	{
		if (this != &tree)
		{
			RBTree<K, V> tmp(tree);
			swap(_root, tmp._root);
		}
		return *this;
	}

	~RBTree()
	{
		_Destory(_root);
	}

	bool Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
				cur = cur->_left;
			else if (cur->_key < key)
				cur = cur->_right;
			else
				return true;
		}
		return false;
	}

	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)    //如果插入的结点是根节点
		{
			_root = new Node(key, value);
			_root->_color = BLACK;
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				return false;                //要插入的结点已经存在
		}
		cur = new Node(key, value);
		if (parent->_key>key)
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;

		while (cur != _root&&parent->_color == RED)      //父节点是红色的需要调整
		{
			Node* grand = parent->_parent;      //找到祖父结点
			if (parent == grand->_left)
			{
				Node* uncle = grand->_right;     //找到叔叔结点
				if (uncle&&uncle->_color == RED)      //叔叔结点是红色
				{
					grand->_color = RED;
					parent->_color = BLACK;
					uncle->_color = BLACK;
					cur = grand;
					parent = cur->_parent;      //红色结点上移，需要继续判断
				}
				else            //叔叔结点不存在或为黑色结点
				{
					//先处理双旋的情况
					if (cur == parent->_right)    //如果cur是父亲的右孩子
					{
						RotateL(parent);         //先对parent进行左旋
						parent = cur;
					}

					//如果cur是parent的右孩子，则经过旋转之后现在就变成了以grand右旋的情况
					RotateR(grand);        //对祖父结点进行右旋
					parent->_color = BLACK;
					grand->_color = RED;
					break;      //这时候就已经平衡了
				}
			}
			else
			{
				Node* uncle = grand->_left;
				if (uncle&&uncle->_color == RED)     //如果叔叔存在且为红色
				{
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grand->_color = RED;        //红色结点上移，继续向上判断
					cur = grand;
					parent = cur->_parent;
				}
				else
				{
					//如果cur是parent的左孩子，则需要先进行右旋将双旋转换成左旋的情况
					if (cur == parent->_left)
					{
						RotateR(parent);
						parent = cur;
					}

					//在对祖父进行左旋
					RotateL(grand);
					parent->_color = BLACK;
					grand->_color = RED;
					break;
				}
			}
		}
		_root->_color = BLACK;     //把根节点置成黑色
		return true;
	}

	bool Remove(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		Node* del = NULL;

		while (cur)            //寻找要删除的结点
		{
			if (cur->_key > key)
				cur = cur->_left;
			else if (cur->_key < key)
				cur = cur->_right;
			else
				break;
		}

		if (cur == NULL)
			return false;           //没找到结点，删除失败
		//如果要删除的结点有两个孩子,则先转化成只有一个孩子或者没有孩子的情况
		if (cur->_left != NULL&&cur->_right != NULL)
		{
			Node* minRight = cur->_right;       //记录要删除的结点在的右子树的最左结点  
			while (minRight->_left)
			{
				minRight = minRight->_left;
			}

			//采用交换删除
			cur->_key = minRight->_key;
			cur->_value = minRight->_value;

			cur = minRight;         //cur指向要删除的结点
		}
		parent = cur->_parent;       //找到要删除的结点的父亲
		del = cur;                   //del指向要删除的结点
		if (cur->_left == NULL)        //要删除的结点的左孩子为空或者不存在
		{
			if (cur == _root)           //如果要删除的结点是根节点，则删除之后就已经平衡
			{
				_root = cur->_right;
				if (cur->_right)                  //如果根节点的右孩子不为空的话，则它一定是红色
				{
					_root->_parent = NULL;
					_root->_color = BLACK;
				}
				delete del;
				return true;
			}
			//将要删除的结点的孩子链接到要删除的结点的父亲下面
			if (parent->_left == cur)             //cur是parent的左孩子,要删除的结点不是根节点，则一定有父亲
				parent->_left = cur->_right;
			else                                  //cur是parent的右孩子，要删除的结点不是父亲，则一定有父亲
				parent->_right = cur->_right;
			if (cur->_right)                        //如果要删除的不是叶子结点的话
				cur->_right->_parent = parent;
			cur = del->_right;                   //让cur指向要删除结点的孩子
		}
		else
		{
			if (cur == _root)          //要删除的结点是根节点,则根节点的左子树一定存在
			{
				_root = cur->_left;
				_root->_parent = NULL;
				_root->_color = BLACK;       //根节点的左孩子不为空的话它一定是红色
				delete del;
				return true;
			}
			if (parent->_left == cur)                     //要删除的不是根节点，则parent一定存在
				parent->_left = cur->_left;
			else
				parent->_right = cur->_left;
			cur->_left->_parent = parent;             //cur的左孩子一定存在
			cur = del->_left;                        //让cur指向要删除结点的孩子
		}

		if (del->_color == RED)           //如果要删除的结点就是红色的，则删除后已经平衡
		{
			delete del;
			return true;
		}

		if (del->_color == BLACK&&cur&&cur->_color == RED)   //如果要删除的结点是黑色的，且它的孩子是红色的，将孩子改为黑色就平衡了
		{
			cur->_color = BLACK;
			delete del;
			return true;
		}

		//要删除的结点是黑色的，且它的孩子为NULL或者是黑色的
		while (parent)
		{
			if (parent->_left == cur)            //如果要删除的结点是父亲结点的左孩子
			{
				Node* subR = parent->_right;       //subR是parent的右孩子,且一定存在
				if (subR->_color == RED)       //parent的右孩子是红色的
				{
					RotateL(parent);          //对parent进行左旋，旋转之后染色，因为cur路径上仍然少一个结点，所以继续检索cur
					parent->_color = RED;
					subR->_color = BLACK;
				}
				else                            //如果subR是黑色的   
				{
					Node* subRL = subR->_left;
					Node* subRR = subR->_right;

					if (parent->_color == BLACK && 
						((subRL == NULL&&subRR == NULL) ||
						(subRL&&subRR&&subRL->_color == BLACK&&subRR->_color == BLACK)))       //如果parent以及subR和subR的孩子都为空
					{
						subR->_color = RED;     //使得subR这条路径上减少一个黑色结点，再判断向上parent
						cur = parent;
						parent = cur->_parent;
					}
					else
					{
						if (parent->_color == RED)            //如果父节点是红色
						{
							if ((subRL == NULL&&subRR == NULL) ||
								(subRL&&subRR&&subRL->_color == BLACK&&subRR->_color == BLACK))
							{
								parent->_color = BLACK;         //将父节点变为黑色
								subR->_color = RED;             //右孩子变为红，相当于在cur这条路径上曾加了一个黑色
								break;            //满足平衡，直接退出
							}
						}

						if (subRL->_color = RED)        //如果subRL为红色，先对subR进行右旋转换为左单选的情况
						{
							RotateR(subR);
							subR = subRL;                //让subR指向旋转之后新的父节点
						}

						//到这就是左单旋的情况
						RotateL(parent);           //对parent进行做单选
						if (parent->_color == RED)   //将旋转之后新的父节点subR变为与原来父节点一样的颜色
							subR->_color = RED;
						else
							subR->_color = BLACK;

						parent->_color = BLACK;       //将原来父节点染成黑色的
						subR->_right->_color = BLACK;   //因为subR的右子树上少了一颗黑色结点，所以要将红色染黑
						break;            //树已经平衡
					}
				}
			}
			else
			{
				Node* subL = parent->_left;       //要删除的结点在parent的右子树，且一定存在
				if (subL->_color == RED)       //parent的左孩子是红色的，则通过旋转让parent左右两边黑色结点个数相对
				{
					RotateR(parent);        //让paret右旋
					//让左右两边黑色结点相同，都少一个结点，再继续判断cur，
					parent->_color = RED;
					subL->_color = BLACK;
				}
				else             //如果parent的左孩子是 黑色的
				{
					Node* subLR = subL->_right;
					Node* subLL = subL->_left;
					//如果父节点与subL的孩子都是黑色的,subLL的孩子要么全为空，要么全为黑
					if (parent->_color == BLACK && 
						((subLL == NULL&&subLR == NULL) ||
						(subLL&&subLR&&subLL->_color == BLACK&&subLR->_color == BLACK)))
					{
						subL->_color = RED;     //使得subL这条路径上少一个黑色接点，再继续向上判断
						cur = parent;
						parent = cur->_parent;
					}
					else
					{
						if (parent->_color == RED)      //如果父亲结点是红色结点
						{
							if ((subLL == NULL&&subLR == NULL)|| 
								(subLL&&subLR&&subLL->_color == BLACK&&subLR->_color == BLACK))
							{
								parent->_color = BLACK;      //让cur这条路径上的黑色接点增加一个
								subL->_color = RED;          //subL这条路径上的黑色接点个数不变
								break;
							}
						}

						if (subLR->_color == RED)       //subL的右孩子为红，先对subL进行左旋
						{
							//将双旋变为右单旋的情况
							RotateL(subL);
							subL = subLR;        //让subL指向旋转之后的父节点
						}

						RotateR(parent);       //对parent进行右单旋
						//将旋转之后新的父节点subL变为parent的颜色
						if (parent->_color == RED)
							subL->_color = RED;
						else
							subL->_color = BLACK;

						parent->_color = BLACK;
						subL->_left->_color = BLACK;
						break;
					}
				}
			}
		}
        _root->_color = BLACK;
		delete del;
		return true;
	}

	bool IsBlance()
	{
		if (_root == NULL)           //如果是空树，则就是平衡的
			return true;

		if (_root->_color == RED)     //如果树的根节点是红色的，则这棵树就不是平衡的
			return false;

		int count = 0;
		//用count统计这棵树最左路中黑色结点的个数，作为与其他路径比较的基准
		Node* cur = _root;
		while (cur)
		{
			if (cur->_color == BLACK)
				count++;
			cur = cur->_left;
		}
		int num=0;
		return _IsBlance(_root,num,count);
	}
protected:
	bool _IsBlance(Node* root,int num,const int& count)
	{
		if (root == NULL)
		{
			return num==count;
		}

		//如果这个结点是红色的，就去判断他的父亲是什么颜色,如果这个结点是红色的，则它一定不是根节点
		if (root->_color == RED&&root->_parent->_color==RED)   
			return false;
		if (root->_color == BLACK)
			num++;

		return _IsBlance(root->_left,num,count)&&_IsBlance(root->_right,num,count);
	}

	void _Copy(Node* root,Node* &newroot)
	{
		if (root == NULL)
			return;
		Node* cur = new Node(root->_key,root->_value);
		cur->_color = root->_color;
		
		newroot = cur;
		cur->_parent = newroot;

		_Copy(root->_left,cur->_left);
		_Copy(root->_right,cur->_right);
	}

	void _Destory(Node* root)
	{
		if (root == NULL)
			return;
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}

	void RotateL(Node* parent)         //左旋
	{
		Node* ppNode = parent->_parent;
		Node* subR = parent->_right;

		parent->_right = subR->_left;
		if (subR->_left)
			subR->_left->_parent = parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
			_root->_parent = NULL;
		}
		else
		{         //与上层进行链接
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
			subR->_parent = ppNode;
		}
	}

	void RotateR(Node* parent)          //右旋
	{
		Node* ppNode = parent->_parent;
		Node* subL = parent->_left;

		parent->_left = subL->_right;
		if (subL->_right)
			subL->_right->_parent = parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (ppNode == NULL)    
		{
			_root = subL;
			_root->_parent= NULL;
		}
		else                           //与上层结点链接
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
			subL->_parent = ppNode;
		}
	}
private:
	Node* _root;
};