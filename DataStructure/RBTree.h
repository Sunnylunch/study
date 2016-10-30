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
		:_color(RED)               //Ĭ�Ͻ���Ǻ�ɫ
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
		if (_root == NULL)    //�������Ľ���Ǹ��ڵ�
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
				return false;                //Ҫ����Ľ���Ѿ�����
		}
		cur = new Node(key, value);
		if (parent->_key>key)
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;

		while (cur != _root&&parent->_color == RED)      //���ڵ��Ǻ�ɫ����Ҫ����
		{
			Node* grand = parent->_parent;      //�ҵ��游���
			if (parent == grand->_left)
			{
				Node* uncle = grand->_right;     //�ҵ�������
				if (uncle&&uncle->_color == RED)      //�������Ǻ�ɫ
				{
					grand->_color = RED;
					parent->_color = BLACK;
					uncle->_color = BLACK;
					cur = grand;
					parent = cur->_parent;      //��ɫ������ƣ���Ҫ�����ж�
				}
				else            //�����㲻���ڻ�Ϊ��ɫ���
				{
					//�ȴ���˫�������
					if (cur == parent->_right)    //���cur�Ǹ��׵��Һ���
					{
						RotateL(parent);         //�ȶ�parent��������
						parent = cur;
					}

					//���cur��parent���Һ��ӣ��򾭹���ת֮�����ھͱ������grand���������
					RotateR(grand);        //���游����������
					parent->_color = BLACK;
					grand->_color = RED;
					break;      //��ʱ����Ѿ�ƽ����
				}
			}
			else
			{
				Node* uncle = grand->_left;
				if (uncle&&uncle->_color == RED)     //������������Ϊ��ɫ
				{
					parent->_color = BLACK;
					uncle->_color = BLACK;
					grand->_color = RED;        //��ɫ������ƣ����������ж�
					cur = grand;
					parent = cur->_parent;
				}
				else
				{
					//���cur��parent�����ӣ�����Ҫ�Ƚ���������˫��ת�������������
					if (cur == parent->_left)
					{
						RotateR(parent);
						parent = cur;
					}

					//�ڶ��游��������
					RotateL(grand);
					parent->_color = BLACK;
					grand->_color = RED;
					break;
				}
			}
		}
		_root->_color = BLACK;     //�Ѹ��ڵ��óɺ�ɫ
		return true;
	}

	bool Remove(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		Node* del = NULL;

		while (cur)            //Ѱ��Ҫɾ���Ľ��
		{
			if (cur->_key > key)
				cur = cur->_left;
			else if (cur->_key < key)
				cur = cur->_right;
			else
				break;
		}

		if (cur == NULL)
			return false;           //û�ҵ���㣬ɾ��ʧ��
		//���Ҫɾ���Ľ������������,����ת����ֻ��һ�����ӻ���û�к��ӵ����
		if (cur->_left != NULL&&cur->_right != NULL)
		{
			Node* minRight = cur->_right;       //��¼Ҫɾ���Ľ���ڵ���������������  
			while (minRight->_left)
			{
				minRight = minRight->_left;
			}

			//���ý���ɾ��
			cur->_key = minRight->_key;
			cur->_value = minRight->_value;

			cur = minRight;         //curָ��Ҫɾ���Ľ��
		}
		parent = cur->_parent;       //�ҵ�Ҫɾ���Ľ��ĸ���
		del = cur;                   //delָ��Ҫɾ���Ľ��
		if (cur->_left == NULL)        //Ҫɾ���Ľ�������Ϊ�ջ��߲�����
		{
			if (cur == _root)           //���Ҫɾ���Ľ���Ǹ��ڵ㣬��ɾ��֮����Ѿ�ƽ��
			{
				_root = cur->_right;
				if (cur->_right)                  //������ڵ���Һ��Ӳ�Ϊ�յĻ�������һ���Ǻ�ɫ
				{
					_root->_parent = NULL;
					_root->_color = BLACK;
				}
				delete del;
				return true;
			}
			//��Ҫɾ���Ľ��ĺ������ӵ�Ҫɾ���Ľ��ĸ�������
			if (parent->_left == cur)             //cur��parent������,Ҫɾ���Ľ�㲻�Ǹ��ڵ㣬��һ���и���
				parent->_left = cur->_right;
			else                                  //cur��parent���Һ��ӣ�Ҫɾ���Ľ�㲻�Ǹ��ף���һ���и���
				parent->_right = cur->_right;
			if (cur->_right)                        //���Ҫɾ���Ĳ���Ҷ�ӽ��Ļ�
				cur->_right->_parent = parent;
			cur = del->_right;                   //��curָ��Ҫɾ�����ĺ���
		}
		else
		{
			if (cur == _root)          //Ҫɾ���Ľ���Ǹ��ڵ�,����ڵ��������һ������
			{
				_root = cur->_left;
				_root->_parent = NULL;
				_root->_color = BLACK;       //���ڵ�����Ӳ�Ϊ�յĻ���һ���Ǻ�ɫ
				delete del;
				return true;
			}
			if (parent->_left == cur)                     //Ҫɾ���Ĳ��Ǹ��ڵ㣬��parentһ������
				parent->_left = cur->_left;
			else
				parent->_right = cur->_left;
			cur->_left->_parent = parent;             //cur������һ������
			cur = del->_left;                        //��curָ��Ҫɾ�����ĺ���
		}

		if (del->_color == RED)           //���Ҫɾ���Ľ����Ǻ�ɫ�ģ���ɾ�����Ѿ�ƽ��
		{
			delete del;
			return true;
		}

		if (del->_color == BLACK&&cur&&cur->_color == RED)   //���Ҫɾ���Ľ���Ǻ�ɫ�ģ������ĺ����Ǻ�ɫ�ģ������Ӹ�Ϊ��ɫ��ƽ����
		{
			cur->_color = BLACK;
			delete del;
			return true;
		}

		//Ҫɾ���Ľ���Ǻ�ɫ�ģ������ĺ���ΪNULL�����Ǻ�ɫ��
		while (parent)
		{
			if (parent->_left == cur)            //���Ҫɾ���Ľ���Ǹ��׽�������
			{
				Node* subR = parent->_right;       //subR��parent���Һ���,��һ������
				if (subR->_color == RED)       //parent���Һ����Ǻ�ɫ��
				{
					RotateL(parent);          //��parent������������ת֮��Ⱦɫ����Ϊcur·������Ȼ��һ����㣬���Լ�������cur
					parent->_color = RED;
					subR->_color = BLACK;
				}
				else                            //���subR�Ǻ�ɫ��   
				{
					Node* subRL = subR->_left;
					Node* subRR = subR->_right;

					if (parent->_color == BLACK && 
						((subRL == NULL&&subRR == NULL) ||
						(subRL&&subRR&&subRL->_color == BLACK&&subRR->_color == BLACK)))       //���parent�Լ�subR��subR�ĺ��Ӷ�Ϊ��
					{
						subR->_color = RED;     //ʹ��subR����·���ϼ���һ����ɫ��㣬���ж�����parent
						cur = parent;
						parent = cur->_parent;
					}
					else
					{
						if (parent->_color == RED)            //������ڵ��Ǻ�ɫ
						{
							if ((subRL == NULL&&subRR == NULL) ||
								(subRL&&subRR&&subRL->_color == BLACK&&subRR->_color == BLACK))
							{
								parent->_color = BLACK;         //�����ڵ��Ϊ��ɫ
								subR->_color = RED;             //�Һ��ӱ�Ϊ�죬�൱����cur����·����������һ����ɫ
								break;            //����ƽ�⣬ֱ���˳�
							}
						}

						if (subRL->_color = RED)        //���subRLΪ��ɫ���ȶ�subR��������ת��Ϊ��ѡ�����
						{
							RotateR(subR);
							subR = subRL;                //��subRָ����ת֮���µĸ��ڵ�
						}

						//����������������
						RotateL(parent);           //��parent��������ѡ
						if (parent->_color == RED)   //����ת֮���µĸ��ڵ�subR��Ϊ��ԭ�����ڵ�һ������ɫ
							subR->_color = RED;
						else
							subR->_color = BLACK;

						parent->_color = BLACK;       //��ԭ�����ڵ�Ⱦ�ɺ�ɫ��
						subR->_right->_color = BLACK;   //��ΪsubR��������������һ�ź�ɫ��㣬����Ҫ����ɫȾ��
						break;            //���Ѿ�ƽ��
					}
				}
			}
			else
			{
				Node* subL = parent->_left;       //Ҫɾ���Ľ����parent������������һ������
				if (subL->_color == RED)       //parent�������Ǻ�ɫ�ģ���ͨ����ת��parent�������ߺ�ɫ���������
				{
					RotateR(parent);        //��paret����
					//���������ߺ�ɫ�����ͬ������һ����㣬�ټ����ж�cur��
					parent->_color = RED;
					subL->_color = BLACK;
				}
				else             //���parent�������� ��ɫ��
				{
					Node* subLR = subL->_right;
					Node* subLL = subL->_left;
					//������ڵ���subL�ĺ��Ӷ��Ǻ�ɫ��,subLL�ĺ���ҪôȫΪ�գ�ҪôȫΪ��
					if (parent->_color == BLACK && 
						((subLL == NULL&&subLR == NULL) ||
						(subLL&&subLR&&subLL->_color == BLACK&&subLR->_color == BLACK)))
					{
						subL->_color = RED;     //ʹ��subL����·������һ����ɫ�ӵ㣬�ټ��������ж�
						cur = parent;
						parent = cur->_parent;
					}
					else
					{
						if (parent->_color == RED)      //������׽���Ǻ�ɫ���
						{
							if ((subLL == NULL&&subLR == NULL)|| 
								(subLL&&subLR&&subLL->_color == BLACK&&subLR->_color == BLACK))
							{
								parent->_color = BLACK;      //��cur����·���ϵĺ�ɫ�ӵ�����һ��
								subL->_color = RED;          //subL����·���ϵĺ�ɫ�ӵ��������
								break;
							}
						}

						if (subLR->_color == RED)       //subL���Һ���Ϊ�죬�ȶ�subL��������
						{
							//��˫����Ϊ�ҵ��������
							RotateL(subL);
							subL = subLR;        //��subLָ����ת֮��ĸ��ڵ�
						}

						RotateR(parent);       //��parent�����ҵ���
						//����ת֮���µĸ��ڵ�subL��Ϊparent����ɫ
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
		if (_root == NULL)           //����ǿ����������ƽ���
			return true;

		if (_root->_color == RED)     //������ĸ��ڵ��Ǻ�ɫ�ģ���������Ͳ���ƽ���
			return false;

		int count = 0;
		//��countͳ�����������·�к�ɫ���ĸ�������Ϊ������·���ȽϵĻ�׼
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

		//����������Ǻ�ɫ�ģ���ȥ�ж����ĸ�����ʲô��ɫ,����������Ǻ�ɫ�ģ�����һ�����Ǹ��ڵ�
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

	void RotateL(Node* parent)         //����
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
		{         //���ϲ��������
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
			subR->_parent = ppNode;
		}
	}

	void RotateR(Node* parent)          //����
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
		else                           //���ϲ�������
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