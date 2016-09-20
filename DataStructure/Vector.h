#pragma once
#include<iostream>
#include"typetraits.h"
#include<cassert>
#include<cstring>
using namespace std;


template<typename T>
class Vector
{
public:
	typedef T* Iterator;
	typedef T& Ref;
	typedef const T* ConstIterator;
	Vector()
		:_start(NULL)
		, _finish(NULL)
		, _EndOfStorage(NULL){}

	~Vector()
	{
		if (_start)
		{
			delete[] _start;
		}
	}
public:
	void PushBack(const T& data)
	{
		Insert(_finish,data);
		//CheckCapacity();
		//*_finish = data;
		//_finish++;
	}

	void PopBack()
	{
		Erase(_finish-1);
	}

	Iterator Insert(Iterator pos, const T& data)
	{
		assert((pos >= _start));
		assert((pos<=_finish));
		size_t sz = (pos-_start);          //如果增容的话，pos会改变
		CheckCapacity();
		pos = _start + sz;
		if (_TypeTraits<T>::_IsPODType().Get())
		{
			memmove(pos + 1, pos, sizeof(T)*(_finish - pos));
		}
		else
		{
			for (size_t i = Size(); i>(size_t)(pos - _start); i--)
			{
				_start[i] = _start[i - 1];
			}
		}
		*pos = data;
		_finish++;
		return pos + 1;
	}

	Iterator Erase(Iterator pos)
	{
		assert((pos >= _start));
		assert((pos < _finish));
		if (_TypeTraits<T>::_IsPODType().Get())
		{
			memcpy(pos, pos + 1, sizeof(T)*(_finish - pos - 1));
		}
		else
		{
			for (size_t i = (pos - _start); i < Size() - 1; i++)
			{
				_start[i] = _start[i + 1];
			}
		}
		_finish--;
		return pos;
	}

	size_t Size() const
	{
		return _finish - _start;
	}

	bool Empty() const
	{
		return _start == NULL;
	}

	size_t Capacity()
	{
		return _EndOfStorage - _start;
	}

	Ref operator[](int index)
	{
		return _start[index];
	}

	Ref Front()
	{
		assert(_start != NULL);
		return _start[0];
	}

	Ref Back()
	{
		assert(_start != NULL);
		return _start[Size()-1];
	}

	Iterator Begin()
	{
		return _start;
	}

	Iterator End()
	{
		return _finish;
	}

	ConstIterator Begin()const
	{
		return _start;
	}

	ConstIterator End()const
	{
		return _finish;
	}
private:
	void CheckCapacity()
	{
		if (_finish == _EndOfStorage)
		{
			size_t sz = Size();
			size_t NewSize = 2 *sz + 3;
			T* tmp = new T[NewSize];
			if (_start&&(_TypeTraits<T>::_IsPODType().Get()))
			{
				memcpy(tmp,_start,sz*sizeof(T));
			}
			else if (_start)
			{
				for (size_t i = 0; i <sz; i++)
				{
					tmp[i] = _start[i];
				}
			}
			delete[] _start;
			_start = tmp;
			_finish = _start +sz;
			_EndOfStorage = _start + NewSize;
		}
	}
protected:
	Iterator _start;
	Iterator _finish;
	Iterator _EndOfStorage;
};