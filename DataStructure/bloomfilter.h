#pragma once
#include<vector>
using namespace std;

struct _HashFunc1
{
	size_t operator()(const string& str)
	{
		size_t num=0;
		for (int i = 0; i < (int)str.size();i++)
		{
			num = num * 131 +str[i];
		}
		return num;
	}
};

struct _HashFunc2
{
	size_t operator()(const string& str)
	{
		size_t num=0;
		for (int i =0; i < (int)str.size(); i++)
		{
			num = num * 65599 + str[i];
		}
		return num;
	}
};

struct _HashFunc3
{
	size_t operator()(const string& str)
	{
		size_t magic = 63689;
		size_t num = 0;
		for (int i = 0; i < (int)str.size(); i++)
		{
			num = num *magic + str[i];
			magic *= 378551;
		}
		return num;
	}
};


struct _HashFunc4
{
	size_t operator()(const string& str)
	{
		size_t num = 0;
		for (int i = 0; i < (int)str.size(); i++)
		{
			if ((i & 1) == 0)
			{
				num ^= ((num << 7) ^ str[i] ^ (num >> 3));
			}
			else
			{
				num^= (~((num << 11) ^ str[i]^ (num >> 5)));
			}
		}
		return num;
	}
};


struct _HashFunc5
{
	size_t operator()(const string& str)
	{
		if (str.empty())
			return 0;
		size_t num = 5381;
		for (int i = 0; i < (int)str.size(); i++)
		{
			num =num* 33 ^str[i];
		}
		return num;
	}
};


//支持Reset的bloomfliter

template<typename K=string
	,class HashFunc1=_HashFunc1
	, class HashFunc2 = _HashFunc2
	, class HashFunc3= _HashFunc3
	, class HashFunc4= _HashFunc4
	, class HashFunc5 = _HashFunc5>
class BloomFilter
{
public:
	BloomFilter(size_t range)
	{
		_bitmap.resize(range*5);           //为了减少误判，提高精度，用5个位置来表示一个数
	}

	void Set(const K& key)          //要设置为1，必须将5个位置都设置
	{
		size_t index1 = HashFunc1()(key) % _bitmap.size();
		size_t index2 = HashFunc2()(key) % _bitmap.size();
		size_t index3 = HashFunc3()(key) % _bitmap.size();
		size_t index4 = HashFunc4()(key) % _bitmap.size();
		size_t index5 = HashFunc5()(key) % _bitmap.size();

		_bitmap[index1]++;
		_bitmap[index2]++;
		_bitmap[index3]++;
		_bitmap[index4]++;
		_bitmap[index5]++;
	}

	bool ReSet(const K& key)          //采用引用计数的方式复位
	{
		size_t index1 = HashFunc1()(key) % _bitmap.size();
		size_t index2 = HashFunc2()(key) % _bitmap.size();
		size_t index3 = HashFunc3()(key) % _bitmap.size();
		size_t index4 = HashFunc4()(key) % _bitmap.size();
		size_t index5 = HashFunc5()(key) % _bitmap.size();
		if (_bitmap[index1] == 0 ||
			_bitmap[index2] == 0 ||
			_bitmap[index3] == 0 ||
			_bitmap[index4] == 0 ||
			_bitmap[index5] == 0)                   //只要有一个为0，说明这个key不存在
			return false;
		//要是都不为0，才减一
		_bitmap[index1]--;
		_bitmap[index2]--;
		_bitmap[index3]--;
		_bitmap[index4]--;
		_bitmap[index5]--;
		return true;
	}

	bool Test(const K& key)
	{
		size_t index1 = HashFunc1()(key) % _bitmap.size();
		size_t index2 = HashFunc2()(key) % _bitmap.size();
		size_t index3 = HashFunc3()(key) % _bitmap.size();
		size_t index4 = HashFunc4()(key) % _bitmap.size();
		size_t index5 = HashFunc5()(key) % _bitmap.size();

		//只有五个位置都为1，才存在
		if (_bitmap[index1] != 0 &&
			_bitmap[index2] != 0 &&
			_bitmap[index3] != 0 &&
			_bitmap[index4] != 0 &&
			_bitmap[index5] != 0)
			return true;
		return false;
	}
private:
	vector<size_t> _bitmap;
};