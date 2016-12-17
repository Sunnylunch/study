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
		if (_Finish!=_EndOfStorage)       //����ռ�û��
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
		size_t n = pos - _Start;                      //���Ҫ�����λ�þ�����ʼλ�õ�ƫ����
		if (_Finish != _EndOfStorage&&pos == _Finish)     //��_Finish���λ�ò���һ��Ԫ��
		{
			Construct(_Finish, value);
			++_Finish;
		}
		else
		{
			CheckStorge(pos, value);                        //�������,����������
		}

		return Begin() + n;                              //������������λ�ã���������ֹposʧЧ(�������ÿռ�)
	}

	Iterator Erase(Iterator pos)
	{
		if (pos != End())      //������һ����Ч��ɾ��λ��
		{
			//�����㷨copy����position���λ��֮���ֵ��ǰ�ƶ�һ������position���λ�ø��ǵ�
			copy(pos - 1; _Finish - 1, pos);
			Destory(_Finish - 1);               //�����һ��Ԫ��������
			_Finish--;                         //_Finish�Լ�,ָ����ȷ��λ��
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
	//	//��������ȡ

	//	//�������������
	//	memmove(frist+1,frist,(_Finish-pos)*sizeof(T));
	//}

	void CheckStorge(Iterator position, const T& value)
	{
		if (_Finish != _EndOfStorage)             //����δ��
		{
			Construct(_Finish, *(_Finish - 1));                          //��Finish-1����ֵ������Finish��
			//��posλ�ÿ�ʼ��_Finish-1��������ڣ���ÿ��Ԫ�ض�����ƶ�һ��λ�ã������㷨copy_backward
			_Finish++;
			copy_backward(position, _Finish - 2, _Finish-1);       //copy_backward�����һ��Ԫ�ص���һ��λ��
			*position =value;
		}
		else             //��������
		{
			size_t oldSize = Size();
			size_t len = (0 == oldSize ? 1 : 2 * oldSize);            //����Ҫ�¿��ٵĳ���
			Iterator newStart = VectorAlloc::Allocate(len);   //����newSize��С�Ŀռ�

			//UninitializedCopy(_Start, _Finish,newStart );   //���ɵ������е�ֵ��������������

			Iterator newFinish =newStart;


			//û�г�ʼ���Ŀ���
			newFinish = uninitialized_copy(_Start,position,newStart);
			Construct(newFinish, value);      //��Ҫ�����ֵ�ŵ�position���λ����
			++newFinish;
			newFinish = uninitialized_copy(position, _Finish,newFinish);

			Destory(_Start);                        //���پɵ�������ֵ
			VectorAlloc::DeAllocate(_Start, oldSize);        //���վ������Ŀռ�

			_Start = newStart;
			_Finish = _Start + oldSize+1;
			_EndOfStorage = _Start + len;
		}
	}

	//void UninitializedCopy(Iterator start,Iterator finish,Iterator newStart)
	//{

	//	//��������ȡ

	//	//�������������
	//	memmove(newStart,start,(finish-start)*sizeof(T));
	//}

private:
	T* _Start;         //ָ���һ��Ԫ��
	T* _Finish;        //ָ�����һ��Ԫ�ص���һ��λ��
	T* _EndOfStorage;  //�����Ķ�
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