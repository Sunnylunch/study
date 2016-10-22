#pragma once
#include<stack>
using namespace std;
 template<typename K,typename V>
 struct AvlTreeNode
 {
	 K _key;
	 V _value;
	 int _bf;           //ƽ�����ӣ������������ĸ߶ȼ�ȥ�������ĸ߶�
	 AvlTreeNode<K, V>  *_left;
	 AvlTreeNode<K, V>  *_right;
	 AvlTreeNode(const K& key,const V& value=V())
		 :_key(key)
		 , _value(value)
		 , _bf(0)
		 , _left(NULL)
		 , _right(NULL)
	 {}
 };


 template<typename K,typename V>
 class AvlTree
 {
	 typedef AvlTreeNode<K, V> Node;
 public:
	 AvlTree()
		 :_root(NULL)
	 {}
	 AvlTree(K* a,size_t size)
		 :_root(NULL)
	 {
		 for (int i = 0; i < (int)size; i++)
		 {
			 Insert(a[i]);
		 }
	 }

	 ~AvlTree()
	 {
		 _Destory(_root);
	 }

	 bool Insert(const K& k)
	 {
		 Node* parent = NULL;
		 Node* cur= _root;
		 stack<Node*> s;
		 while (cur != NULL)
		 {
			 s.push(cur);
			 if (k < cur->_key)
				 cur = cur->_left;
			 else if (k>cur->_key)
				 cur = cur->_right;
			 else
				 return false;                 //�ҵ��򲻲���
		 }
		 cur = new Node(k);                    //����һ���½��
		 if (s.empty())                        //���ջΪ��
		 {
			 _root = cur;                       //�½ڵ�ֱ�Ӳ���
			 return true;
		 }
		 parent = s.top();           //��parentָ���������λ�õĸ���
		 if (k>parent->_key)
		 {
			 parent->_right = cur;   //���Ҫ����Ľ����ڸ��ڵ�
		 }
		 else 
		 {
			 parent->_left = cur;     //���Ҫ����Ľ��С�ڸ��ڵ�
		 }
		 while (!s.empty())            //����ƽ�⻯
		 {
			 parent = s.top();         //��ջ���˳����ڵ�
			 s.pop();
			 if (parent->_left ==cur)   //���cur��parent�����ӣ���parent��ƽ�����Ӽ�һ
				 parent->_bf--;
			 else                      //���cur��parent�����ӣ���parent��ƽ�����Ӽ�һ
				 parent->_bf++;

			 if (parent->_bf == 0)       //������ڵ��ƽ������Ϊ0�����Ѿ�ƽ��,����ѭ��
				 break;
			 if (parent->_bf == 1 || parent->_bf == -1)      //������ڵ��ƽ�����ӵľ���ֵΪ1
				 cur = parent;                //��������ϻ��ݣ����츸�ڵ��ƽ��״̬
			 else                             //��Ҫ��ƽ�⻯����
			 {
				 int d = 0;            //��������˫��ת
				 if (parent->_bf < 0)  //�õ����ڵ��ƽ�����ӵ�����
					 d = -1;           
				 else
					 d = 1;
				 if (cur->_bf == d)    //������ڵ��ƽ��������dͬ�ţ���˵������������룬Ҫ����ת�ָ�
				 {
					 if (d == -1)            //���ڵ���������߶ȸߣ���������ת�ָ�
						 RotateRight(parent);
					 else                     //���ڵ���������߶ȸߣ���������ת�ָ�
						 RotateLeft(parent);

				 }
				 else            //�������ڲ���룬Ҫ˫��ת�ָ�
				 {
					 if (d == -1)    //���ڵ���������߶ȸߣ�������������
						 DoubleRotateLR(parent);
					 else             //���ڵ���������߶ȸߣ���������Һ���
						 DoubleRotateRL(parent);
				 }
				 //����ƽ���parent�ĸ߶Ƚ��ͣ��������Ͻ��л���
				 break;
			 }
		 }

		 if (!s.empty())          //���ջ��Ϊ�գ�����Ҫ������������
		 {
			 cur = s.top();
			 if (cur->_key > parent->_key)
				 cur->_left = parent;
			 else
				 cur->_right = parent;
		 }
		 else
			 _root = parent;                 //���ջΪ��,���������ڵ�
		 return true;
	 }

	 bool Remove(const K& k)            //ɾ��һ�����
	 {
		 int dd = 0;                   //���������ת֮�����ϲ�����ӹ�ϵ
		 int d = 0;
		 Node* tmp = NULL;          //���������游���
		 Node* cur = _root;
		 Node* del = NULL;
		 Node* parent = NULL;
		 stack<Node*> s;
		 while (cur != NULL)
		 {
			 s.push(cur);                //����Ӹ��ڵ㵽ɾ�����֮���·��
			 if (cur->_key < k)
				 cur = cur->_right;
			 else if (cur->_key>k)
				 cur = cur->_left;
			 else
				 break;
		 }
		 if (cur == NULL)
			 return false;                   //�Ҳ���ɾ��ʧ��
		 //�����ɾ���Ľ����������Ů������ת����һ����Ů�����
		 if (cur->_left != NULL&&cur->_right != NULL)
		 {
			 Node* minRight = cur->_right;       //minRight����cur����������Сֵ
			 while (minRight->_left)
			 {
				 s.push(minRight);
				 minRight = minRight->_left;
			 }
			 cur->_key = minRight->_key;
			 cur->_value = minRight->_value;
			 cur = minRight;         //��curָ��ɾ���Ľ��
			 s.push(cur);            //��Ҫɾ���Ľ����ջ
		 }
		 s.pop();                    //�׳�Ҫɾ���Ľ��
		 if (s.empty())               //���Ҫɾ�����Ǹ��ڵ�
		 {
			 if (cur->_left != NULL)
				 _root = cur->_left;
			 else
				 _root = cur->_right;
			 delete cur;
			 return true;
		 }

		 parent = s.top();           //parent����Ҫɾ�����ĸ��ڵ�
		 del = cur;                  //��ɾ���Ľ�㱣�浽del����
		 if (cur->_left != NULL)     //Ҫɾ���Ľ��ֻ��һ����Ů������������
		 {
			 parent = cur->_left;
			 cur = cur->_left;
		 }
		 else
		 {
			 parent = cur->_right;
			 cur = cur->_right;
		 }

		//����ƽ�⻯
		 while(!s.empty())
		 {
			 parent=s.top();           //parnet���游�ڵ�
			 s.pop();                  //�׳����ڵ�
			 if (parent->_left == cur)   //cur��parent��������,�������ڵ��ƽ������
				 parent->_bf++;
			 else
				 parent->_bf--;
			 if (!s.empty())             //���ջ��Ϊ��
			 {
			     tmp = s.top();        //tmp����cur���游���
				 if (tmp->_left == parent)     //dd��ʾ��ת�����ϲ�����ӷ���
					 dd = -1;                  //��ת֮�����ϲ�������
				 else
					 dd = 1;                    //��ת֮�����ϲ�������
			 }
			 else
				 dd = 0;                         //��ת֮�����ϲ�����

			 if (parent->_bf == 1 || parent->_bf == -1)   //ɾ�������ĸ߶Ȳ���
				 break;
			 if (parent!= 0)          //ԭ��parent�ĸ߶Ȳ�Ϊ0���ҽϰ�������������
			 {
				 if (parent->_bf < 0)      //����иߵ�������������
				 {
					 d = -1;
					 cur = parent->_left;    //curָ��ϸߵ�����
				 }
				 else                   //�ϸߵ�������������
				 {
					 d = 1;
					 cur = parent->_right;
				 }
				 if (cur->_bf == 0)          //����ϸߵ�����ƽ��������0,�����һ�ε���ת
				 {
					 if (d == -1)              //����ת,�ϸ�������������
						 RotateRight(parent);
					 else
						 RotateLeft(parent);   //����ת���ϸ�������������
					 break;                   //��ת���֮�����ĸ߶Ȳ��䣬��ֱ������ѭ��
				 }
				 if (cur->_bf==d) //����ϸ������븸�ڵ�ƽ������ͬ�ţ�����ת,��ת֮�����ĸ߶ȸı�
				 {
					 if (d == -1)              //����ת,�ϸ�������������
						 RotateRight(parent);
					 else
						 RotateLeft(parent);   //����ת���ϸ�������������
				 }
				 else              //˫��ת
				 {
					 if (d == -1)
						 DoubleRotateLR(parent);
					 else
						 DoubleRotateRL(parent);
				 }
				 //���ϲ��������
				 if (dd == -1)
					 tmp->_left = parent;
				 else if (dd == 1)
					 tmp->_right = parent;				 
			 }
			 cur = parent;      //cur���浱ǰparent,���ڻ���
		 }
		 if (s.empty())
			 _root = parent;
		 return true;
	 }

	 bool Find(const K& k)
	 {
		 Node* cur = _root;
		 while (cur)
		 {
			 if (k < cur->_key)
				 cur = cur->_left;
			 else if (k>cur->_key)
				 cur = cur->_right;
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
	 void _InOder(Node* root)
	 {
		 if (root == NULL)
			 return;
		 _InOder(root->_left);
		 cout << root->_key << " " << root->_bf << endl;
		 _InOder(root->_right);
	 }

	 void RotateLeft(Node *&ptr)                         //����ת
	 {
		 Node* subL= ptr;              //subLָ��ptr���
		 ptr = ptr->_right;            //��ptrָ���µĸ����
		 subL->_right = ptr->_left;    //��ptr�����������ӵ�subL����������
		 ptr->_left = subL;            //��subL��Ϊptr��������
		 ptr->_bf = 0;                 //��Ϊ����֮��ptr�����������߶���ͬ������ƽ������Ϊ0
		 subL->_bf = 0;                //subL�����������ĸ߶�Ҳ��ͬ��ƽ������ҲΪ0
	 }

	 void RotateRight(Node* &ptr)                        //����ת
	 {
		 Node* subR = ptr;            //subLָ��ptr
	     ptr = ptr->_left;            //ptrָ���µĸ��ڵ�
		 subR->_left = ptr->_right;   //ptr�����������ӵ�subR����������
		 ptr->_right = subR;           //��subR��Ϊ�¸���������
		 ptr->_bf = 0;                //����ƽ������
		 subR->_bf = 0;
	 }

	 void DoubleRotateLR(Node* &ptr)                    //˫��ת���������
	 {
		 Node* subL = ptr->_left;        //��subLָ��ptr������
		 Node* subR = subL->_right;      //��subRָ��subL���Һ��ӣ���ָ��ptr�����ӽ��

		 //�Ƚ������������ڲ����ת��Ϊ�����룬����˫��תת��Ϊ����ת
		 subL->_right = subR->_left;     //��subR�������ӵ�subL������
		 subR->_left = subL;             //��subR���³�Ϊ��

		 //����ƽ������
		 if (subR->_bf <= 0)     //subR���������߶Ȳ�С��������
			 subL->_bf = 0;      //��ΪsubL������������һ�㣬����ƽ������Ϊ0
		 else                    //subR���������߶ȸߣ�subR�������ĸ߶Ȳ���
			 subL->_bf =-1;       //��subL��������Ҫ����һ��

		 //�ٽ���������ת����ƽ����
		 ptr->_left = subR->_right;
		 subR->_right = ptr;

		 //����ƽ������
		 if (subR->_bf== -1)       //subR���������߶�С��������
			 ptr->_bf = 1;         //ptr������������,subRԭ��������������
		 else                      //subR���������ĸ߶Ȳ�С���������߶�
			 ptr->_bf = 0;         //subR���������߶Ȳ��䣬ptr������������
		 subR->_bf = 0;             //�µĸ��ڵ��ƽ������Ϊ0
		 ptr = subR;               //��ptrָ��ָ�ƽ�����µĸ�
	 }

	 void DoubleRotateRL(Node* &ptr)                   //˫��ת�����Һ���
	 {
		 Node* subR = ptr->_right;
		 Node* subL = subR->_left;

		 //�Ƚ������������ڲ����ת����������
 		 subR->_left = subL->_right;
		 subL->_right = subR;

		 //����ƽ������
		 if (subL->_bf == -1)  //subL���������߶�С��������
			 subR->_bf = 1;    //subR������������
		 else                  //subL���������߶Ȳ�С���������߶�
			 subR->_bf = 0;

		 //����
		 ptr->_right = subL->_left;
		 subL->_left = ptr;

		 //����ƽ������
		 if (subL->_bf <= 0)     //subL���������߶Ȳ������������߶�
			 ptr->_bf = 0;       //ptr�����������ƣ�subL���������߶�����
		 else
			 ptr->_bf = -1;       
		 subL->_bf = 0;
		 ptr = subL;              //��ptrָ��ָ�ƽ�����µĸ�
	 }
protected:
	void  _Destory(Node* root)
	{
		if (root == NULL)
			return;
		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
	}
private:
	AvlTree(const AvlTree<K,V>&);
	AvlTree<K,V>& operator=(const AvlTree<K,V>&);
private:
	 Node* _root;
 };