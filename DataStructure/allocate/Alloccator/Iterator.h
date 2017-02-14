#pragma once

//五种迭代器的标签
struct InputIteratorTag{};
struct OutputIteratorTag{};
struct ForwardIteratorTag :public InputIteratorTag{};   //前向迭代器类型，公有继承于只读迭代器类型
struct BidirectionalIteratorTag:public ForwardIteratorTag{};  //双向迭代器类型，公有继承于前向迭代器
struct RandomAccessIteratorTag :public BidirectionalIteratorTag{};     //随机迭代器类型，公有继承于双向迭代器



template<typename T,class Distance=int>             //定义只读迭代器的类型,迭代器内嵌五种型别
struct InputIterator
{
	typedef InputIteratorTag  IteratorCategory;       //为只读迭代器重命名
	typedef T                 ValueType;
	typedef Distance          DifferenceType;
	typedef T*                Pointer;
	typedef T&                Reference;
};


//定义只写迭代器的类型
template<typename T, class Distance = int>
struct OutputIterator
{
	typedef OutputIteratorTag  IteratorCategory;
	typedef T                  ValueType;
	typedef Distance           DifferenceType;
	typedef T*                 Pointer;
	typedef T&                 Reference;
};

//前向迭代器类型
template<typename T, class Distance = int>
struct ForwardIterator
{
	typedef ForwardIteratorTag  IteratorCategory;
	typedef T                   ValueType;
	typedef Distance            DifferenceType;
	typedef T*                  Pointer;
	typedef T&                  Reference;
};

//双向迭代器类型
template<typename T, class Distance = int>
struct BidirectionalIterator
{
	typedef BidirectionalIteratorTag  IteratorCategory;
	typedef T                         ValueType;
	typedef Distance                  DifferenceType;
	typedef T*                        Pointer;
	typedef T&                        Reference;
};


//随机迭代器类型
template<typename T, class Distance = int>
struct RandomAccessIterator
{
	typedef RandomAccessIteratorTag  IteratorCategory;
	typedef T                        ValueType;
	typedef Distance                 DifferenceType;
	typedef T*                       Pointer;
	typedef T&                       Reference;
};


//通过迭代器萃取得到迭代器内嵌的五种类型
//如果是原生指针的话，则通过特化实现
template<typename Iterator>               //迭代器的萃取，这个类型的模板参数是一个迭代器类型
struct IteratorTraits
{
	typedef typename Iterator::IteratorCategory IteratorCategory;
	typedef typename Iterator::ValueType        ValueType;
	typedef typename Iterator::DifferenceType   DifferenceType;
	typedef typename Iterator::Pointer          Pointer;
	typedef typename Iterator::Reference        Reference;
};

template<typename T>               //迭代器的萃取，这个类型的模板参数是一个迭代器类型
struct IteratorTraits<T *>
{
	typedef RandomAccessIteratorTag   IteratorCategory;
	typedef T                         ValueType;
	typedef int                       DifferenceType;
	typedef T*                        Pointer;
	typedef T&                        Reference;
};


template<typename T>               //迭代器的萃取，这个类型的模板参数是一个迭代器类型
struct IteratorTraits<const T*>
{
	typedef RandomAccessIteratorTag   IteratorCategory;
	typedef T                         ValueType;
	typedef int                       DifferenceType;
	typedef const T*                  Pointer;
	typedef const T&                  Reference;
};


template<typename Iterator>
size_t Distance(Iterator first, Iterator last)
{
	typedef IteratorTraits<Iterator>::IteratorCategory Category;
	return _Distance(first, last, Category());
}


//利用切片，子类对象可以给父类对象赋值
template<typename Iterator>
size_t _Distance(Iterator first,Iterator last, InputIteratorTag)
{
	size_t n = 0;
	while (first!=last)
	{
		++n;
		++first;
	}
	return n;
}

//随机迭代器,直接进行加减
template<typename Iterator>
size_t _Distance(Iterator first,Iterator last, RandomAccessIteratorTag)
{
	return last - first;
}



//让迭代器移动n步
template<typename Iterator>
void Advance(Iterator& iter,int n)
{
	//萃取迭代器的类型
	typedef typename IteratorTraits<Iterator>::IteratorCategory Category;
	_Advance(iter,n,Category());
}


//前向迭代器只能向前一步一步的访问
template<typename Iterator>
void _Advance(Iterator& iter,int n,ForwardIteratorTag)
{
	assert(n>=0);         //前向迭代器只能向前走
	while (n--)
		iter++;	
}


//双向迭代器可以正着走，也可以倒着走
template<typename Iterator>
void _Advance(Iterator& iter, int n, BidirectionalIteratorTag)
{
	if (n > 0)
	{
		while (n--)
			iter++;
	}
	else
	{
		while (n++)
			iter--;
	}
}


//随机迭代器可以直接走n步
template<typename Iterator>
void _Advance(Iterator& iter, int n, RandomAccessIteratorTag)
{
	iter += n;
}


