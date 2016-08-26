#pragma once
#include<iostream>
#include<cstring>
#include<string>
#include<cassert>
using namespace std;

template<typename T>
class Seqlist
{
public:
	Seqlist();
	Seqlist(const Seqlist<T>& seq);
	Seqlist & operator=(Seqlist<T> seq);
	~Seqlist();
	void PushBack(const T& d);
	void PushFront(const T& d);
	void PopBack();
	void PopFront();
	void Insert(int index,const T& d);
	int Search(const T& d);
	void Remove(const T& d);
	void RemoveAll(const T& d);
	void Sort();
	void Reserve(int n);
	void Display();
	int GetSize();
	T& operator[](int index);
private:
	void CheckCapacity(int n=0);
private:
	T *_pdata;
	int _sz;
	int _capacity;
};

template<typename T>
T& Seqlist<T>::operator[](int index)
{
	assert(index >= 0);
	assert(index < _sz);
	return _pdata[index];
}

template<typename T>
int Seqlist<T>::GetSize()
{
	return _sz;
}

template<typename T>
Seqlist<T>::Seqlist()
             :_sz(0)
              , _capacity(0)
			  , _pdata(NULL){}

template<typename T>
Seqlist<T>::Seqlist(const Seqlist<T>& seq)
{

	_pdata = new T[seq._capacity];
	for (int i = 0; i < seq._sz; i++)
	{
		_pdata[i] = seq._pdata[i];
	}
	_sz = seq._sz;
	_capacity = seq._capacity;
}


template<typename T>
Seqlist<T>& Seqlist<T>::operator=(Seqlist<T> seq)
{
	swap(_pdata,seq._pdata);
	_sz = seq._sz;
	_capacity = seq._capacity;
	return *this;
}

template<typename T>
Seqlist<T>::~Seqlist()
{
    if (_pdata != NULL)
	{
		delete[] _pdata;
		_pdata = NULL;
		_sz = 0;
		_capacity = 0;
	}
}

template<typename T>
void Seqlist<T>::CheckCapacity(int n=0)
{
	if (_sz == _capacity||n>_capacity)
	{
		int NewCapacity =2*_capacity+1;
		if (n > _capacity)
		{
			NewCapacity = n;
		}
		T* tmp = new T[NewCapacity];
		for (int i = 0; i < _sz; i++)
		{
			tmp[i] =_pdata[i];
		}
		delete[] _pdata;
		_pdata = tmp;
		_capacity = NewCapacity;
	}

}

template<typename T>
void Seqlist<T>::PushBack(const T& d)
{
	CheckCapacity();
	_pdata[_sz++] = d;
}

template<typename T>
void Seqlist<T>::PushFront(const T& d)
{
	CheckCapacity();
	//memmove(_pdata + 1,_pdata,sizeof(T)*_sz);
	for (int i =_sz;i>0; i--)
	{
		_pdata[i] = _pdata[i-1];
	}
	_pdata[0] = d;
	_sz++;
}

template<typename T>
void Seqlist<T>::PopBack()
{
	_sz--;
}

template<typename T>
void Seqlist<T>::PopFront()
{
	//memmove(_pdata,_pdata+1,sizeof(T)*(--_sz));
	for (int i = 0; i<_sz-1; i++)
	{
		_pdata[i] = _pdata[i+1];
	}
	_sz--;
}

template<typename T>
void Seqlist<T>::Insert(int index, const T& d)
{
	assert(index >= 0);
	assert(index<_sz);
	CheckCapacity();
	//memmove(_pdata+index+1,_pdata+index,sizeof(T)*(_sz-index));
	for (int i = _sz; i>index; i--)
	{
		_pdata[i] = _pdata[i - 1];
	}
	_sz++;
	_pdata[index] = d;
}

template<typename T>
int Seqlist<T>::Search(const T& d)
{
	int i = 0;
	for (i = 0; i < _sz; i++)
	{
		if (_pdata[i] == d)
		{
			return i;
		}
	}
	return -1;              //Ã»ÕÒµ½·µ»Ø-1
}

template<typename T>
void Seqlist<T>::Remove(const T& d)
{
	int index = Search(d);
	if (index == -1)
	{
		return;
	}
	else
	{
		//memmove(_pdata+index,_pdata+index+1,sizeof(T)*(_sz-index-1));
		for (int i =index; i<_sz-1; i++)
		{
			_pdata[i] = _pdata[i+1];
		}
		_sz--;
	}
}

template<typename T>
void Seqlist<T>::RemoveAll(const T& d)
{
	while (Search(d) != -1)
	{
		Remove(d);
	}
}

template<typename T>
void Seqlist<T>::Reserve(int n)
{
	CheckCapacity(n);
}

template<typename T>
void Seqlist<T>::Sort()
{
	int end = _sz - 1;
	for (int i = 0; i < _sz - 1; i++)
	{
		int flag = 1;
		int k = end;
		for (int j = 0; j <end;j++)
		{
			if (_pdata[j]>_pdata[j+1])
			{
				T tmp = _pdata[j];
				_pdata[j] = _pdata[j + 1];
				_pdata[j + 1] = tmp;
				flag = 0;
				k= j;
			}
		}
		if (flag == 1)
		{
			return;
		}
		end = k;
	}
}


template<typename T>
void Seqlist<T>::Display()
{
	for (int i = 0; i < _sz; i++)
	{
		cout << _pdata[i] << " ";
	}
	cout << endl;
}