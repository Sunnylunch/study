#pragma once
#include<queue>
#include<stack>
using namespace std;

template<typename T>
struct TreeNode
{
	T _data;
	TreeNode<T> *_left;
	TreeNode<T> *_right;
	TreeNode(const T& data=T())
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};


template<typename T>
class TreeNonR
{
	typedef TreeNode<T> Node;
public:
	TreeNonR()
		:_root(NULL)
	{}

	/*TreeNonR(const T* a, size_t size, const T& invalid)
	{
		size_t index = 0;
		stack<Node*> s;
		Node* cur = _root;
		int flag = 1;

		while (index < size)
		{
			if (flag == 1)
			{
				if (a[index] == '#')
					flag = 2;
				else
				{
					cur= new Node(a[index]);
					if (!s.empty())
					{
						s.top()->_left = cur;
					}
					else
					{
						_root = cur;
					}
					s.push(cur);
				}
			}
			else if (flag==2)
			{
				if (a[index] == '#')
					flag = 3;
				else
				{
					cur = new Node(a[index]);
					s.top()->_right = cur;
					s.push(cur);
					flag = 1;
				}
			}
			else
			{
				Node* top = s.top();
				s.pop();
				while (!s.empty() && s.top()->_right == top)
				{
					top = s.top();
					s.pop();
				}
				flag = 2;
				index--;
			}
			index++;
		}

	}*/

	TreeNonR(const T* a, size_t size, const T& invalid)
	{
		Node* cur = NULL;
		stack<Node*> s;
		size_t index = 0;
		while (index < size)
		{
			while (index < size&&a[index] != invalid)
			{
				if (index == 0)                     //根节点特殊处理
				{
					_root = new Node(a[index++]);
					cur = _root;
				}
				else
				{
					cur->_left = new Node(a[index++]);
					cur = cur->_left;
				}
				s.push(cur);
			}
			index++;

			Node* top = s.top();
			s.pop();

			if (index < size&&a[index] != invalid)
			{
				cur = top;
				cur->_right = new Node(a[index++]);
				cur = cur->_right;
				s.push(cur);
			}
		}
	}


	TreeNonR(const TreeNonR<T>& t)
	{
		Node* tmp = NULL;
		Node* cur = t._root;
		stack<Node*> s;
		stack<Node*> s2;
		while (cur || !s.empty())
		{
			while (cur)
			{
				if (cur == t._root)             //根节点特殊处理
				{
					tmp = new Node(cur->_data);
					_root = tmp;
				}
				else
				{
					tmp->_left = new Node(cur->_data);
					tmp = tmp->_left;
				}
				s.push(cur);
				s2.push(tmp);
				cur = cur->_left;
			}

			Node* top = s.top();
			Node* top2 = s2.top();
			s.pop();
			s2.pop();

			cur = top->_right;
			if (cur)
			{
				tmp = top2;
				tmp->_right= new Node(cur->_data);
				tmp = tmp->_right;
				cur = cur->_left;
			}
		}
	}


	TreeNonR<T>& operator=(TreeNonR<T>& t)
	{
		if (this != &t)
		{
			TreeNonR<T> tmp(t);
			swap(_root,tmp._root);
		}
		return *this;
	}


	~TreeNonR()
	{
		Node* cur = _root;
		stack<Node*> s;
		stack<Node*> del;         //遍历一遍树，将每个结点存入del,最后释放del
		while (cur || !s.empty())
		{
			while (cur)
			{
				del.push(cur);
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();
			cur = top->_right;   
		}

		while (!del.empty())    //释放del栈中的结点
		{
			Node* top = del.top();
			del.pop();
			delete top;
		}
	}

	void PrevOderNonR()
	{
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)                            //访问左路结点
			{
				cout << cur->_data << " ";
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			s.pop();
			cur = top->_right;  //将左路的最后一个结点的右子树的根节点设置为cur,重复上述过程
		}
		cout <<endl;
	}

	void InOderNonR()
	{
		Node* cur = _root;
		stack<Node*> s;

		while (cur || !s.empty())
		{
			while (cur)              //访问左路
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			cout << top->_data <<" ";
			s.pop();
			cur = top->_right;   //将左路的最后一个结点的右子树的根节点设置为cur,重复上述过程
		}
		cout << endl;
	}

	//非递归后序遍历二叉树，设置3个状态来分别标记：遍历左路，将右子树的根节点入队，出栈
	void PostOderNonR()
	{
		if (_root == NULL)
			return;
		Node* cur =_root;
		int flag = 1;
		stack<Node*> s;
		s.push(_root);
		while (!s.empty())
		{
			cur = s.top();
			if (flag == 1)        //遍历左路
			{
				if (cur->_left == NULL)  //左路为空，切换状态到2
				{
					flag = 2;
				}
				else
				{
					cur = cur->_left;
					s.push(cur);
				}
			}
			else if (flag == 2)   //将当前结点的右子树的根节点入队
			{
				if (cur->_right== NULL) //如果右子树的根节点为空，表示该结点访问完毕，切换到出栈
					flag = 3;
				else
				{
					cur = cur->_right;
					s.push(cur);   //将当前结点的右子树的根节点入队
					flag = 1;      //切换状态到遍历左路
				}
			}
			else
			{
				Node* top = s.top();      
				cout << top->_data<<" ";
				s.pop();
				while (!s.empty()&&s.top()->_right==top)  //将上一个已经访问完右子树的结点出栈
				{
					top = s.top();
					s.pop();
					cout << top->_data << " ";
				}
				flag = 2;        //切换状态到2
			}
		}	
		cout << endl;
	}

	size_t Size()
	{
		size_t count = 0;
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				count++;        //遍历一个结点就让count++
				s.push(cur);
				cur = cur->_left;
			}

			Node * top = s.top();
			s.pop();
			cur = top->_right;
		}
		return count;
	}

	size_t Depth()
	{
		if (_root == NULL)
			return 0;
		queue<Node*> q;
		size_t deep = 0;             
		size_t  NodeNum = 1;      //统计有多少数据入过队
		size_t  LeveLast = 1;      //标记正在访问的这层的最后一个数据的序号
		size_t  VisitNum=0;       //统计已经出队的数据的个数
		q.push(_root);
		while (!q.empty())
		{
			Node* cur =q.front();
			q.pop();
			VisitNum++;
			if (NULL != cur->_left)
			{
				q.push(cur->_left);
				NodeNum++;
			}

			if (NULL != cur->_right)
			{
				q.push(cur->_right);
				NodeNum++;
			}

			//如果以出队的个数等于这一层的最后一个数据的序号
			if (LeveLast == VisitNum)     
			{
				deep++;                //访问完一层就让深度加一
				LeveLast = NodeNum;    //更新到下一层的最后一个数据的位置
			}
		}
		return deep;
	}

	size_t GetLeveSize(size_t i)
	{
		//空树返回0
		if (NULL == _root)
			return 0;
		//第0或第1层返回层号
		if (i<=1)
			return i;

		queue<Node*> q;
		q.push(_root);
		size_t leve =1;              //标记层号
		size_t  NodeNum = 1;          //统计有多少数据入过队
		size_t  LeveLast = 1;         //标记正在访问的这层的最后一个数据的序号
		size_t  VisitNum = 0;         //统计已经有多少数据已经出队
		while (!q.empty())
		{
			Node* cur = q.front();
			q.pop();
			VisitNum++;
			if (NULL != cur->_left)
			{
				q.push(cur->_left);
				NodeNum++;
			}

			if (NULL != cur->_right)
			{
				q.push(cur->_right);
				NodeNum++;
			}
			
			if (VisitNum == LeveLast)   //如果以出队的个数等于这一层的最后一个数据的序号
			{
				leve++;
				if (leve == i)
					break;	
				LeveLast = NodeNum;        //更新到下一层的最后一个数据的位置
			}
		}	
		//用已经入队过的数据个数减去已经出队的个数，得到要求的这一层的个数
		return NodeNum - VisitNum;   
	}



	size_t Leaft()
	{
		size_t count = 0;
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				//如果左右子树都为空，则为叶子结点
				if (cur->_left == NULL&&cur->_right == NULL)
					count++;
				s.push(cur);
				cur = cur->_left;
			}
			Node * top = s.top();
			s.pop();
			cur = top->_right;
		}
		return count;
	}

	Node* Find(const T& x)
	{
		Node* cur = _root;
		stack<Node*> s;
		while(cur||!s.empty())
		{
			while (cur)
			{
				if (cur->_data == x)         //如果找到则直接返回
					return cur;
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			s.pop();
			cur = top->_right;
		}
		return NULL;
	}

protected:
	Node *_root;
};