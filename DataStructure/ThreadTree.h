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
		 _root = _CreatTree(a,size,index,invalid);  //创建二叉树

		 Node* prev = NULL;  //前驱结点指针
         //中序线索化二叉树
		 if (_root != NULL)
		 {
			 CreatInThread(_root, prev);    //线索化二叉树
			 prev->rightchild = NULL;       //将最后一个结点的后继置为空
			 prev->rtag = 1;                //rtag=1表示指向后继
		 }
	 }

	 Node* Frist(Node* cur)    //寻找以cur为根的子树的第一个结点
	 {
		 if (cur== NULL)
			 return NULL;
		 while (cur->ltag == 0)
			 cur=cur->leftchild;
		 return cur;
	 }

	 Node* Last(Node* cur)     //寻找以cur为根的子树的最后一个结点
	 {
		 if (cur == NULL)
			 return NULL;
		 while (cur->rtag==0)
		 {
			 cur = cur->rightchild;
		 }
		 return cur;
	 }

	 Node* Prior(Node* cur)   //找cur前驱结点
	 {
		 if (cur == NULL)
			 return NULL;
		 if (cur->ltag == 1)
			 return cur->leftchild;
		 return Last(cur->leftchild);
	 }

	 Node* Next(Node* cur)     //找后继结点
	 {
		 if (cur == NULL)
			 return NULL;
		 if (cur->rtag == 1)
			 return cur->rightchild;
		 return  Frist(cur->rightchild);
	 }

	 void PrevOder()            //先序遍历
	 {
		 if (NULL == _root)
			 return ;
		 Node* cur = _root;
		 while (cur != NULL)
		 {
			 cout << cur->_data << " ";     //访问根节点
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
		 while (cur->ltag == 0 || cur->rtag == 0)  //寻找后序的第一个结点
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
				 while (cur->ltag == 0 || cur->rtag == 0)  //寻找后序的第一个结点
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
		 if (p == NULL || p == _root)            //如果是空结点或根节点，则父结点为空
			 return NULL;
		 Node* cur = p;
		 while (cur->ltag == 0)
			 cur = cur->leftchild;
		 if (cur->leftchild != NULL)
		 {
			 for (cur = cur->leftchild;
				 cur != NULL&&cur->leftchild != p&&cur->rightchild != p;
				 cur = cur->rightchild);        //在右路寻找
		 }
		 if (cur == NULL || cur->leftchild == NULL)  //如果没找到
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
	 //中序建立二叉树
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

	 //二叉树中序线索化
	 void CreatInThread(Node* root,Node* &prev)  //prev必须传引用
	 {
		 if (NULL == root)
			 return;
		 CreatInThread(root->leftchild,prev);       //左子树线索化
		 if (NULL == root->leftchild)               //如果左子树的根节点为空，则建立当前结点的前驱
		 {
			 root->leftchild = prev;
			 root->ltag = 1;
		 } 
		 if (prev!=NULL&&prev->rightchild==NULL)    //设置prev的后继结点
		 {
			 prev->rightchild =root;
			 prev->rtag = 1;
		 }
		 prev =root;                //更新前驱结点
		 CreatInThread(root->rightchild,prev);    //线索化右子树
	 }

	 //寻找父节点
	

 protected:
	 Node * _root;
 };