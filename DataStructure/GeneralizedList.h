#pragma once 
#include<iostream>
#include<cassert>
using namespace std;
enum Type          //�����Ľ������������
{
	HEAD_TYPE,     //ͷ���
	VALUE_TYPE,    //ֵ����
	LIST_TYPE,     //������
};

struct GeneralizedNode
{
	Type _type;
	GeneralizedNode * _next;      //ָ����һ������ָ��
	union                         //�ֲ��ֵ࣬���
	{
		char _value;                    //ֵ����
		GeneralizedNode* _sublink;     //������
	};
	GeneralizedNode()
		:_next(NULL)
		, _sublink(NULL)
	{}
};


class GeneralizedList
{
	typedef GeneralizedNode Node;
public:
	GeneralizedList()
	{}

	GeneralizedList(const char *str)
		:_head(new Node)
	{
		_head=_CreatList(str,_head);
	}

	~GeneralizedList()
	{
		_destroy(_head);
	}
	GeneralizedList(const GeneralizedList& l)      //�������캯��
	{
		_head =NULL;
		_head=_Copy(_head,l._head);
	}

	GeneralizedList& operator=(GeneralizedList l)
	{
		swap(_head,l._head);
		return *this;
	}

	size_t Size()
	{
		return _Size(_head);
	}

	size_t Depth()
	{
		return _Depth(_head);
	}

	void Display()
	{
		_print(_head);
		cout << endl;
	}

private:
	Node* _CreatList(const char* &str,Node *head=(new Node))
	{
		assert(*str=='(');
		++str;
		Node* prev= head;
		head->_type = HEAD_TYPE;
		while (*str)
		{
			if ((*str >= 'a'&&*str <= 'z')
				|| (*str >= 'A'&&*str <= 'Z')
				|| (*str >= '0'&&*str <= '9'))
			{
				prev->_next = new Node;
				prev = prev->_next;
				prev->_value = *str;
				++str;
				prev->_type = VALUE_TYPE;
			}
			else if (*str == '(')
			{
				prev->_next = new Node;
				prev = prev->_next;
				prev->_sublink= _CreatList(str);        //�����ӱ�ݹ鴦��
				prev->_type = LIST_TYPE;
				++str;
			}
			else if (*str == ')')
			{
				return head;
			}
			else
			{
				++str;
			}
		}
		return head;
	}

	void _print(Node* head)
	{
		assert(head);
		Node *cur =head;
		while (cur)
		{
			if (cur->_type ==VALUE_TYPE)
			{
				cout << cur->_value;
				if (cur->_next != NULL)        //����������һ��ֵ��������������
				{
					cout << ",";
				}
				cur = cur->_next;
			}
			else if (cur->_type==LIST_TYPE)  //������ӱ�
			{
				_print(cur->_sublink);
				if (cur->_next != NULL)        //����������һ��ֵ��������������
				{
					cout << ",";
				}
				cur = cur->_next;
			}
			else
			{
				cout << "(";
				cur = cur->_next;
			}
		}
		cout << ")";
	}

	size_t _Size(Node *head)                       //�����������ݵĸ���
	{
		size_t count = 0;
		Node *cur = head;
		while (cur)
		{
			if (cur->_type == VALUE_TYPE)
			{
				count++;
				cur = cur->_next;
			}
			else if (cur->_type == LIST_TYPE)
			{
				count += _Size(cur->_sublink);
				cur = cur->_next;
			}
			else
			{
				cur = cur->_next;
			}
		}
		return count;
	}

	size_t _Depth(Node *head)                        //����������
	{
		size_t MaxDeep =1;
		size_t n =1;
		Node *cur = head;
		while (cur)
		{
			if (cur->_type == VALUE_TYPE)
			{
				cur = cur->_next;
			}
			else if (cur->_type == LIST_TYPE)
			{
				n+=_Depth(cur->_sublink);
				if (n > MaxDeep)
				{
					MaxDeep = n;
				}
				n =1;
				cur = cur->_next;
			}
			else
			{
				cur = cur->_next;
			}
		}
		return MaxDeep;
	}



	Node* _Copy(Node *NewHead,Node* head)
	{
		assert(head);
		Node *_newhead =new Node;
		NewHead=_newhead;
		Node *cur =head;       
		_newhead->_type = cur->_type;      //����ͷ��������
		while (cur)
		{
			if (cur->_type == VALUE_TYPE)
			{
				_newhead->_next= new Node;
				_newhead = _newhead->_next;

				_newhead->_value= cur->_value;
				_newhead->_type = cur->_type;

				cur = cur->_next;
			}
			else if (cur->_type==LIST_TYPE)
			{
				_newhead->_next= new Node;
				_newhead = _newhead->_next;
				_newhead->_type = cur->_type;

				_newhead->_sublink = _Copy(_newhead->_sublink,cur->_sublink);  //���ӱ��������
				
				cur = cur->_next;
			}
			else
			{
				cur = cur->_next;
			}
		}
		return NewHead;
	}

	void _destroy(Node *head)
	{
		Node *del = head;
		while (head)
		{
			del = head;
			if (head->_type== LIST_TYPE)
			{
				_destroy(head->_sublink);
				head = head->_next;
			}
			else
			{
				head = head->_next;
				delete del;
			}
		}
	}
protected:
	Node *_head;
};