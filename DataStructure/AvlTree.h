#pragma once
#include<stack>
using namespace std;
 template<typename K,typename V>
 struct AvlTreeNode
 {
	 K _key;
	 V _value;
	 int _bf;           //平衡因子，等于右子树的高度减去左子树的高度
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
				 return false;                 //找到则不插入
		 }
		 cur = new Node(k);                    //开辟一个新结点
		 if (s.empty())                        //如果栈为空
		 {
			 _root = cur;                       //新节点直接插入
			 return true;
		 }
		 parent = s.top();           //让parent指向这个插入位置的父亲
		 if (k>parent->_key)
		 {
			 parent->_right = cur;   //如果要插入的结点大于父节点
		 }
		 else 
		 {
			 parent->_left = cur;     //如果要插入的结点小于父节点
		 }
		 while (!s.empty())            //重新平衡化
		 {
			 parent = s.top();         //从栈中退出父节点
			 s.pop();
			 if (parent->_left ==cur)   //如果cur是parent的左孩子，则parent的平衡因子减一
				 parent->_bf--;
			 else                      //如果cur是parent的左孩子，则parent的平衡因子加一
				 parent->_bf++;

			 if (parent->_bf == 0)       //如果父节点的平衡因子为0，则已经平衡,跳出循环
				 break;
			 if (parent->_bf == 1 || parent->_bf == -1)      //如果父节点的平衡因子的绝对值为1
				 cur = parent;                //则继续向上回溯，考察父节点的平衡状态
			 else                             //需要做平衡化处理
			 {
				 int d = 0;            //用于区别单双旋转
				 if (parent->_bf < 0)  //得到父节点的平衡因子的正负
					 d = -1;           
				 else
					 d = 1;
				 if (cur->_bf == d)    //如果父节点的平衡因子与d同号，则说明进行了外插入，要单旋转恢复
				 {
					 if (d == -1)            //父节点的左子树高度高，进行右旋转恢复
						 RotateRight(parent);
					 else                     //父节点的右子树高度高，进行左旋转恢复
						 RotateLeft(parent);

				 }
				 else            //进行了内侧插入，要双旋转恢复
				 {
					 if (d == -1)    //父节点的左子树高度高，则进行先左后右
						 DoubleRotateLR(parent);
					 else             //父节点的右子树高度高，则进行先右后左
						 DoubleRotateRL(parent);
				 }
				 //重新平衡后，parent的高度降低，无需向上进行回溯
				 break;
			 }
		 }

		 if (!s.empty())          //如果栈不为空，则需要进行重新连接
		 {
			 cur = s.top();
			 if (cur->_key > parent->_key)
				 cur->_left = parent;
			 else
				 cur->_right = parent;
		 }
		 else
			 _root = parent;                 //如果栈为空,调整到根节点
		 return true;
	 }

	 bool Remove(const K& k)            //删除一个结点
	 {
		 int dd = 0;                   //用来标记旋转之后与上层的链接关系
		 int d = 0;
		 Node* tmp = NULL;          //用来保存祖父结点
		 Node* cur = _root;
		 Node* del = NULL;
		 Node* parent = NULL;
		 stack<Node*> s;
		 while (cur != NULL)
		 {
			 s.push(cur);                //保存从根节点到删除结点之间的路径
			 if (cur->_key < k)
				 cur = cur->_right;
			 else if (cur->_key>k)
				 cur = cur->_left;
			 else
				 break;
		 }
		 if (cur == NULL)
			 return false;                   //找不到删除失败
		 //如果被删除的结点有两个子女，则先转换成一个子女的情况
		 if (cur->_left != NULL&&cur->_right != NULL)
		 {
			 Node* minRight = cur->_right;       //minRight保存cur右子树的最小值
			 while (minRight->_left)
			 {
				 s.push(minRight);
				 minRight = minRight->_left;
			 }
			 cur->_key = minRight->_key;
			 cur->_value = minRight->_value;
			 cur = minRight;         //让cur指向被删除的结点
			 s.push(cur);            //让要删除的结点入栈
		 }
		 s.pop();                    //抛出要删除的结点
		 if (s.empty())               //如果要删除的是根节点
		 {
			 if (cur->_left != NULL)
				 _root = cur->_left;
			 else
				 _root = cur->_right;
			 delete cur;
			 return true;
		 }

		 parent = s.top();           //parent保存要删除结点的父节点
		 del = cur;                  //被删除的结点保存到del里面
		 if (cur->_left != NULL)     //要删除的结点只有一个子女，并进行链接
		 {
			 parent = cur->_left;
			 cur = cur->_left;
		 }
		 else
		 {
			 parent = cur->_right;
			 cur = cur->_right;
		 }

		//重新平衡化
		 while(!s.empty())
		 {
			 parent=s.top();           //parnet保存父节点
			 s.pop();                  //抛出父节点
			 if (parent->_left == cur)   //cur在parent的左子树,调整父节点的平衡因子
				 parent->_bf++;
			 else
				 parent->_bf--;
			 if (!s.empty())             //如果栈不为空
			 {
			     tmp = s.top();        //tmp保存cur的祖父结点
				 if (tmp->_left == parent)     //dd表示旋转后与上层的链接方向
					 dd = -1;                  //旋转之后与上层左链接
				 else
					 dd = 1;                    //旋转之后与上层右链接
			 }
			 else
				 dd = 0;                         //旋转之后不与上层链接

			 if (parent->_bf == 1 || parent->_bf == -1)   //删除后树的高度不变
				 break;
			 if (parent!= 0)          //原来parent的高度不为0，且较矮的子树被缩短
			 {
				 if (parent->_bf < 0)      //如果叫高的子树是左子树
				 {
					 d = -1;
					 cur = parent->_left;    //cur指向较高的子树
				 }
				 else                   //较高的子树是右子树
				 {
					 d = 1;
					 cur = parent->_right;
				 }
				 if (cur->_bf == 0)          //如果较高的子树平衡因子是0,则进行一次单旋转
				 {
					 if (d == -1)              //右旋转,较高子树是左子树
						 RotateRight(parent);
					 else
						 RotateLeft(parent);   //左旋转，较高子树是右子树
					 break;                   //旋转完成之后树的高度不变，则直接跳出循化
				 }
				 if (cur->_bf==d) //如果较高子树与父节点平衡因子同号，单旋转,旋转之后树的高度改变
				 {
					 if (d == -1)              //右旋转,较高子树是左子树
						 RotateRight(parent);
					 else
						 RotateLeft(parent);   //左旋转，较高子树是右子树
				 }
				 else              //双旋转
				 {
					 if (d == -1)
						 DoubleRotateLR(parent);
					 else
						 DoubleRotateRL(parent);
				 }
				 //与上层进行链接
				 if (dd == -1)
					 tmp->_left = parent;
				 else if (dd == 1)
					 tmp->_right = parent;				 
			 }
			 cur = parent;      //cur保存当前parent,用于回溯
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

	 void RotateLeft(Node *&ptr)                         //左旋转
	 {
		 Node* subL= ptr;              //subL指向ptr结点
		 ptr = ptr->_right;            //让ptr指向新的根结点
		 subL->_right = ptr->_left;    //让ptr的左子树链接到subL的右子树上
		 ptr->_left = subL;            //让subL成为ptr的左子树
		 ptr->_bf = 0;                 //因为左旋之后ptr的左右子树高度相同，所以平衡因子为0
		 subL->_bf = 0;                //subL的左右子树的高度也相同，平衡因子也为0
	 }

	 void RotateRight(Node* &ptr)                        //右旋转
	 {
		 Node* subR = ptr;            //subL指向ptr
	     ptr = ptr->_left;            //ptr指向新的根节点
		 subR->_left = ptr->_right;   //ptr的右子树链接到subR的左子树上
		 ptr->_right = subR;           //让subR成为新根的右子树
		 ptr->_bf = 0;                //调整平衡因子
		 subR->_bf = 0;
	 }

	 void DoubleRotateLR(Node* &ptr)                    //双旋转，先左后右
	 {
		 Node* subL = ptr->_left;        //让subL指向ptr的左孩子
		 Node* subR = subL->_right;      //让subR指向subL的右孩子，即指向ptr的孙子结点

		 //先进行左旋，将内侧插入转换为外侧插入，即将双旋转转换为单旋转
		 subL->_right = subR->_left;     //让subR的左链接到subL的右上
		 subR->_left = subL;             //让subR重新成为根

		 //调整平衡因子
		 if (subR->_bf <= 0)     //subR的左子树高度不小于右子树
			 subL->_bf = 0;      //因为subL的左子树下移一层，所以平衡因子为0
		 else                    //subR的右子树高度高，subR左子树的高度不变
			 subL->_bf =-1;       //而subL的左子树要下移一层

		 //再进行右旋，转换成平衡树
		 ptr->_left = subR->_right;
		 subR->_right = ptr;

		 //调整平衡因子
		 if (subR->_bf== -1)       //subR的右子树高度小于左子树
			 ptr->_bf = 1;         //ptr的右子树下移,subR原来的右子树上移
		 else                      //subR的右子树的高度不小于左子树高度
			 ptr->_bf = 0;         //subR的右子树高度不变，ptr的右子树下移
		 subR->_bf = 0;             //新的根节点的平衡因子为0
		 ptr = subR;               //让ptr指向恢复平衡后的新的根
	 }

	 void DoubleRotateRL(Node* &ptr)                   //双旋转，先右后左
	 {
		 Node* subR = ptr->_right;
		 Node* subL = subR->_left;

		 //先进行右旋，将内侧插入转换成外侧插入
 		 subR->_left = subL->_right;
		 subL->_right = subR;

		 //调节平衡因子
		 if (subL->_bf == -1)  //subL的右子树高度小于左子树
			 subR->_bf = 1;    //subR的右子树下移
		 else                  //subL的右子树高度不小于左子树高度
			 subR->_bf = 0;

		 //左旋
		 ptr->_right = subL->_left;
		 subL->_left = ptr;

		 //调节平衡因子
		 if (subL->_bf <= 0)     //subL的左子树高度不大于右子树高度
			 ptr->_bf = 0;       //ptr的右子树下移，subL的右子树高度上移
		 else
			 ptr->_bf = -1;       
		 subL->_bf = 0;
		 ptr = subL;              //让ptr指向恢复平衡后的新的根
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