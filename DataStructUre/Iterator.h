#pragma once

//���ֵ������ı�ǩ
struct InputIteratorTag{};
struct OutputIteratorTag{};
struct ForwardIteratorTag :public InputIteratorTag{};   //ǰ����������ͣ����м̳���ֻ������������
struct BidirectionalIteratorTag:public ForwardIteratorTag{};  //˫����������ͣ����м̳���ǰ�������
struct RandomAccessIteratorTag :public BidirectionalIteratorTag{};     //������������ͣ����м̳���˫�������



template<typename T,class Distance=int>             //����ֻ��������������,��������Ƕ�����ͱ�
struct InputIterator
{
	typedef InputIteratorTag  IteratorCategory;       //Ϊֻ��������������
	typedef T                 ValueType;
	typedef Distance          DifferenceType;
	typedef T*                Pointer;
	typedef T&                Reference;
};


//����ֻд������������
template<typename T, class Distance = int>
struct OutputIterator
{
	typedef OutputIteratorTag  IteratorCategory;
	typedef T                  ValueType;
	typedef Distance           DifferenceType;
	typedef T*                 Pointer;
	typedef T&                 Reference;
};

//ǰ�����������
template<typename T, class Distance = int>
struct ForwardIterator
{
	typedef ForwardIteratorTag  IteratorCategory;
	typedef T                   ValueType;
	typedef Distance            DifferenceType;
	typedef T*                  Pointer;
	typedef T&                  Reference;
};

//˫�����������
template<typename T, class Distance = int>
struct BidirectionalIterator
{
	typedef BidirectionalIteratorTag  IteratorCategory;
	typedef T                         ValueType;
	typedef Distance                  DifferenceType;
	typedef T*                        Pointer;
	typedef T&                        Reference;
};


//�������������
template<typename T, class Distance = int>
struct RandomAccessIterator
{
	typedef RandomAccessIteratorTag  IteratorCategory;
	typedef T                        ValueType;
	typedef Distance                 DifferenceType;
	typedef T*                       Pointer;
	typedef T&                       Reference;
};


//ͨ����������ȡ�õ���������Ƕ����������
//�����ԭ��ָ��Ļ�����ͨ���ػ�ʵ��
template<typename Iterator>               //����������ȡ��������͵�ģ�������һ������������
struct IteratorTraits
{
	typedef typename Iterator::IteratorCategory IteratorCategory;
	typedef typename Iterator::ValueType        ValueType;
	typedef typename Iterator::DifferenceType   DifferenceType;
	typedef typename Iterator::Pointer          Pointer;
	typedef typename Iterator::Reference        Reference;
};

template<typename T>               //����������ȡ��������͵�ģ�������һ������������
struct IteratorTraits<T *>
{
	typedef RandomAccessIteratorTag   IteratorCategory;
	typedef T                         ValueType;
	typedef int                       DifferenceType;
	typedef T*                        Pointer;
	typedef T&                        Reference;
};


template<typename T>               //����������ȡ��������͵�ģ�������һ������������
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


//������Ƭ�����������Ը��������ֵ
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

//���������,ֱ�ӽ��мӼ�
template<typename Iterator>
size_t _Distance(Iterator first,Iterator last, RandomAccessIteratorTag)
{
	return last - first;
}



//�õ������ƶ�n��
template<typename Iterator>
void Advance(Iterator& iter,int n)
{
	//��ȡ������������
	typedef typename IteratorTraits<Iterator>::IteratorCategory Category;
	_Advance(iter,n,Category());
}


//ǰ�������ֻ����ǰһ��һ���ķ���
template<typename Iterator>
void _Advance(Iterator& iter,int n,ForwardIteratorTag)
{
	assert(n>=0);         //ǰ�������ֻ����ǰ��
	while (n--)
		iter++;	
}


//˫����������������ߣ�Ҳ���Ե�����
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


//�������������ֱ����n��
template<typename Iterator>
void _Advance(Iterator& iter, int n, RandomAccessIteratorTag)
{
	iter += n;
}


