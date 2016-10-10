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
	
	//������� ���������� ������
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
	//������� ��2��
	void InOder()
	{
		Node* cur = NULL;
		for (cur = Frist(_root); cur != NULL; cur = Next(cur))
		{
			cout << cur->_data << " ";
		}
		cout << endl;
	}


	//�������   ����������������
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

	//������� ����������������
	void PostOder()
	{
		if (_root == NULL)
			return;
		Node* cur = _root;
		while (cur->_leftTag == LINK || cur->_rightTag == LINK)       //Ѱ�ҵ�һ�����ʵĽ��
		{
			if (cur->_leftTag == LINK)
				cur = cur->_left;
			else if (cur->_rightTag==LINK)
			    cur = cur->_right;		
		}
		cout << cur->_data << " ";           //���ʵ�һ�����
		Node* p = NULL;
		while ((p=Parent(cur))&&p!=NULL)
		{
			if (p->_right == cur||p->_rightTag==THREAD)  //����Ѿ���������������,����������������
				cur = p;                                  //cur��ת�����ڵ�
			else
			{
				cur =p->_right;
				while (cur->_leftTag == LINK                //�ҵ��������µ�һ�����ʵĽ��
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
	//����������������
	void InThreadTree()
	{
		Node* prev = NULL;
		_InThreadTree(_root, prev);
		prev->_rightTag = THREAD;
	}

	Node* Parent(Node* root)          //Ѱ��root���ĸ��ڵ�
	{
		if (root == NULL || root == _root) //���root�ǿս������㣬�򷵻�NULL
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

	Node* Frist(Node* root)        //Ѱ����rootΪ���ڵ����,��������µĵ�һ�����
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

	Node* Next(Node *root)          //Ѱ�����������root�ĺ�̽��
	{
		if (root == NULL)
			return NULL;
		Node* cur = root;
		if(cur->_rightTag ==THREAD)
			return cur->_right;                   //ֱ�ӷ��غ��
		return Frist(cur->_right);                 //�����������·��ʵĵ�һ�����
	}

	Node* Last(Node *root)         //Ѱ����rootΪ���ڵ����,��������µ����һ�����
	{
		if (root == NULL)
			return NULL;
		Node* cur = root;
		while (cur->_right==LINK)
			cur = cur->_right;
		return cur;
	}

	Node* Prior(Node *root)        //Ѱ�����������root��ǰ�̽��
	{
		if (root == NULL)
			return NULL;
		Node* cur = root;
		if (cur->_leftTag == THREAD)
			return cur->_left;              //ֱ�ӷ���ǰ�̼���
		return Last(cur->_left);            //���������������һ�����ʵĽ��
	}


	Node* _CreatTree(const T* a, size_t size, size_t& index, const T& invalid)
	{
		//����һ�Ŷ�����
		Node* root = NULL;
		if (index < size&&a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _CreatTree(a, size, ++index, invalid);
			root->_right = _CreatTree(a, size, ++index, invalid);
		}
		return root;
	}

	//����������������
	void _InThreadTree(Node* root, Node* &prev)
	{
		if (NULL == root)
			return;
		_InThreadTree(root->_left, prev);
		if (root->_left == NULL)                //������ǰ��
		{
			root->_leftTag = THREAD;
			root->_left = prev;
			prev = root;
		}
		if (prev != root&&prev->_right == NULL)      //���������
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