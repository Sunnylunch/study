#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;


///////////////////////////////////////////////////////////////////////
////////////一级空间配置器，当是大块内存时调用，直接向系统申请
////////////__malloc_alloc_template

typedef void(*MALLOCALLOC)();           //将void (*)()   重命名成MALLOCALLOC

template<int inst>
class _MallocAllocTemplate
{
private:
	static void* _OomMalloc(size_t);       //malloc失败的时候调用的函数
	static MALLOCALLOC _MallocAllocOomHandler;         //函数指针，内存不足的时候的处理机制
public:
	static void* _Allocate(size_t n)                        //分配空间n个字节的空间
	{
		void *result=0;
		result = malloc(n);
		if (0 == result)                    //若果malloc失败，则就调OOM_malloc
			_OomMalloc(n);

		return result;
	}

	static void _DeAllocate(void *p)                //释放这块空间
	{
		free(p);
	}

	static MALLOCALLOC _SetMallocHandler(MALLOCALLOC f)    //这是一个函数，参数是一个函数指针，返回值也是一个函数指针
	{
		MALLOCALLOC old = _MallocAllocOomHandler;
		_MallocAllocOomHandler = f;              //将内存分配失败的句柄设置为f(让它指向一个内存失败了，让系统去释放其他地方空间的函数)
		return old;
	}
};

template<int inst>
void(* _MallocAllocTemplate<inst>::_MallocAllocOomHandler)()=0;    //默认不设置内存不足处理机制

template<int inst>
void* _MallocAllocTemplate<inst>::_OomMalloc(size_t n)
{
	MALLOCALLOC _MyMallocHandler;     //定义一个函数指针
	void *result;                
	while (1)
	{
		_MyMallocHandler = _MallocAllocOomHandler;
		if (0 == _MyMallocHandler)                  //没有设置内存不足处理机制
			throw std::bad_alloc();                  //则抛出异常

		(*_MyMallocHandler)();                 //调用内存不足处理的函数，申请释放其他地方的内存
		if (result = malloc(n))                //重新申请内存
			break;
	}
	return result;                              //申请成功时，则返回这块内存的地址
}

typedef _MallocAllocTemplate<0> malloc_alloc;





//////////////////////////////////////////////////////////////////////////////
//////////////////二级空间配置器__default_alloc_template

enum { _ALIGN = 8 };              //按照基准值8的倍数进行内存操作
enum { _MAXBYTES = 128 };        //自由链表中最大的块的大小是128
enum { _NFREELISTS = 16 };       //自由链表的长度，等于_MAXBYTES/_ALIGN
template <bool threads, int inst>  //非模板类型参数
class _DefaultAllocTemplate
{
	union _Obj                      //自由链表结点的类型
	{
		_Obj* _freeListLink;         //指向自由链表结点的指针
		char _clientData[1];          //this client sees
	};
private:
	static char* _startFree;             //内存池的头指针
	static char* _endFree;               //内存池的尾指针
	static size_t _heapSize;              //记录内存池已经向系统申请了多大的内存
	static _Obj* volatile _freeList[_NFREELISTS];    //自由链表
private:
	static size_t _GetFreeListIndex(size_t bytes)   //得到这个字节对应在自由链表中应取的位置
	{
		return (bytes +(size_t) _ALIGN - 1) / (size_t)_ALIGN - 1;      
	}

	static size_t _GetRoundUp(size_t bytes)        //对这个字节向上取成8的倍数
	{
		return (bytes + (size_t)_ALIGN - 1)&(~(_ALIGN-1));     //将n向上取成8的倍数
	}


	static void* _Refill(size_t n);          //在自由链表中申请内存,n表示要的内存的大小
	static char* _chunkAlloc(size_t size,int& nobjs);    //在内存池中申请内存nobjs个对象，每个对象size个大小
public:
	static void* Allocate(size_t n);      //n要大于0
	static void DeAllocate(void *p,size_t n);        //n要不等于0
};


template<bool threads,int inst>
char* _DefaultAllocTemplate<threads,inst>::_startFree = 0;        //内存池的头指针

template<bool threads, int inst>
char* _DefaultAllocTemplate<threads, inst>::_endFree=0;           //内存池的尾指针

template<bool threads, int inst>
size_t _DefaultAllocTemplate<threads, inst>::_heapSize = 0;              //记录内存池已经向系统申请了多大的内存

template<bool threads, int inst>
typename _DefaultAllocTemplate<threads, inst>::_Obj* volatile      //前面加typename表示后面是个类型
_DefaultAllocTemplate<threads, inst>::_freeList[_NFREELISTS] = {0};    //自由链表





template<bool threads, int inst>
void* _DefaultAllocTemplate<threads, inst>::Allocate(size_t n)    //分配空间
{
	void *ret;
	//先判断要分配的空间大小是不是大于128个字节
	if (n>_MAXBYTES)      //大于_MAXBYTES个字节则认为是大块内存，直接调用一级空间配置器
	{
		ret = malloc_alloc::_Allocate(n);
	}
	else       //否则就去自由链表中找
	{
		_Obj* volatile *myFreeList = _freeList+_GetFreeListIndex(n);  //让myFreeList指向自由链表中n向上取8的整数倍
		_Obj* result = *myFreeList;
		if (result == 0)  //这个结点下面没有挂内存，则就要去内存池中申请
		{
			ret = _Refill(_GetRoundUp(n));      //到内存池中申请
		}
		else            //已经在自由链表上找到了内存
		{
			*myFreeList= result->_freeListLink;      //把第二块空间的地址放到自由链表上
			ret = result;
		}
	}
	return ret;
}


template<bool threads, int inst>
void _DefaultAllocTemplate<threads, inst>::DeAllocate(void *p, size_t n)   //回收空间
{
	//先判断这个字节的大小
	if (n > _MAXBYTES)  //如果n大于自由链表中结点所能挂的最大内存块，则就直接调用一级指针的释放函数
	{
		malloc_alloc::_DeAllocate(p);
	}
	else        //将这块内存回收到自由链表中
	{
		_Obj* q = (_Obj*)p;
		_Obj* volatile *myFreeList = _freeList + _GetFreeListIndex(n);
		q->_freeListLink = *myFreeList;
		*myFreeList = q;
	}
}



template<bool threads,int inst>
void* _DefaultAllocTemplate<threads, inst>::_Refill(size_t n)     //n表示要申请的字节个数
{
	int nobjs = 20;           //向内存池申请的时候一次性申请20个
	char* chunk = _chunkAlloc(n,nobjs);    //因为现在链表中没有，所以要想内存池中申请，多余的再挂到自由链表下面

	if (1 == nobjs)          //只分配到了一个对象
	{
		return chunk;
	}

	_Obj* ret = (_Obj*)chunk;                  //将申请的第一个对象作为返回值
	_Obj* volatile *myFreeList = _freeList+ _GetFreeListIndex(n);
	*myFreeList =(_Obj*)(chunk+n);             //将第二个对象的地址放到自由链表中
	_Obj* cur= *myFreeList;
	_Obj* next=0;
	cur->_freeListLink = 0;
	for (int i = 2; i < nobjs; ++i)             //将剩下的块挂到自由链表上
	{
		next= (_Obj*)(chunk + n*i);
		cur->_freeListLink = next;
		cur = next;
	}
	cur->_freeListLink = 0;
	return ret;
}



template<bool threads, int inst>
char* _DefaultAllocTemplate<threads, inst>::_chunkAlloc(size_t size, int& nobjs)  //向系统中申请内存
{
	char* result = 0;
	size_t totalBytes = size*nobjs;        //总共请求的内存大小
	size_t leftBytes = _endFree - _startFree;      //内存池剩余的大小

	if (leftBytes>=totalBytes)     //如果剩余的大小大于等于申请的大小，则返回这个这内存
	{
		result = _startFree;
		_startFree += totalBytes;
		return result;
	}
	else if (leftBytes>size)         //如果剩余的内存足够分配一个size,
	{
		nobjs=(int)(leftBytes/size);
		result = _startFree;
		_startFree +=(nobjs*size);
		return result;
	}
	else            //内存池中的内存已经不够一个size了
	{
		size_t NewBytes = 2 * totalBytes+_GetRoundUp(_heapSize>>4);       //内存池要开辟的新的容量
		if (leftBytes >0)  //剩余的内存挂到自由链表上
		{
			_Obj* volatile *myFreeList = _freeList + _GetFreeListIndex(leftBytes);
			((_Obj*)_startFree)->_freeListLink = *myFreeList;
			*myFreeList = (_Obj*)_startFree;
		}
		
		//开辟新的内存
		_startFree = (char*)malloc(NewBytes);

		if (0 == _startFree)                   //如果开辟失败
		{
			//如果开辟失败的话，则表明系统已经没有内存了，这时候我们就要到自由链表中找一块比n还大的内存块，如果还没有的话，那就掉一级空间配置器
			for (size_t i = size; i <(size_t)_MAXBYTES;i+=(size_t)_ALIGN)
			{
				_Obj* volatile *myFreeList = _freeList + _GetFreeListIndex(i);
				_Obj* p =*myFreeList;
				if (NULL != p)       //在自由链表找到一块内存块
				{
					_startFree =(char*)p;                   
					//将这个内存块摘下来给内存池
					*myFreeList = p->_freeListLink;
					_endFree = _startFree + i;
					return _chunkAlloc(size, nobjs);  //内存池开辟好的话，就再调一次chunk分配内存
				}
			}

			//要是再找不到的话，就调一级空间配置器，其中有内存不足处理机制,要是还不行的话，他会自动抛出异常
			_endFree = NULL;
			_startFree=(char*)malloc_alloc::_Allocate(NewBytes);
		}	

		//开辟成功的，就更新heapSize(记录总共向系统申请了多少内存),，更新_endFree
		_heapSize += NewBytes;
		_endFree = _startFree + NewBytes;
		return _chunkAlloc(size, nobjs);             //内存池开辟好的话，就再调一次chunk分配内存
	}
}


typedef _DefaultAllocTemplate<0,0>  default_alloc;



void TestAllocator()
{
	int *a=(int*)default_alloc::Allocate(40);
}
