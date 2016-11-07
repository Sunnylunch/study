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


//֧��Reset��bloomfliter

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
		_bitmap.resize(range*5);           //Ϊ�˼������У���߾��ȣ���5��λ������ʾһ����
	}

	void Set(const K& key)          //Ҫ����Ϊ1�����뽫5��λ�ö�����
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

	bool ReSet(const K& key)          //�������ü����ķ�ʽ��λ
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
			_bitmap[index5] == 0)                   //ֻҪ��һ��Ϊ0��˵�����key������
			return false;
		//Ҫ�Ƕ���Ϊ0���ż�һ
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

		//ֻ�����λ�ö�Ϊ1���Ŵ���
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