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
				if (index == 0)                     //���ڵ����⴦��
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
				if (cur == t._root)             //���ڵ����⴦��
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
		stack<Node*> del;         //����һ��������ÿ��������del,����ͷ�del
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

		while (!del.empty())    //�ͷ�delջ�еĽ��
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
			while (cur)                            //������·���
			{
				cout << cur->_data << " ";
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			s.pop();
			cur = top->_right;  //����·�����һ�������������ĸ��ڵ�����Ϊcur,�ظ���������
		}
		cout <<endl;
	}

	void InOderNonR()
	{
		Node* cur = _root;
		stack<Node*> s;

		while (cur || !s.empty())
		{
			while (cur)              //������·
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			cout << top->_data <<" ";
			s.pop();
			cur = top->_right;   //����·�����һ�������������ĸ��ڵ�����Ϊcur,�ظ���������
		}
		cout << endl;
	}

	//�ǵݹ�������������������3��״̬���ֱ��ǣ�������·�����������ĸ��ڵ���ӣ���ջ
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
			if (flag == 1)        //������·
			{
				if (cur->_left == NULL)  //��·Ϊ�գ��л�״̬��2
				{
					flag = 2;
				}
				else
				{
					cur = cur->_left;
					s.push(cur);
				}
			}
			else if (flag == 2)   //����ǰ�����������ĸ��ڵ����
			{
				if (cur->_right== NULL) //����������ĸ��ڵ�Ϊ�գ���ʾ�ý�������ϣ��л�����ջ
					flag = 3;
				else
				{
					cur = cur->_right;
					s.push(cur);   //����ǰ�����������ĸ��ڵ����
					flag = 1;      //�л�״̬��������·
				}
			}
			else
			{
				Node* top = s.top();      
				cout << top->_data<<" ";
				s.pop();
				while (!s.empty()&&s.top()->_right==top)  //����һ���Ѿ��������������Ľ���ջ
				{
					top = s.top();
					s.pop();
					cout << top->_data << " ";
				}
				flag = 2;        //�л�״̬��2
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
				count++;        //����һ��������count++
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
		size_t  NodeNum = 1;      //ͳ���ж������������
		size_t  LeveLast = 1;      //������ڷ��ʵ��������һ�����ݵ����
		size_t  VisitNum=0;       //ͳ���Ѿ����ӵ����ݵĸ���
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

			//����Գ��ӵĸ���������һ������һ�����ݵ����
			if (LeveLast == VisitNum)     
			{
				deep++;                //������һ�������ȼ�һ
				LeveLast = NodeNum;    //���µ���һ������һ�����ݵ�λ��
			}
		}
		return deep;
	}

	size_t GetLeveSize(size_t i)
	{
		//��������0
		if (NULL == _root)
			return 0;
		//��0���1�㷵�ز��
		if (i<=1)
			return i;

		queue<Node*> q;
		q.push(_root);
		size_t leve =1;              //��ǲ��
		size_t  NodeNum = 1;          //ͳ���ж������������
		size_t  LeveLast = 1;         //������ڷ��ʵ��������һ�����ݵ����
		size_t  VisitNum = 0;         //ͳ���Ѿ��ж��������Ѿ�����
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
			
			if (VisitNum == LeveLast)   //����Գ��ӵĸ���������һ������һ�����ݵ����
			{
				leve++;
				if (leve == i)
					break;	
				LeveLast = NodeNum;        //���µ���һ������һ�����ݵ�λ��
			}
		}	
		//���Ѿ���ӹ������ݸ�����ȥ�Ѿ����ӵĸ������õ�Ҫ�����һ��ĸ���
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
				//�������������Ϊ�գ���ΪҶ�ӽ��
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
				if (cur->_data == x)         //����ҵ���ֱ�ӷ���
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