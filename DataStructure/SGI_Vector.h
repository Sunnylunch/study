#pragma once
#include"Allocator.h"
#include"Construct.h"
#include <iostream>
#include <algorithm>
#include<memory>
using namespace std;
#include"Iterator.h"



template<typename T, typename _ALLOC = Alloc>
class Vector
{
	typedef SimpleAlloc<T, _ALLOC> VectorAlloc;
public:
	typedef T* Iterator;
	typedef const T*  ConstIterator;

	Vector()
		:_Start(NULL)
		, _Finish(NULL)
		, _EndOfStorage(NULL)
	{}

	~Vector()
	{
		Clear();
		VectorAlloc::DeAllocate(_Start, (_EndOfStorage - _Start));
	}

	void PushBack(const T& value)
	{ 
		if (_Finish!=_EndOfStorage)       //如果空间没满
		{
			Construct(_Finish,value);
			_Finish++;
		}
		else
		{
			Insert(End(), value);
		}
	}

	void PopBack()
	{
		--_Finish;
		Destory(_Finish);
	}

	Iterator Insert(Iterator pos, const T& value)
	{
		size_t n = pos - _Start;                      //算出要插入的位置距离起始位置的偏移量
		if (_Finish != _EndOfStorage&&pos == _Finish)     //在_Finish这个位置插入一个元素
		{
			Construct(_Finish, value);
			++_Finish;
		}
		else
		{
			CheckStorge(pos, value);                        //检查容量,并作出调整
		}

		return Begin() + n;                              //返回这个插入的位置，这样做防止pos失效(重新配置空间)
	}

	Iterator Erase(Iterator pos)
	{
		if (pos != End())      //必须是一个有效的删除位置
		{
			//调用算法copy，将position这个位置之后的值向前移动一个，将position这个位置覆盖掉
			copy(pos - 1; _Finish - 1, pos);
			Destory(_Finish - 1);               //将最后一个元素析构掉
			_Finish--;                         //_Finish自减,指向正确的位置
		}
		return pos;
	}

	void  Clear()
	{
		while (_Start != _Finish)
		{
			_Finish--;
			Destory(_Finish);
		}
	}

	size_t Size()
	{
		return _Finish - _Start;
	}

	Iterator Begin()
	{
		return _Start;
	}

	Iterator End()
	{
		return _Finish;
	}
protected:
	//void CopyBackWard(Iterator frist,Iterator last,Iterator finish)
	//{
	//	//迭代器萃取

	//	//如果是内置类型
	//	memmove(frist+1,frist,(_Finish-pos)*sizeof(T));
	//}

	void CheckStorge(Iterator position, const T& value)
	{
		if (_Finish != _EndOfStorage)             //容量未满
		{
			Construct(_Finish, *(_Finish - 1));                          //将Finish-1处的值拷贝到Finish处
			//从pos位置开始到_Finish-1这段区间内，将每个元素都向后移动一个位置，采用算法copy_backward
			_Finish++;
			copy_backward(position, _Finish - 2, _Finish-1);       //copy_backward从最后一个元素的下一个位置
			*position =value;
		}
		else             //容量已满
		{
			size_t oldSize = Size();
			size_t len = (0 == oldSize ? 1 : 2 * oldSize);            //计算要新开辟的长度
			Iterator newStart = VectorAlloc::Allocate(len);   //开辟newSize大小的空间

			//UninitializedCopy(_Start, _Finish,newStart );   //将旧的容器中的值拷贝到新容器中

			Iterator newFinish =newStart;


			//没有初始化的拷贝
			newFinish = uninitialized_copy(_Start,position,newStart);
			Construct(newFinish, value);      //将要插入的值放到position这个位置上
			++newFinish;
			newFinish = uninitialized_copy(position, _Finish,newFinish);

			Destory(_Start);                        //销毁旧的容器的值
			VectorAlloc::DeAllocate(_Start, oldSize);        //回收旧容器的空间

			_Start = newStart;
			_Finish = _Start + oldSize+1;
			_EndOfStorage = _Start + len;
		}
	}

	//void UninitializedCopy(Iterator start,Iterator finish,Iterator newStart)
	//{

	//	//迭代器萃取

	//	//如果是内置类型
	//	memmove(newStart,start,(finish-start)*sizeof(T));
	//}

private:
	T* _Start;         //指向第一个元素
	T* _Finish;        //指向最后一个元素的下一个位置
	T* _EndOfStorage;  //容量的端
};


void Test()
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.PushBack(5);
	cout << Distance(v.Begin(),v.End()) << endl;
	Vector<int>::Iterator iter = v.End();
	Advance(iter,-2);
	cout << *iter << endl;
}