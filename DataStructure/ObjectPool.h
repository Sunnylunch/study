#pragma once
#include<iostream>
#include<vector>
#include<time.h>
using namespace std;
//��������ʵ���ڴ�أ�ÿһ����㶼����һ���ڴ�
template<typename T>
class ObjectPool
{
	struct BlockNode         //ÿһ���������
	{ 
		void* _memory;        //ָ��һ���Ѿ�������ڴ�
		BlockNode * _next;    //ָ����һ�����
		size_t _objNum;       //��¼����ڴ��ж���ĸ���

		BlockNode(size_t objNum)
			:_objNum(objNum)
			, _next(NULL)
		{
			_memory = malloc(_objNum*_itemSize);
		}

		~BlockNode()
		{
			free(_memory);
			_memory = NULL;
			_next = NULL;
			_objNum = 0;
		}
	};
protected:
	size_t _countIn;      //��ǰ�������õļ���
	BlockNode* _frist;    //ָ�������ͷ
	BlockNode* _last;     //ָ�������β
	size_t _maxNum;        //��¼�ڴ����������
	static size_t _itemSize;   //��������Ĵ�С
	T* _lastDelete;        //ָ�������ͷŵ��Ǹ�����Ŀռ�
public:
	ObjectPool(size_t initNum = 32, size_t maxNum = 100000)  //Ĭ���ʼ�ڴ����32������һ���ڴ�������maxNum������
		:_countIn(0)
		, _maxNum(maxNum)
		, _lastDelete(NULL)
	{
		_frist = _last =new BlockNode(initNum);   //�ȿ���һ����㣬������������ڴ���ܹ����initNum������
	}

	~ObjectPool()
	{
		Destory();
	}

	T* New()                   //�����ڴ�
	{
		if (_lastDelete)         //�ȵ��ͷ��Ѿ����겢�һ��������ڴ���ȥ��
		{
			T* object = _lastDelete;
			_lastDelete = *((T**)_lastDelete);  //��_lastDeleteת����T**��*������ȡ����T*��Ҳ����ȡ��ǰT*���ʹ�С�ĵ�Ԫ
			return new(object) T();        //������ڴ��ôӶ�λnew��ʼ��һ��
		}

		//�жϻ���û���Ѿ�������ڴ��һ�δʹ��,���û���ڴ�Ļ���Ҫ�ٷ����ڴ�
		if (_countIn >= _last->_objNum)     //���ڵ��ڱ�ʾû���ˣ���ʱ���Ҫ�����ڴ���
		{
			size_t size =2*_countIn;
			if (size > _maxNum)            //�������С���ܳ���maxNum�����û�������Զ�������
				size = _maxNum;
			_last->_next = new BlockNode(size);
			_last = _last->_next;
			_countIn = 0;
		}

		//�����Ѿ�����õ�δ��ʹ�õ��ڴ�
		T* object =(T*)((char*)_last->_memory + _countIn*_itemSize);
		_countIn++;
		return new(object) T();        //�����ռ����ض�λnew��ʼ��һ��
	}

	void Destory()
	{
		BlockNode *cur = _frist;
		while (cur)
		{
			BlockNode* del = cur;
			cur = cur->_next;
			delete del;            //���Զ�����~BlockNode()
		}
		_frist = _last = NULL;
	}

	void Delete(T* object)          //�ͷ��ڴ�
	{
		if (object)
		{
			object->~T();        
			*((T**)object) = _lastDelete;      //��_lastDelete���汣��ĵ�ַ�浽tmpָ��ռ��ǰT*��С�Ŀռ�����
			_lastDelete = object;
		}
	}

protected:
	static size_t GetItemSize()
	{
		if (sizeof(T)>sizeof(T*))
		{
			return sizeof(T);
		}
		else
		{
			return sizeof(T*);
		}
	}
};

template<typename T>
size_t ObjectPool<T>::_itemSize =ObjectPool<T>::GetItemSize();          //�����ʼ����̬����_itemSize

