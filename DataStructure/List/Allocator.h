#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<utility>
using namespace std;

#include<stdarg.h>
//#define __DEBUG__

FILE* fOut = fopen("debug.txt", "w");
static string GetFileName(const string& path)
{
	char ch = '/';

#ifdef _WIN32
	ch = '\\';
#endif

	size_t pos = path.rfind(ch);
	if (pos == string::npos)
		return path;
	else
		return path.substr(pos + 1);
}


inline static void __trace_debug(const char* function, const char* filename,
	int line, char* format, ...)
{
#ifdef __DEBUG__

	fprintf(fOut, "[%s:%d]%s", GetFileName(filename).c_str(), line, function);
	//��fOut����stdout���Ǵ�ӡ����׼�������

	//��ӡ�û���Ϣ
	va_list args;                      //�����ĸ���
	va_start(args, format);
	vfprintf(fOut, format, args);
	va_end(args);

#endif     //__DEBUG__
}


#define __TRACE_DEBUG(...) \
	__trace_debug(__FUNCTION__, __FILE__, __LINE__, __VA_ARGS__);










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
	static void* Allocate(size_t n)                        //����ռ�n���ֽڵĿռ�
	{
		__TRACE_DEBUG("һ���ռ�����������%u�ֽ�\n", n);
		void *result = 0;
		result = malloc(n);
		if (0 == result)                    //����mallocʧ�ܣ���͵�OOM_malloc
			_OomMalloc(n);

		return result;
	}

	static void DeAllocate(void *p, size_t n)                //�ͷ����ռ�
	{
		__TRACE_DEBUG("һ���ռ��������ͷ�%u�ֽ�\n", n);
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
void(*_MallocAllocTemplate<inst>::_MallocAllocOomHandler)() = 0;    //Ĭ�ϲ������ڴ治�㴦�����

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
		return (bytes + (size_t)_ALIGN - 1) / (size_t)_ALIGN - 1;
	}

	static size_t _GetRoundUp(size_t bytes)        //������ֽ�����ȡ��8�ı���
	{
		return (bytes + (size_t)_ALIGN - 1)&(~(_ALIGN - 1));     //��n����ȡ��8�ı���
	}


	static void* _Refill(size_t n);          //�����������������ڴ�,n��ʾҪ���ڴ�Ĵ�С
	static char* _chunkAlloc(size_t size, int& nobjs);    //���ڴ���������ڴ�nobjs������ÿ������size����С
public:
	static void* Allocate(size_t n);      //nҪ����0
	static void DeAllocate(void *p, size_t n);        //nҪ������0
};


template<bool threads, int inst>
char* _DefaultAllocTemplate<threads, inst>::_startFree = 0;        //�ڴ�ص�ͷָ��

template<bool threads, int inst>
char* _DefaultAllocTemplate<threads, inst>::_endFree = 0;           //�ڴ�ص�βָ��

template<bool threads, int inst>
size_t _DefaultAllocTemplate<threads, inst>::_heapSize = 0;              //��¼�ڴ���Ѿ���ϵͳ�����˶����ڴ�

template<bool threads, int inst>
typename _DefaultAllocTemplate<threads, inst>::_Obj* volatile      //ǰ���typename��ʾ�����Ǹ�����
_DefaultAllocTemplate<threads, inst>::_freeList[_NFREELISTS] = { 0 };    //��������





template<bool threads, int inst>
void* _DefaultAllocTemplate<threads, inst>::Allocate(size_t n)    //����ռ�
{
	__TRACE_DEBUG("�����ռ�����������%u�ֽ�\n", n);
	void *ret;
	//���ж�Ҫ����Ŀռ��С�ǲ��Ǵ���128���ֽ�
	if (n>_MAXBYTES)      //����_MAXBYTES���ֽ�����Ϊ�Ǵ���ڴ棬ֱ�ӵ���һ���ռ�������
	{
		ret = malloc_alloc::Allocate(n);
	}
	else       //�����ȥ������������
	{
		_Obj* volatile *myFreeList = _freeList + _GetFreeListIndex(n);  //��myFreeListָ������������n����ȡ8��������
		_Obj* result = *myFreeList;
		if (result == 0)  //����������û�й��ڴ棬���Ҫȥ�ڴ��������
		{
			ret = _Refill(_GetRoundUp(n));      //���ڴ��������
		}
		else            //�Ѿ��������������ҵ����ڴ�
		{
			__TRACE_DEBUG("�����������ϵ�%u��λ��ȡ�ڴ��\n", _GetFreeListIndex(n));
			*myFreeList = result->_freeListLink;      //�ѵڶ���ռ�ĵ�ַ�ŵ�����������
			ret = result;
		}
	}
	return ret;
}


template<bool threads, int inst>
void _DefaultAllocTemplate<threads, inst>::DeAllocate(void *p, size_t n)   //���տռ�
{
	__TRACE_DEBUG("�����ռ��������ͷ�0x%p,%u���ֽ�\n", p, n);
	//���ж�����ֽڵĴ�С
	if (n > _MAXBYTES)  //���n�������������н�����ܹҵ�����ڴ�飬���ֱ�ӵ���һ��ָ����ͷź���
	{
		malloc_alloc::DeAllocate(p, n);
	}
	else        //������ڴ���յ�����������
	{
		_Obj* q = (_Obj*)p;
		_Obj* volatile *myFreeList = _freeList + _GetFreeListIndex(n);
		q->_freeListLink = *myFreeList;
		*myFreeList = q;
	}
}



template<bool threads, int inst>
void* _DefaultAllocTemplate<threads, inst>::_Refill(size_t n)     //n��ʾҪ������ֽڸ���
{
	int nobjs = 20;           //���ڴ�������ʱ��һ��������20��
	char* chunk = _chunkAlloc(n, nobjs);    //��Ϊ����������û�У�����Ҫ���ڴ�������룬������ٹҵ�������������

	if (1 == nobjs)          //ֻ���䵽��һ������
	{
		return chunk;
	}
	__TRACE_DEBUG("��ʣ��%u���ڴ���������������\n", nobjs - 1);
	_Obj* ret = (_Obj*)chunk;                  //������ĵ�һ��������Ϊ����ֵ
	_Obj* volatile *myFreeList = _freeList + _GetFreeListIndex(n);
	*myFreeList = (_Obj*)(chunk + n);             //���ڶ�������ĵ�ַ�ŵ�����������
	_Obj* cur = *myFreeList;
	_Obj* next = 0;
	cur->_freeListLink = 0;
	for (int i = 2; i < nobjs; ++i)             //��ʣ�µĿ�ҵ�����������
	{
		next = (_Obj*)(chunk + n*i);
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
	__TRACE_DEBUG("ʣ��%u�ڴ棬����%u�ڴ�\n", leftBytes, totalBytes);
	if (leftBytes >= totalBytes)     //���ʣ��Ĵ�С���ڵ�������Ĵ�С���򷵻�������ڴ�
	{
		__TRACE_DEBUG("���ڴ��������%u�ڴ�\n", totalBytes);
		result = _startFree;
		_startFree += totalBytes;
		return result;
	}
	else if (leftBytes>size)         //���ʣ����ڴ��㹻����һ��size,
	{
		__TRACE_DEBUG("�ڴ��ֻ��%u���ڴ�\n", leftBytes);
		nobjs = (int)(leftBytes / size);
		result = _startFree;
		_startFree += (nobjs*size);
		return result;
	}
	else            //�ڴ���е��ڴ��Ѿ�����һ��size��
	{
		size_t NewBytes = 2 * totalBytes + _GetRoundUp(_heapSize >> 4);       //�ڴ��Ҫ���ٵ��µ�����
		if (leftBytes >0)  //ʣ����ڴ�ҵ�����������
		{
			__TRACE_DEBUG("��ʣ��%u�ڴ�ҵ�����������\n", leftBytes);
			_Obj* volatile *myFreeList = _freeList + _GetFreeListIndex(leftBytes);
			((_Obj*)_startFree)->_freeListLink = *myFreeList;
			*myFreeList = (_Obj*)_startFree;
		}

		//�����µ��ڴ�
		_startFree = (char*)malloc(NewBytes);

		if (0 == _startFree)                   //�������ʧ��
		{
			//�������ʧ�ܵĻ��������ϵͳ�Ѿ�û���ڴ��ˣ���ʱ�����Ǿ�Ҫ��������������һ���n������ڴ�飬�����û�еĻ����Ǿ͵�һ���ռ�������
			for (size_t i = size; i <(size_t)_MAXBYTES; i += (size_t)_ALIGN)
			{
				_Obj* volatile *myFreeList = _freeList + _GetFreeListIndex(i);
				_Obj* p = *myFreeList;
				if (NULL != p)       //�����������ҵ�һ���ڴ��
				{
					__TRACE_DEBUG("����������������ڴ���������ڴ�\n");
					_startFree = (char*)p;
					//������ڴ��ժ�������ڴ��
					*myFreeList = p->_freeListLink;
					_endFree = _startFree + i;
					return _chunkAlloc(size, nobjs);  //�ڴ�ؿ��ٺõĻ������ٵ�һ��chunk�����ڴ�
				}
			}

			//Ҫ�����Ҳ����Ļ����͵�һ���ռ����������������ڴ治�㴦�����,Ҫ�ǻ����еĻ��������Զ��׳��쳣
			_endFree = NULL;
			_startFree = (char*)malloc_alloc::Allocate(NewBytes);
		}

		//���ٳɹ��ģ��͸���heapSize(��¼�ܹ���ϵͳ�����˶����ڴ�),������_endFree
		_heapSize += NewBytes;
		_endFree = _startFree + NewBytes;
		return _chunkAlloc(size, nobjs);             //�ڴ�ؿ��ٺõĻ������ٵ�һ��chunk�����ڴ�
	}
}

#ifdef __USE_MALLOC                              //�������__USE_MALLOC����ʹ��һ���ռ�������
typedef _MallocAllocTemplate<0> Alloc;
#else                                            //���û��ʹ�õĻ�������ö����ռ�������
typedef _DefaultAllocTemplate<false, 0> Alloc;
#endif      //__USE_MALLOC


//���һ���ӿ�SimpleAlloc,���������
template<typename T, typename _ALLOC>
class SimpleAlloc
{
public:
	static T* Allocate(size_t n)           //����n���������
	{
		//��void* ת����T*
		return 0 == n ? 0 : (T*)_ALLOC::Allocate(sizeof(T)*n);
	}

	static T* Allocate(void)               //����һ���������
	{
		return (T*)_ALLOC::Allocate(sizeof(T));
	}

	static void DeAllocate(T* ptr, size_t n)
	{
		if (n != 0)                //�ͷŵĶ���Ϊ0
			_ALLOC::DeAllocate(ptr, sizeof(T)*n);
	}

	static void DeAllocate(T* ptr)
	{
		_ALLOC::DeAllocate(ptr, sizeof(T));
	}
};


//
//void Test1()
//{
//	vector<pair<void*, size_t>> v;
//	v.push_back(make_pair(_DefaultAllocTemplate<false, 0>::Allocate(129), 129));
//
//	for (size_t i = 0; i < 21; ++i)
//	{
//		v.push_back(make_pair(_DefaultAllocTemplate<false, 0>::Allocate(12), 12));
//	}
//
//	while (!v.empty())
//	{
//		_DefaultAllocTemplate<false, 0>::DeAllocate(v.back().first, v.back().second);
//		v.pop_back();
//	}
//
//	for (size_t i = 0; i < 21; ++i)
//	{
//		v.push_back(make_pair(_DefaultAllocTemplate<false, 0>::Allocate(7), 7));
//	}
//
//	for (size_t i = 0; i < 10; ++i)
//	{
//		v.push_back(make_pair(_DefaultAllocTemplate<false, 0>::Allocate(16), 16));
//	}
//
//	while (!v.empty())
//	{
//		_DefaultAllocTemplate<false, 0>::DeAllocate(v.back().first, v.back().second);
//		v.pop_back();
//	}
//}
//
//
//
//void Test3()
//{
//	cout << "����ϵͳ���ڴ�ľ�" << endl;
//
//	SimpleAlloc<char, Alloc>::Allocate(1024 * 1024 * 1024);
//	SimpleAlloc<char, Alloc>::Allocate(1024 * 1024);
//
//	//���ò��ԣ�˵��ϵͳ����С���ڴ���������Ǻ�ǿ�ġ�
//	for (int i = 0; i< 100000; ++i)
//	{
//		char*p1 = SimpleAlloc<char, Alloc>::Allocate(128);
//	}
//
//	cout << "�������" << endl;
//}


