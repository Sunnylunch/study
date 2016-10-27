#pragma once
#include<queue>
using namespace std;
template<typename K,typename V>
struct AVLTreeNode
{
	K _key;
	V _value;
	int _bf;           //平衡因子，右子树的高度减去左子树的高度
	AVLTreeNode<K, V> *_left;
	AVLTreeNode<K, V> *_right;
	AVLTreeNode<K, V> *_parent;
	AVLTreeNode(K key, V value)
		:_key(key)
		, _value(value)
		, _bf(0)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};


template<typename K,typename V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	AVLTree(const AVLTree<K,V>& tree)
		:_root(NULL)
	{
		_Copy(tree._root,_root);
	}

	AVLTree<K, V>& operator=(const AVLTree<K,V>& avl)
	{
		if (this != &avl)
		{
			AVLTree<K, V> tmp(avl);
			swap(_root,tmp._root);
		}
		return *this;
	}

 	~AVLTree()
	{
		_Destory(_root);
	}

	bool Insert(const K& key,const V& value)
	{
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)                        //寻找要插入的位置
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;             //如果已经存在就不插入
		}

		cur = new Node(key,value);
		if (parent!=NULL)                 //树不是空树
		{
			if (parent->_key < key)
				parent->_right = cur;
			else
				parent->_left = cur;
			cur->_parent = parent;
		}
		else                             //树是空树
		{
			_root = cur;
			return true;
		}

		if (cur == parent->_left)        //如果插入的位置是父节点的左孩子
			parent->_bf--;
		else
			parent->_bf++;               //如果插入的位置是父节点的右孩子

		while (parent != NULL)             //沿着插入位置到根节点回溯，查找平衡因子不满足的结点
		{
			if (parent->_bf == 0)          //表明插入之后parent这棵树的高度没变，因此这时就是AVL树
			{
				return true;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)  //parent这棵树满足AVL,因为parent的高度发生变化，还要向上查找祖先结点
			{
				Node* ppNode = parent->_parent;      //保存parent的父节点 
				if (ppNode != NULL)
				{
					if (ppNode->_left == parent)      //ppNode的左子树高度发生变化
						ppNode->_bf--;
					else                              //ppNode的右子树高度发生变化
						ppNode->_bf++;
				}
				parent = parent->_parent;      //当前树满足AVL树，所以继续向上判断
			}
			else          //如果当前树不满足AVL树，则就进行旋转恢复平衡
			{
				if (parent->_bf==2)          //如果parent的右子树高
				{
					if (parent->_right->_bf == 1)      //parent一定不是叶子节点，所以他的孩子不为空
						RotateL(parent);             //因为子树与parent一样都是右子树高，进行单左旋
					else                       //parent的右子树高，它的孩子左子树高，右左双旋
						RotateRL(parent);
				}
				else if(parent->_bf==-2)         //parent的左子树高度高
				{
					if (parent->_left->_bf == -1)  //parent孩子的左子树高
						RotateR(parent);          //右单旋
					else                   //parent的左子树高，它的孩子右子树高，左右双旋
						RotateLR(parent);
				}
				break;                      //旋转之后这棵树的高度恢复成原来的高度
			}
		}
		return true;
	}


	bool Remove(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;
		Node* del = NULL;        //用来指向要删除的位置
		while (cur)                  //寻找要删除的位置
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				cur = cur->_left;
			}
			else
				break;
		}

		if (cur == NULL)                 //删除失败
			return false;
		del = cur;
	//如果要删除的结点有两个孩子，则寻找右子树最左结点，将问题转换成只有一个孩子或没有孩子的形式
		if (cur->_left != NULL&&cur->_right != NULL)
		{
			cur = cur->_right;          //cur的右孩子一定不为空
			while (cur->_left)
			{
				cur = cur->_left;
			}

			del->_key = cur->_key;
			del->_value = cur->_value;

			del = cur;           //交换之后让del指向这个要删除的结点
		}

		parent = cur->_parent;        //让parent指向要删除的结点的父亲
		if (cur->_left == NULL)       //要删除的结点的左孩子为空,或者都为空
		{
			if (parent == NULL)
			{
				_root = cur->_right;
				if (cur->_right)           //如果cur有右孩子，则右孩子直接做根
					cur->_right->_parent = NULL;
			}
			else
			{
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
				if (cur->_right)                    //cur的右子树不为空
					cur->_right->_parent = parent;
			}
			cur = del->_right;           //cur更新到要删除结点的右子树
		}
		else                        //要删除的结点的右孩子为空，左孩子不为空
		{
			if (parent == NULL)               //如果要删除的结点是头结点
				_root = cur->_left;
			else                                    //删除的结点不是根节点，则进行链接
			{
				if (parent->_left == cur)
					parent->_left = cur->_left;
				else
					parent->_right = cur->_left;
				cur->_left->_parent = parent;
			}
			cur = del->_left;            //cur更新到要删除结点的左子树
		}

		//因为要删除的结点之后的子树的高度不变，不需要修改，需要从parent向上判断是否平衡
		while (parent)           //只要parent不为空，就有可能不平衡
		{
			//调整parent的平衡因子
			if (parent->_left == cur)   //删除的是parent的左子树
				parent->_bf++;
			else
				parent->_bf--;

			if (parent->_bf == 1 || parent->_bf == -1) //原来平衡，删除一个后树高度不变，整棵树已经平衡
			{
				break;
			}

		    //平衡因子原来不为0，删除一个高的子树之后变为0，需要继续向上寻找
			if (parent->_bf != 0)    //平衡因子原来不为0，且比较矮的子树被删除
			{
				if (cur == NULL)
				{
					if (parent->_left == NULL)
						cur = parent->_right;
					else
						cur = parent->_left;
				}
				else
				{
					if (parent->_left == cur)   //原来parent的比较矮的左子树被删除,让cur指向较高的子树
						cur = parent->_right;
					else
						cur = parent->_left;
				}


				if (cur->_bf == 0)       //cur的平衡因子为0，单旋转就可以平衡，而且parent这棵树的高度不变
				{
					if (parent->_bf < 0)  //parent的左子树高，进行右旋转
					{
						RotateR(parent);        //parent旋转后指向这棵旋转子树的新根
						parent->_bf=1;         
						parent->_right->_bf= -1;
					}
					else          //进行左旋转
					{
						RotateL(parent);
						parent->_bf =-1;
						parent->_left->_bf =1;
					}
					break;
				}
				//如果parent与较高的子树同号，则进行单旋转，旋转自后树的高度没有恢复成删除之前的，所以继续向上找
				int d = parent->_bf - cur->_bf;   //用d来判断是否同号，同号的话为1或-1，因为parent->_bf为2或-2，cur->_bf为1或-1
				if (d == 1 || d == -1)
				{
					if (d == 1)       //右子树高，要进行左旋
						RotateL(parent);
					else
						RotateR(parent);      //左子树高，进行右旋
				}
				else              //要双旋处理,因为异号，所以d为3或-3
				{
					if (d == 3)       //parent->_bf为2，cur->_bf为-1,右左双旋
						RotateRL(parent);
					else
						RotateLR(parent);
				}
			}
			cur = parent;
			parent = parent->_parent;
		}
		delete del;
		return true;
	}

	bool Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
				cur = cur->_right;
			else if (cur->_key>key)
				cur = cur->_left;
			else
				return true;
		}
		return false;
	}

	void InOder()
	{
		_InOder(_root);
	}
protected:
	void _Copy(Node* root,Node *&newroot)
	{
		if (root == NULL)
			return;
		Node* node = new Node(root->_key, root->_value);
		node->_bf = root->_bf;
		newroot = node;
		node->_parent = newroot;

		_Copy(root->_left,newroot->_left);
		_Copy(root->_right, newroot->_right);
	
	}

	void _Destory(Node* root)
	{
		if (root == NULL)
			return;
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}

	void _InOder(Node* root)
	{
		if (root == NULL)
			return;
		_InOder(root->_left);
		cout << root->_key << " " << root->_bf << endl;
		_InOder(root->_right);
	}

	void RotateL(Node *&parent)         //左单旋
	{
		Node* subR = parent->_right; 
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent;      //保存parent的父节点

		parent->_right = subRL;
		if (subRL != NULL)
			subRL->_parent = parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;          //让旋转的这棵树的根节点重新与上层链接
			else
				ppNode->_right = subR;         //让旋转的这棵树的根节点重新与上层链接
			subR->_parent = ppNode;
		}
		parent->_bf = subR->_bf = 0;      //subR和parent又归于平衡
		parent = subR;                   //让parent重新指向这棵树的根
	}

	void RotateR(Node * &parent)       //右单旋
	{
		Node* subL = parent->_left;         
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;      //保存parent的父节点

		parent->_left = subLR;
		if (subLR != NULL)
			subLR->_parent = parent;

		subL->_right = parent;
		parent->_parent = subL;
		 
		if (ppNode == NULL)             //如果parent是空
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;                 //让旋转的这棵树的根节点重新与上层链接
			else
				ppNode->_right = subL;                  //让旋转的这棵树的根节点重新与上层链接
			subL->_parent = ppNode;
		}
		parent->_bf = subL->_bf=0;        //parent与subL又趋于平衡       
		parent = subL;                    //让parent重新指向这棵树的根
	}

	void RotateLR(Node *&parent)       //左右双旋
	{
		Node* tmp = parent->_left ;
		Node* tmp2 = parent;

		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int d1 = 0;
		int d2 = 0;
		if (subLR->_bf==1)        //右子树子树变高
			d1 =-1;
		if (subLR->_bf == -1)       //左子树高
			d2 = 1;
		
		RotateL(tmp);
		RotateR(tmp2);

		subL->_bf = d1;
		parent->_bf=d2;
		parent = subLR;          //让parent重新指向这棵树的根
	}

	void RotateRL(Node* &parent)        //右左双旋
	{
		Node* tmp = parent->_right;
		Node* tmp2 = parent;

		Node* subR = parent->_right;       //记录subR和parent的平衡因子
		Node* subRL = subR->_left;
		int d1 = 0;
		int d2 = 0;
		if (subRL->_bf == -1)
			d1 = 1;
		if (subRL->_bf == 1)
			d2 = -1;

		RotateR(tmp);
		RotateL(tmp2);

		subR->_bf = d1;
		parent->_bf = d2;

		parent = subRL;         //让parent重新指向这棵树的根
	}
private:
	Node* _root;
};