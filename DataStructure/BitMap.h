#pragma once
#include<vector>
using namespace std;


class BitMap
{
public:
	BitMap(size_t range)                 //给定位图所能表示的范围
	{
		_bitmap.resize(range/32+1);      //设置大小
	}

	void Set(size_t num)         //置1
	{
		size_t index = num / 32;     //计算所在下标
		size_t bit = num % 32;       //得位所在位置
		_bitmap[index] |= (1 << bit);
	}

	void ReSet(size_t num)           //置零
	{
		size_t index = num / 32;         //计算所在下标
		size_t bit = num % 32;          //得位所在位置
		_bitmap[index] &= (~(1 << bit));
	}

	bool Test(size_t num)
	{
		size_t index = num / 32;         //计算所在下标
		size_t bit = num % 32;          //得位所在位置
		return (_bitmap[index]>>num)&1;
	}
private:
	vector<size_t> _bitmap;
};