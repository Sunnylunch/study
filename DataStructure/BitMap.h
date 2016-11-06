#pragma once
#include<vector>
using namespace std;


class BitMap
{
public:
	BitMap(size_t range)                 //����λͼ���ܱ�ʾ�ķ�Χ
	{
		_bitmap.resize(range/32+1);      //���ô�С
	}

	void Set(size_t num)         //��1
	{
		size_t index = num / 32;     //���������±�
		size_t bit = num % 32;       //��λ����λ��
		_bitmap[index] |= (1 << bit);
	}

	void ReSet(size_t num)           //����
	{
		size_t index = num / 32;         //���������±�
		size_t bit = num % 32;          //��λ����λ��
		_bitmap[index] &= (~(1 << bit));
	}

	bool Test(size_t num)
	{
		size_t index = num / 32;         //���������±�
		size_t bit = num % 32;          //��λ����λ��
		return (_bitmap[index]>>num)&1;
	}
private:
	vector<size_t> _bitmap;
};