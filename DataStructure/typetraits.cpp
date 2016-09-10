#include<iostream>
#include<string>
using namespace std;

struct TrueType
{
	bool Get()
	{
		return true;
    }
};

struct FalseType
{
	bool Get()
	{
		return false;
	}
};

template<typename T>
class TypeTraits
{
public:
	typedef FalseType IsPODType;     //将FalseType重命名
};


//将基本数据类型全部特化
template<>
class TypeTraits<int>
{
public:
	typedef TrueType IsPODType;
};

template<>
class TypeTraits<unsigned int>
{
public:
	typedef TrueType IsPODType;
};

template<>
class TypeTraits<short>
{
public:
	typedef TrueType IsPODType;
};

template<>
class TypeTraits<unsigned short>
{
public:
	typedef TrueType IsPODType;
};


template<>
class TypeTraits<char>
{
public:
	typedef TrueType IsPODType;
};

template<>
class TypeTraits<unsigned char>
{
public:
	typedef TrueType IsPODType;
};


template<>
class TypeTraits<float>
{
public:
	typedef TrueType IsPODType;
};

template<>
class TypeTraits<double>
{
public:
	typedef TrueType IsPODType;
};


template<>
class TypeTraits<long>
{
public:
	typedef TrueType IsPODType;
};

template<>
class TypeTraits<long long>
{
public:
	typedef TrueType IsPODType;
};


template<>
class TypeTraits<unsigned long long>
{
public:
	typedef TrueType IsPODType;
};



template<>
class TypeTraits<unsigned long>
{
public:
	typedef TrueType IsPODType;
};

//实现一个可以根据类型而选择拷贝方式的函数
template<typename T>
void Copy(T *dest, T* src, int sz)
{
	if (TypeTraits<T>::IsPODType().Get() == 1)
	{
		memmove(dest, src, sz*sizeof(T));
	}
	else
	{
		for (int i = 0; i < sz; i++)
		{
			dest[i] = src[i];
		}
	}
}

void test()
{
	//int arr[10] = { 1, 5, 8, 9, 6, 3, 4, 7, 0, 2 };
	////int arr1[10];
	////Copy(arr1,arr,10);
	//string s1[3] = {"aaaaa","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","ccccccccccccccccc"};
	//string s2[3];
	//Copy(s2,s1,3);
	//cout << s2[0]<<s2[1]<<s2[2]<< endl;
	string s;
	cout << sizeof(s) << endl;
}


int main()
{
	test();
	system("pause");
	return 0;
}