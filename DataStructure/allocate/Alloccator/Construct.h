#pragma once

//���캯��
template<typename T1, typename T2>
inline void Construct(T1* ptr, const T2& value)
{
	new(ptr)T1(value);           //��λnew���ʽ�����ռ���г�ʼ��,T1�ǿ��ٿռ�����ͣ�T2�ǿռ�����ֵ������
}


//��������
template<typename T>
inline void Destory(T* ptr)           //�����ռ�������
{
	ptr->~T();
}