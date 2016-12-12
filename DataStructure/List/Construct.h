#pragma once

//构造函数
template<typename T1, typename T2>
inline void Construct(T1* ptr, const T2& value)
{
	new(ptr)T1(value);           //定位new表达式对这块空间进行初始化,T1是开辟空间的类型，T2是空间里面值的类型
}


//析构函数
template<typename T>
inline void Destory(T* ptr)           //将这块空间析构掉
{
	ptr->~T();
}