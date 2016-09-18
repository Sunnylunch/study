#include<iostream>
#include<stack>
#include<queue>
#include<cassert>
using namespace std;
//
//
����ջʵ��һ������

template<typename T>
class Queue
{
public:
	void Push(const T& data);
	void Pop();
	size_t Size();
	bool Empty();
	T& Front();
	T& Back();
private:
	stack<T> _s1;           //_s1��Ϊ���
	stack<T> _s2;           //_s2��Ϊ����
};

template<typename T>
void Queue<T>::Push(const T& data)
{
	_s1.push(data);
}

template<typename T>
void Queue<T>::Pop()
{
	assert((_s1.size()+_s2.size()));           //����ջ��Ϊ�գ�������ѿ�
	if (_s2.empty())                           //���_s2�Կգ�����Ҫ��_s1�е�Ԫ�ص���_s2��
	{
		while (!_s1.empty())
		{
			_s2.push(_s1.top());
			_s1.pop();
		}
	}
	_s2.pop();
}

template<typename T>
size_t Queue<T>::Size()
{
	return (_s1.size() + _s2.size());        //��������ջ��Ԫ��֮��
}

template<typename T>
bool Queue<T>::Empty()
{
	if (_s1.empty() && _s2.empty())      //�������ջ��Ϊ�գ��򷵻�true
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
T& Queue<T>::Front()
{
	assert((_s1.size() + _s2.size()));           //����ջ��Ϊ�գ�������ѿ�
	if (_s2.empty())                           //���_s2�Կգ�����Ҫ��_s1�е�Ԫ�ص���_s2��
	{
		while (!_s1.empty())
		{
			_s2.push(_s1.top());
			_s1.pop();
		}
	}
	return _s2.top();
}

template<typename T>
T& Queue<T>::Back()
{
	assert((_s1.size() + _s2.size()));           //����ջ��Ϊ�գ�������ѿ�
	if (_s1.empty())                    //_s1Ϊ�գ���Ҫ��_s2ջ��Ԫ�ص���_s1
	{
		while (!_s2.empty())
		{
			_s1.push(_s2.top());
			_s2.pop();
		}
	}
	return _s1.top();
}


void test()
{
	Queue<int> q;
	q.Push(0);
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	q.Push(5);
	q.Pop();
	cout << q.Front() << endl;
	cout << q.Back() << endl;
	cout << q.Empty() << endl;
	cout << q.Size() << endl;

}

int main()
{
	test();
	system("pause");
	return 0;
}





//��������ʵ��һ��ջ


template<typename T>
class Stack
{
public:
	void Push(const T& data);
	void Pop();
	T& Top();
	size_t Size();
	bool Empty();
private:
	queue<T> _q1;
	queue<T> _q2;
};


template<typename T>
void Stack<T>::Push(const T& data)
{
	�򲻿յĶ��������������
	if (!_q2.empty())          //���q2��Ϊ��
	{
		_q2.push(data);
	}
	else
	{
		_q1.push(data);
	}
}

template<typename T>
void Stack<T>::Pop()
{
	assert((_q1.size()+_q2.size()));    //�������в���ͬʱΪ��
	queue<T> *tmp1= NULL;    //��¼���յĶ���
	queue<T> *tmp2 = NULL;    //��¼�յĶ���
	if (_q1.empty())          //���_q1Ϊ��
	{
		tmp1 = &_q2;
		tmp2 = &_q1;
	}
	else
	{
		tmp1 = &_q1;
		tmp2 = &_q2;
	}
	while (tmp1->size() > 1)
	{
		tmp2->push(tmp1->front());
		tmp1->pop();
	}
	tmp1->pop();
}

template<typename T>
T& Stack<T>::Top()
{
	assert((_q1.size() + _q2.size()));    //�������в���ͬʱΪ��
	queue<T> *tmp1 = NULL;    //��¼���յĶ���
	if (_q1.empty())          //���_q1Ϊ��
	{
		tmp1 = &_q2;
	}
	else
	{
		tmp1 = &_q1;
	}
	return tmp1->back();         //���ز��յĶ��е�β��Ԫ��
}

template<typename T>
size_t Stack<T>::Size()
{
	return (_q1.size() + _q2.size());
}


template<typename T>
bool Stack<T>::Empty()
{
	return (_q1.empty() && _q2.empty());
}


void test()
{
	Stack<int> s;
	s.Push(0);
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	cout << s.Top() << endl;
	cout << s.Size() << endl;
	cout << s.Empty() << endl;
	s.Pop();
	cout << s.Top() << endl;
	cout << s.Size() << endl;
	cout << s.Empty() << endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}