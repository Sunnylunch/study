#pragma once

 template<typename T>
 struct ThreadTreeNode
 {
	 int ltag;
	 int rtag;
	 T _data;
	 ThreadTreeNode<T> * leftchild;
	 ThreadTreeNode<T>* rightchild;
	 ThreadTreeNode(const T& data=T())
		 :ltag(0)
		 ,rtag(0)
		 , leftchild(NULL)
		 , rightchild(NULL)
		 , _data(data)
	 {}
 };


 template<typename T>
 class ThreadTree
 {
	 typedef ThreadTreeNode<T> Node;
 public:
	 ThreadTree()
		 :_root(NULL){}

	 ThreadTree(const T* a,size_t size,const T& invalid)
	 {
		 size_t index = 0;
		 _root = _CreatTree(a,size,index,invalid);  //����������

		 Node* prev = NULL;  //ǰ�����ָ��
         //����������������
		 if (_root != NULL)
		 {
			 CreatInThread(_root, prev);    //������������
			 prev->rightchild = NULL;       //�����һ�����ĺ����Ϊ��
			 prev->rtag = 1;                //rtag=1��ʾָ����
		 }
	 }

	 Node* Frist(Node* cur)    //Ѱ����curΪ���������ĵ�һ�����
	 {
		 if (cur== NULL)
			 return NULL;
		 while (cur->ltag == 0)
			 cur=cur->leftchild;
		 return cur;
	 }

	 Node* Last(Node* cur)     //Ѱ����curΪ�������������һ�����
	 {
		 if (cur == NULL)
			 return NULL;
		 while (cur->rtag==0)
		 {
			 cur = cur->rightchild;
		 }
		 return cur;
	 }

	 Node* Prior(Node* cur)   //��curǰ�����
	 {
		 if (cur == NULL)
			 return NULL;
		 if (cur->ltag == 1)
			 return cur->leftchild;
		 return Last(cur->leftchild);
	 }

	 Node* Next(Node* cur)     //�Һ�̽��
	 {
		 if (cur == NULL)
			 return NULL;
		 if (cur->rtag == 1)
			 return cur->rightchild;
		 return  Frist(cur->rightchild);
	 }

	 void PrevOder()            //�������
	 {
		 if (NULL == _root)
			 return ;
		 Node* cur = _root;
		 while (cur != NULL)
		 {
			 cout << cur->_data << " ";     //���ʸ��ڵ�
			 if (cur->ltag == 0)
			 {
				 cur = cur->leftchild;
			 }
			 else if (cur->rtag==0)
			 {
				 cur = cur->rightchild;
			 }
			 else
			 {
				 while (cur&&cur->rtag == 1)
					 cur = cur->rightchild;
				 if (cur != NULL)
					 cur = cur->rightchild;
			 }
		 }
		 cout << endl;
	 }

	 void InOder()
	 {
		 if (_root == NULL)
			 return;
		 Node* cur = NULL;
		 for (cur = Frist(_root); cur != NULL; cur = Next(cur))
		 {
			 cout << cur->_data << " ";
		 }
		 cout << endl;
	 }

	 void PostOder()
	 {
		 if (_root == NULL)
			 return ;
		 Node* cur = _root;
		 Node* p = NULL;
		 while (cur->ltag == 0 || cur->rtag == 0)  //Ѱ�Һ���ĵ�һ�����
		 {
			 if (cur->ltag == 0)
				 cur = cur->leftchild;
			 else if (cur->rtag==0)
			 {
				 cur = cur->rightchild;
			 }
		 }
		 cout << cur->_data << " ";
		 while ((p=Parent(cur))!=NULL)
		 {
			 if (p->rightchild == cur || p->rtag == 1)
				 cur = p;
			 else
			 {
				 cur = p->rightchild;
				 while (cur->ltag == 0 || cur->rtag == 0)  //Ѱ�Һ���ĵ�һ�����
				 {
					 if (cur->ltag == 0)
						 cur = cur->leftchild;
					 else if (cur->rtag==0)
					 {
						 cur = cur->rightchild;
					 }
				 }
			 }	
			 cout << cur->_data << " ";
		 }
		 cout << endl;
	 }

	 Node* Parent(Node *p)
	 {
		 if (p == NULL || p == _root)            //����ǿս�����ڵ㣬�򸸽��Ϊ��
			 return NULL;
		 Node* cur = p;
		 while (cur->ltag == 0)
			 cur = cur->leftchild;
		 if (cur->leftchild != NULL)
		 {
			 for (cur = cur->leftchild;
				 cur != NULL&&cur->leftchild != p&&cur->rightchild != p;
				 cur = cur->rightchild);        //����·Ѱ��
		 }
		 if (cur == NULL || cur->leftchild == NULL)  //���û�ҵ�
		 {
			 cur = p;
			 while (cur->rtag == 0)
				 cur = cur->rightchild;
			 for (cur = cur->rightchild;
				 cur&&cur->leftchild != p&&cur->rightchild != p;
				 cur = cur->leftchild);
		 }
		 return cur;
	 }
 protected:
	 //������������
	 Node* _CreatTree(const T* a,size_t size,size_t& index,const T& invalid)
	 {
		 Node* cur = NULL;
		 if (index < size&&a[index] != invalid)
		 {
			 cur = new Node(a[index]);
			 cur->leftchild = _CreatTree(a,size,++index,invalid);
			 cur->rightchild = _CreatTree(a, size, ++index, invalid);
		 }
		 return cur;
	 }

	 //����������������
	 void CreatInThread(Node* root,Node* &prev)  //prev���봫����
	 {
		 if (NULL == root)
			 return;
		 CreatInThread(root->leftchild,prev);       //������������
		 if (NULL == root->leftchild)               //����������ĸ��ڵ�Ϊ�գ�������ǰ����ǰ��
		 {
			 root->leftchild = prev;
			 root->ltag = 1;
		 } 
		 if (prev!=NULL&&prev->rightchild==NULL)    //����prev�ĺ�̽��
		 {
			 prev->rightchild =root;
			 prev->rtag = 1;
		 }
		 prev =root;                //����ǰ�����
		 CreatInThread(root->rightchild,prev);    //������������
	 }

	 //Ѱ�Ҹ��ڵ�
	

 protected:
	 Node * _root;
 };