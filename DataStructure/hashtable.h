#pragma once
#include<vector>
using namespace std;
#include<cmath>
#include<cstring>
enum Status{EMPTY,DELETE,EXIST,};


template<typename K,typename V>
struct HashTableNode
{
	K _key;
	V _value;
	Status _status;
	HashTableNode(const K& key=K(),const V& value=V())
		:_key(key)
		, _value(value)
		, _status(EMPTY)
	{}
};


template<typename K, typename V>
struct _HASHFUN
{
	int operator()(const K& key,size_t size)
	{
		size_t num = 0;
		int len = strlen(key);
		int i = 0;
		while (len--)
		{
			num += key[i] * (int)pow(128.0,len);
			i++;
		}
		return num%size;
	}
};


//线性探测
template<typename K,typename V>
class HashTable
{
	typedef HashTableNode<K, V> Node;
public:
	HashTable()
		:_size(0)
	{
		_table.resize(_GetPrime(0));
	}

	HashTable(const HashTable<K, V>& hash)
	{
		size_t newsize =hash._table.size();           //得到hash的大小
		_table.resize(newsize);                       //先扩容

		for (size_t i = 0; i <_table.size(); i++)     //将hash表中的关键码拷贝到到新表中
		{
			if (hash._table[i]._status == EXIST)
			{
				_table[i]._key=hash._table[i]._key;
				_table[i]._value = hash._table[i]._value;
				_table[i]._status = EXIST;
			}
		}
		_size = hash._size;
	}

	HashTable<K, V>& operator=(const HashTable<K,V>& hash)
	{
		if (this != &hash)
		{
			HashTable<K, V> h(hash);
			Swap(h);
		}
		return *this;
	}

	~HashTable()
	{

	}

	Node* Find(const K& key)
	{
		int index = _HashFunc(key);
		if (index >= 0)
		{
			int start = index;        //记录第一次计算的位置
			while (_table[index]._status!=EMPTY)      //这个位置要不为空
			{
				if (_table[index]._key == key)   
				{
					//如果已经找到这个关键码，还要判断这个关键码的状态
					if (_table[index]._status ==EXIST)
					      return &_table[index];
				}
				index++;
				if (index == _table.size())
					index=0;

				if (index == start)                    //如果此时表中都不为空，但是有标记删除的，所以还有可能再找到起始位置
					break;                             //这种情况是找不到的
			}
		}
		return NULL;
	}

	bool Insert(const K& key,const V& value)
	{
		_CheckCapacity();               //先判断需不需要增加表的长度
		int index = _HashFunc(key);
		if (index >= 0)         //如果已经找到了在hash中映射的地址
		{
			while (_table[index]._status==EXIST)  //先找到这个不为存在的位置,由于负载因子的存在，所以不可能全都是EXIST
			{
				index++;
				if (index == _table.size())
					index = 0;
			}
			//如果这个位置不是存在的状态，再插入

			_table[index]._key = key;
			_table[index]._value = value;
			_table[index]._status = EXIST;
			_size++;
			return true;
		}
		return false;
	}

	bool Remove(const K& key)
	{
		//要删除之前先要找到这个要删除的关键码
		Node* del = Find(key);
		if (del)                 //如果已经找到了要删除的关键码，则采用懒惰删除
		{
			del->_status = DELETE;
			_size--;                   //元素的个数要减一
			return true;
		}
		return false;
	}

	void Swap(HashTable<K,V>& table)
	{
		if (this != &table)         //不是自己与自己交换
		{
			_table.swap(table._table);
			swap(_size,table._size);
		}
	}
protected:
	int _HashFunc(const K& key)
	{
		if (_table.size())
		{
			return _HASHFUN<K,V>()(key,_table.size());
		}
		return -1;
	}

	static unsigned _GetPrime(const unsigned long size)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul,
			786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul,
			25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul,
			805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};
		for (size_t i = 0; i <_PrimeSize; i++)     //返回一个比当前hash表大的素数
		{
			if (size < _PrimeList[i])
				return _PrimeList[i];
		}
		return _PrimeList[_PrimeSize-1];   //否则返回最后一个值
	}

	void _CheckCapacity() //如果载荷因子大于0.8，则这时候插入的效率就很低，所以这时候就要增大表的大小
	{
		//载荷因子等于元素的个数除以表的长度
		if (_table.size() == 0 || _size * 10 / _table.size() >= 8)   //这时候插入的效率很低，就要增加hash表的长度
		{
			//由于hash表已经扩容，所以要重新计算表中元素的哈希地址
			HashTable<K, V> hash;           //先创建一个临时的表
			size_t newsize = _GetPrime(_table.size());
			hash._table.resize(newsize);
			for (size_t i = 0; i <_table.size(); i++)     //将旧的表中的关键码拷贝到hash中
			{
				if (_table[i]._status == EXIST)
				{
					hash.Insert(_table[i]._key, _table[i]._value);
				}
			}
			//交换两个hash表
			Swap(hash);
		}
	}
private:
	vector<Node> _table;
	size_t _size;
};