#pragma once
#include<queue>
using namespace std;
template<typename K,typename V>
struct AVLTreeNode
{
	K _key;
	V _value;
	int _bf;           //ƽ�����ӣ��������ĸ߶ȼ�ȥ�������ĸ߶�
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
		while (cur)                        //Ѱ��Ҫ�����λ��
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
				return false;             //����Ѿ����ھͲ�����
		}

		cur = new Node(key,value);
		if (parent!=NULL)                 //�����ǿ���
		{
			if (parent->_key < key)
				parent->_right = cur;
			else
				parent->_left = cur;
			cur->_parent = parent;
		}
		else                             //���ǿ���
		{
			_root = cur;
			return true;
		}

		if (cur == parent->_left)        //��������λ���Ǹ��ڵ������
			parent->_bf--;
		else
			parent->_bf++;               //��������λ���Ǹ��ڵ���Һ���

		while (parent != NULL)             //���Ų���λ�õ����ڵ���ݣ�����ƽ�����Ӳ�����Ľ��
		{
			if (parent->_bf == 0)          //��������֮��parent������ĸ߶�û�䣬�����ʱ����AVL��
			{
				return true;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)  //parent���������AVL,��Ϊparent�ĸ߶ȷ����仯����Ҫ���ϲ������Ƚ��
			{
				Node* ppNode = parent->_parent;      //����parent�ĸ��ڵ� 
				if (ppNode != NULL)
				{
					if (ppNode->_left == parent)      //ppNode���������߶ȷ����仯
						ppNode->_bf--;
					else                              //ppNode���������߶ȷ����仯
						ppNode->_bf++;
				}
				parent = parent->_parent;      //��ǰ������AVL�������Լ��������ж�
			}
			else          //�����ǰ��������AVL������ͽ�����ת�ָ�ƽ��
			{
				if (parent->_bf==2)          //���parent����������
				{
					if (parent->_right->_bf == 1)      //parentһ������Ҷ�ӽڵ㣬�������ĺ��Ӳ�Ϊ��
						RotateL(parent);             //��Ϊ������parentһ�������������ߣ����е�����
					else                       //parent���������ߣ����ĺ����������ߣ�����˫��
						RotateRL(parent);
				}
				else if(parent->_bf==-2)         //parent���������߶ȸ�
				{
					if (parent->_left->_bf == -1)  //parent���ӵ���������
						RotateR(parent);          //�ҵ���
					else                   //parent���������ߣ����ĺ����������ߣ�����˫��
						RotateLR(parent);
				}
				break;                      //��ת֮��������ĸ߶Ȼָ���ԭ���ĸ߶�
			}
		}
		return true;
	}


	bool Remove(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;
		Node* del = NULL;        //����ָ��Ҫɾ����λ��
		while (cur)                  //Ѱ��Ҫɾ����λ��
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

		if (cur == NULL)                 //ɾ��ʧ��
			return false;
		del = cur;
	//���Ҫɾ���Ľ�����������ӣ���Ѱ�������������㣬������ת����ֻ��һ�����ӻ�û�к��ӵ���ʽ
		if (cur->_left != NULL&&cur->_right != NULL)
		{
			cur = cur->_right;          //cur���Һ���һ����Ϊ��
			while (cur->_left)
			{
				cur = cur->_left;
			}

			del->_key = cur->_key;
			del->_value = cur->_value;

			del = cur;           //����֮����delָ�����Ҫɾ���Ľ��
		}

		parent = cur->_parent;        //��parentָ��Ҫɾ���Ľ��ĸ���
		if (cur->_left == NULL)       //Ҫɾ���Ľ�������Ϊ��,���߶�Ϊ��
		{
			if (parent == NULL)
			{
				_root = cur->_right;
				if (cur->_right)           //���cur���Һ��ӣ����Һ���ֱ������
					cur->_right->_parent = NULL;
			}
			else
			{
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
				if (cur->_right)                    //cur����������Ϊ��
					cur->_right->_parent = parent;
			}
			cur = del->_right;           //cur���µ�Ҫɾ������������
		}
		else                        //Ҫɾ���Ľ����Һ���Ϊ�գ����Ӳ�Ϊ��
		{
			if (parent == NULL)               //���Ҫɾ���Ľ����ͷ���
				_root = cur->_left;
			else                                    //ɾ���Ľ�㲻�Ǹ��ڵ㣬���������
			{
				if (parent->_left == cur)
					parent->_left = cur->_left;
				else
					parent->_right = cur->_left;
				cur->_left->_parent = parent;
			}
			cur = del->_left;            //cur���µ�Ҫɾ������������
		}

		//��ΪҪɾ���Ľ��֮��������ĸ߶Ȳ��䣬����Ҫ�޸ģ���Ҫ��parent�����ж��Ƿ�ƽ��
		while (parent)           //ֻҪparent��Ϊ�գ����п��ܲ�ƽ��
		{
			//����parent��ƽ������
			if (parent->_left == cur)   //ɾ������parent��������
				parent->_bf++;
			else
				parent->_bf--;

			if (parent->_bf == 1 || parent->_bf == -1) //ԭ��ƽ�⣬ɾ��һ�������߶Ȳ��䣬�������Ѿ�ƽ��
			{
				break;
			}

		    //ƽ������ԭ����Ϊ0��ɾ��һ���ߵ�����֮���Ϊ0����Ҫ��������Ѱ��
			if (parent->_bf != 0)    //ƽ������ԭ����Ϊ0���ұȽϰ���������ɾ��
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
					if (parent->_left == cur)   //ԭ��parent�ıȽϰ�����������ɾ��,��curָ��ϸߵ�����
						cur = parent->_right;
					else
						cur = parent->_left;
				}


				if (cur->_bf == 0)       //cur��ƽ������Ϊ0������ת�Ϳ���ƽ�⣬����parent������ĸ߶Ȳ���
				{
					if (parent->_bf < 0)  //parent���������ߣ���������ת
					{
						RotateR(parent);        //parent��ת��ָ�������ת�������¸�
						parent->_bf=1;         
						parent->_right->_bf= -1;
					}
					else          //��������ת
					{
						RotateL(parent);
						parent->_bf =-1;
						parent->_left->_bf =1;
					}
					break;
				}
				//���parent��ϸߵ�����ͬ�ţ�����е���ת����ת�Ժ����ĸ߶�û�лָ���ɾ��֮ǰ�ģ����Լ���������
				int d = parent->_bf - cur->_bf;   //��d���ж��Ƿ�ͬ�ţ�ͬ�ŵĻ�Ϊ1��-1����Ϊparent->_bfΪ2��-2��cur->_bfΪ1��-1
				if (d == 1 || d == -1)
				{
					if (d == 1)       //�������ߣ�Ҫ��������
						RotateL(parent);
					else
						RotateR(parent);      //�������ߣ���������
				}
				else              //Ҫ˫������,��Ϊ��ţ�����dΪ3��-3
				{
					if (d == 3)       //parent->_bfΪ2��cur->_bfΪ-1,����˫��
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

	void RotateL(Node *&parent)         //����
	{
		Node* subR = parent->_right; 
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent;      //����parent�ĸ��ڵ�

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
				ppNode->_left = subR;          //����ת��������ĸ��ڵ��������ϲ�����
			else
				ppNode->_right = subR;         //����ת��������ĸ��ڵ��������ϲ�����
			subR->_parent = ppNode;
		}
		parent->_bf = subR->_bf = 0;      //subR��parent�ֹ���ƽ��
		parent = subR;                   //��parent����ָ��������ĸ�
	}

	void RotateR(Node * &parent)       //�ҵ���
	{
		Node* subL = parent->_left;         
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;      //����parent�ĸ��ڵ�

		parent->_left = subLR;
		if (subLR != NULL)
			subLR->_parent = parent;

		subL->_right = parent;
		parent->_parent = subL;
		 
		if (ppNode == NULL)             //���parent�ǿ�
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;                 //����ת��������ĸ��ڵ��������ϲ�����
			else
				ppNode->_right = subL;                  //����ת��������ĸ��ڵ��������ϲ�����
			subL->_parent = ppNode;
		}
		parent->_bf = subL->_bf=0;        //parent��subL������ƽ��       
		parent = subL;                    //��parent����ָ��������ĸ�
	}

	void RotateLR(Node *&parent)       //����˫��
	{
		Node* tmp = parent->_left ;
		Node* tmp2 = parent;

		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int d1 = 0;
		int d2 = 0;
		if (subLR->_bf==1)        //�������������
			d1 =-1;
		if (subLR->_bf == -1)       //��������
			d2 = 1;
		
		RotateL(tmp);
		RotateR(tmp2);

		subL->_bf = d1;
		parent->_bf=d2;
		parent = subLR;          //��parent����ָ��������ĸ�
	}

	void RotateRL(Node* &parent)        //����˫��
	{
		Node* tmp = parent->_right;
		Node* tmp2 = parent;

		Node* subR = parent->_right;       //��¼subR��parent��ƽ������
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

		parent = subRL;         //��parent����ָ��������ĸ�
	}
private:
	Node* _root;
};