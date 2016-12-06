#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;


///////////////////////////////////////////////////////////////////////
////////////һ���ռ������������Ǵ���ڴ�ʱ���ã�ֱ����ϵͳ����
////////////__malloc_alloc_template

typedef void(*MALLOCALLOC)();           //��void (*)()   ��������MALLOCALLOC

template<int inst>
class _MallocAllocTemplate
{
private:
	static void* _OomMalloc(size_t);       //mallocʧ�ܵ�ʱ����õĺ���
	static MALLOCALLOC _MallocAllocOomHandler;         //����ָ�룬�ڴ治���ʱ��Ĵ������
public:
	static void* _Allocate(size_t n)                        //����ռ�n���ֽڵĿռ�
	{
		void *result=0;
		result = malloc(n);
		if (0 == result)                    //����mallocʧ�ܣ���͵�OOM_malloc
			_OomMalloc(n);

		return result;
	}

	static void _DeAllocate(void *p)                //�ͷ����ռ�
	{
		free(p);
	}

	static MALLOCALLOC _SetMallocHandler(MALLOCALLOC f)    //����һ��������������һ������ָ�룬����ֵҲ��һ������ָ��
	{
		MALLOCALLOC old = _MallocAllocOomHandler;
		_MallocAllocOomHandler = f;              //���ڴ����ʧ�ܵľ������Ϊf(����ָ��һ���ڴ�ʧ���ˣ���ϵͳȥ�ͷ������ط��ռ�ĺ���)
		return old;
	}
};

template<int inst>
void(* _MallocAllocTemplate<inst>::_MallocAllocOomHandler)()=0;    //Ĭ�ϲ������ڴ治�㴦�����

template<int inst>
void* _MallocAllocTemplate<inst>::_OomMalloc(size_t n)
{
	MALLOCALLOC _MyMallocHandler;     //����һ������ָ��
	void *result;                
	while (1)
	{
		_MyMallocHandler = _MallocAllocOomHandler;
		if (0 == _MyMallocHandler)                  //û�������ڴ治�㴦�����
			throw std::bad_alloc();                  //���׳��쳣

		(*_MyMallocHandler)();                 //�����ڴ治�㴦��ĺ����������ͷ������ط����ڴ�
		if (result = malloc(n))                //���������ڴ�
			break;
	}
	return result;                              //����ɹ�ʱ���򷵻�����ڴ�ĵ�ַ
}

typedef _MallocAllocTemplate<0> malloc_alloc;





//////////////////////////////////////////////////////////////////////////////
//////////////////�����ռ�������__default_alloc_template

enum { _ALIGN = 8 };              //���ջ�׼ֵ8�ı��������ڴ����
enum { _MAXBYTES = 128 };        //�������������Ŀ�Ĵ�С��128
enum { _NFREELISTS = 16 };       //��������ĳ��ȣ�����_MAXBYTES/_ALIGN
template <bool threads, int inst>  //��ģ�����Ͳ���
class _DefaultAllocTemplate
{
	union _Obj                      //���������������
	{
		_Obj* _freeListLink;         //ָ�������������ָ��
		char _clientData[1];          //this client sees
	};
private:
	static char* _startFree;             //�ڴ�ص�ͷָ��
	static char* _endFree;               //�ڴ�ص�βָ��
	static size_t _heapSize;              //��¼�ڴ���Ѿ���ϵͳ�����˶����ڴ�
	static _Obj* volatile _freeList[_NFREELISTS];    //��������
private:
	static size_t _GetFreeListIndex(size_t bytes)   //�õ�����ֽڶ�Ӧ������������Ӧȡ��λ��
	{
		return (bytes +(size_t) _ALIGN - 1) / (size_t)_ALIGN - 1;      
	}

	static size_t _GetRoundUp(size_t bytes)        //������ֽ�����ȡ��8�ı���
	{
		return (bytes + (size_t)_ALIGN - 1)&(~(_ALIGN-1));     //��n����ȡ��8�ı���
	}


	static void* _Refill(size_t n);          //�����������������ڴ�,n��ʾҪ���ڴ�Ĵ�С
	static char* _chunkAlloc(size_t size,int& nobjs);    //���ڴ���������ڴ�nobjs������ÿ������size����С
public:
	static void* Allocate(size_t n);      //nҪ����0
	static void DeAllocate(void *p,size_t n);        //nҪ������0
};


template<bool threads,int inst>
char* _DefaultAllocTemplate<threads,inst>::_startFree = 0;        //�ڴ�ص�ͷָ��

template<bool threads, int inst>
char* _DefaultAllocTemplate<threads, inst>::_endFree=0;           //�ڴ�ص�βָ��

template<bool threads, int inst>
size_t _DefaultAllocTemplate<threads, inst>::_heapSize = 0;              //��¼�ڴ���Ѿ���ϵͳ�����˶����ڴ�

template<bool threads, int inst>
typename _DefaultAllocTemplate<threads, inst>::_Obj* volatile      //ǰ���typename��ʾ�����Ǹ�����
_DefaultAllocTemplate<threads, inst>::_freeList[_NFREELISTS] = {0};    //��������





template<bool threads, int inst>
void* _DefaultAllocTemplate<threads, inst>::Allocate(size_t n)    //����ռ�
{
	void *ret;
	//���ж�Ҫ����Ŀռ��С�ǲ��Ǵ���128���ֽ�
	if (n>_MAXBYTES)      //����_MAXBYTES���ֽ�����Ϊ�Ǵ���ڴ棬ֱ�ӵ���һ���ռ�������
	{
		ret = malloc_alloc::_Allocate(n);
	}
	else       //�����ȥ������������
	{
		_Obj* volatile *myFreeList = _freeList+_GetFreeListIndex(n);  //��myFreeListָ������������n����ȡ8��������
		_Obj* result = *myFreeList;
		if (result == 0)  //����������û�й��ڴ棬���Ҫȥ�ڴ��������
		{
			ret = _Refill(_GetRoundUp(n));      //���ڴ��������
		}
		else            //�Ѿ��������������ҵ����ڴ�
		{
			*myFreeList= result->_freeListLink;      //�ѵڶ���ռ�ĵ�ַ�ŵ�����������
			ret = result;
		}
	}
	return ret;
}


template<bool threads, int inst>
void _DefaultAllocTemplate<threads, inst>::DeAllocate(void *p, size_t n)   //���տռ�
{
	//���ж�����ֽڵĴ�С
	if (n > _MAXBYTES)  //���n�������������н�����ܹҵ�����ڴ�飬���ֱ�ӵ���һ��ָ����ͷź���
	{
		malloc_alloc::_DeAllocate(p);
	}
	else        //������ڴ���յ�����������
	{
		_Obj* q = (_Obj*)p;
		_Obj* volatile *myFreeList = _freeList + _GetFreeListIndex(n);
		q->_freeListLink = *myFreeList;
		*myFreeList = q;
	}
}



template<bool threads,int inst>
void* _DefaultAllocTemplate<threads, inst>::_Refill(size_t n)     //n��ʾҪ������ֽڸ���
{
	int nobjs = 20;           //���ڴ�������ʱ��һ��������20��
	char* chunk = _chunkAlloc(n,nobjs);    //��Ϊ����������û�У�����Ҫ���ڴ�������룬������ٹҵ�������������

	if (1 == nobjs)          //ֻ���䵽��һ������
	{
		return chunk;
	}

	_Obj* ret = (_Obj*)chunk;                  //������ĵ�һ��������Ϊ����ֵ
	_Obj* volatile *myFreeList = _freeList+ _GetFreeListIndex(n);
	*myFreeList =(_Obj*)(chunk+n);             //���ڶ�������ĵ�ַ�ŵ�����������
	_Obj* cur= *myFreeList;
	_Obj* next=0;
	cur->_freeListLink = 0;
	for (int i = 2; i < nobjs; ++i)             //��ʣ�µĿ�ҵ�����������
	{
		next= (_Obj*)(chunk + n*i);
		cur->_freeListLink = next;
		cur = next;
	}
	cur->_freeListLink = 0;
	return ret;
}



template<bool threads, int inst>
char* _DefaultAllocTemplate<threads, inst>::_chunkAlloc(size_t size, int& nobjs)  //��ϵͳ�������ڴ�
{
	char* result = 0;
	size_t totalBytes = size*nobjs;        //�ܹ�������ڴ��С
	size_t leftBytes = _endFree - _startFree;      //�ڴ��ʣ��Ĵ�С

	if (leftBytes>=totalBytes)     //���ʣ��Ĵ�С���ڵ�������Ĵ�С���򷵻�������ڴ�
	{
		result = _startFree;
		_startFree += totalBytes;
		return result;
	}
	else if (leftBytes>size)         //���ʣ����ڴ��㹻����һ��size,
	{
		nobjs=(int)(leftBytes/size);
		result = _startFree;
		_startFree +=(nobjs*size);
		return result;
	}
	else            //�ڴ���е��ڴ��Ѿ�����һ��size��
	{
		size_t NewBytes = 2 * totalBytes+_GetRoundUp(_heapSize>>4);       //�ڴ��Ҫ���ٵ��µ�����
		if (leftBytes >0)  //ʣ����ڴ�ҵ�����������
		{
			_Obj* volatile *myFreeList = _freeList + _GetFreeListIndex(leftBytes);
			((_Obj*)_startFree)->_freeListLink = *myFreeList;
			*myFreeList = (_Obj*)_startFree;
		}
		
		//�����µ��ڴ�
		_startFree = (char*)malloc(NewBytes);

		if (0 == _startFree)                   //�������ʧ��
		{
			//�������ʧ�ܵĻ��������ϵͳ�Ѿ�û���ڴ��ˣ���ʱ�����Ǿ�Ҫ��������������һ���n������ڴ�飬�����û�еĻ����Ǿ͵�һ���ռ�������
			for (size_t i = size; i <(size_t)_MAXBYTES;i+=(size_t)_ALIGN)
			{
				_Obj* volatile *myFreeList = _freeList + _GetFreeListIndex(i);
				_Obj* p =*myFreeList;
				if (NULL != p)       //�����������ҵ�һ���ڴ��
				{
					_startFree =(char*)p;                   
					//������ڴ��ժ�������ڴ��
					*myFreeList = p->_freeListLink;
					_endFree = _startFree + i;
					return _chunkAlloc(size, nobjs);  //�ڴ�ؿ��ٺõĻ������ٵ�һ��chunk�����ڴ�
				}
			}

			//Ҫ�����Ҳ����Ļ����͵�һ���ռ����������������ڴ治�㴦�����,Ҫ�ǻ����еĻ��������Զ��׳��쳣
			_endFree = NULL;
			_startFree=(char*)malloc_alloc::_Allocate(NewBytes);
		}	

		//���ٳɹ��ģ��͸���heapSize(��¼�ܹ���ϵͳ�����˶����ڴ�),������_endFree
		_heapSize += NewBytes;
		_endFree = _startFree + NewBytes;
		return _chunkAlloc(size, nobjs);             //�ڴ�ؿ��ٺõĻ������ٵ�һ��chunk�����ڴ�
	}
}


typedef _DefaultAllocTemplate<0,0>  default_alloc;



void TestAllocator()
{
	int *a=(int*)default_alloc::Allocate(40);
}
