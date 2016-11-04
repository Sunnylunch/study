#pragma once
#include<vector>
using namespace std;
#include<cmath>
#include<cstring>


namespace HASHTABLE
{
	enum Status{ EMPTY, DELETE, EXIST, };

	template<typename K, typename V>
	struct HashTableNode
	{
		K _key;
		V _value;
		Status _status;
		HashTableNode(const K& key = K(), const V& value = V())
			:_key(key)
			, _value(value)
			, _status(EMPTY)
		{}
	};

	template<typename K>
	struct __HashFunc
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template<>                      //由于string用的也比较多，所以将string实现成偏特化
	struct __HashFunc<string>
	{
		size_t operator()(const string& str)
		{
			size_t num = 0;
			int len =(int)str.size();
			int i = 0;
			while (len--)
			{
				num += str[i] * (int)pow(128.0, len);
				i++;
			}
			return num;
		}
	};


	//线性探测           //二次探测
	template<typename K, typename V,class HashFunc=__HashFunc<K>>
	class HashTable
	{
		typedef HashTableNode<K, V> Node;
	public:
		HashTable()
			:_size(0)
		{
			_table.resize(_GetPrime(0));
		}

		HashTable(const HashTable<K, V,HashFunc>& hash)
		{
			size_t newsize = hash._table.size();           //得到hash的大小
			_table.resize(newsize);                       //先扩容

			for (size_t i = 0; i <_table.size(); i++)     //将hash表中的关键码拷贝到到新表中
			{
				if (hash._table[i]._status == EXIST)
				{
					_table[i]._key = hash._table[i]._key;
					_table[i]._value = hash._table[i]._value;
					_table[i]._status = EXIST;
				}
			}
			_size = hash._size;
		}

		HashTable<K, V, HashFunc>& operator=(const HashTable<K, V, HashFunc>& hash)
		{
			if (this != &hash)
			{
				HashTable<K, V, HashFunc> h(hash);
				Swap(h);
			}
			return *this;
		}

		Node* Find(const K& key)
		{
			int index = _HashFunc(key);
			if (index >= 0)
			{
				int start = index;        //记录第一次计算的位置
				while (_table[index]._status != EMPTY)      //这个位置要不为空
				{
					if (_table[index]._key == key)
					{
						//如果已经找到这个关键码，还要判断这个关键码的状态
						if (_table[index]._status == EXIST)
							return &_table[index];
					}
					index++;
					if (index == _table.size())
						index = 0;

					if (index == start)                    //如果此时表中都不为空，但是有标记删除的，所以还有可能再找到起始位置
						break;                             //这种情况是找不到的
				}
			}
			return NULL;
		}

		bool Insert(const K& key, const V& value)
		{
			_CheckCapacity();               //先判断需不需要增加表的长度
			int index = _HashFunc(key);
			if (index >= 0)         //如果已经找到了在hash中映射的地址
			{
				while (_table[index]._status == EXIST)  //先找到这个不为存在的位置,由于负载因子的存在，所以不可能全都是EXIST
				{
					index++;                        //线性探测可以改为二次探测，双散列也可以
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

		void Swap(HashTable<K, V, HashFunc>& table)
		{
			if (this != &table)         //不是自己与自己交换
			{
				_table.swap(table._table);
				swap(_size, table._size);
			}
		}
	protected:
		int _HashFunc(const K& key)
		{
			if (_table.size())
			{   //生成一个匿名对象，调用仿函数
				return HashFunc()(key)%_table.size();
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
			return _PrimeList[_PrimeSize - 1];   //否则返回最后一个值
		}

		void _CheckCapacity() //如果载荷因子大于0.8，则这时候插入的效率就很低，所以这时候就要增大表的大小
		{
			//载荷因子等于元素的个数除以表的长度
			if (_table.size() == 0 || _size * 10 / _table.size() >= 8)   //这时候插入的效率很低，就要增加hash表的长度
			{
				//由于hash表已经扩容，所以要重新计算表中元素的哈希地址
				HashTable<K, V, HashFunc> hash;           //先创建一个临时的表
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
}





namespace HashTable_link
{
	template<typename K,typename V>
	struct HashTableNode
	{
		K _key;
		V _value;
		HashTableNode<K, V>* _next;
		HashTableNode(const K& key=K(),const V& value=V())
			:_key(key)
			, _value(value)
			, _next(NULL)
		{}
	};

	template<class K>             //为了将得到hash地址统一起来，使用仿函数，将整型的时候默认实现出来
	struct __HashFunc               //仿函数，将关键值转换成整型数值
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	//由于string也是常用的类型，所以对string进行偏特化
	template<>
	struct __HashFunc<string>
	{
		size_t operator()(const string& str)
		{
			size_t num = 0;
			for (int i = 0; i < (int)str.size(); i++)
			{
				num += num * 131 +str[i];
			}
			return num;
		}
	};

	template<typename K,typename V,class HashFunc=__HashFunc<K>>       //仿函数默认类型是K
	class HashTable
	{
		typedef HashTableNode<K, V> Node;
	public:
		HashTable()
			:_size(0)
		{
			_tables.resize(_GetPrime(0));
		}

		HashTable(const HashTable<K, V,HashFunc>& hash)
		{
			_tables.resize(hash._tables.size());
			for (int i = 0; i <(int)hash._tables.size(); i++)             //将当前表的内容导入到新表
			{
				Node* cur = hash._tables[i];
				while (cur)
				{
					Insert(cur->_key, cur->_value);
					cur = cur->_next;
				}
			}
		}

		HashTable<K, V, HashFunc>& operator=(const HashTable<K, V, HashFunc>& hash)
		{
			if (this != &hash)           //如果不是自赋值
			{
				HashTable<K, V, HashFunc> tmp(hash);
				Swap(tmp);
			}
			return *this;
		}

		~HashTable()
		{
			for (int i = 0; i <(int)_tables.size(); i++)             //将当前表的内容导入到新表
			{
				Node* cur =_tables[i];
				Node* del = NULL;
				while (cur)
				{
					del = cur;
					cur = cur->_next;
					delete del;
				}
			}
		}

		Node* Find(const K& key)
		{
			int index = _HashFunc(key);
			if (index >= 0)
			{
				Node* cur = _tables[index];
				while (cur)
				{
					if (cur->_key == key)
					{
						return cur;
					}
					cur = cur->_next;
				}

			}
			return NULL;
		}

		bool Insert(const K& key,const V& value)
		{
			_CheckSize();                      //先判断表的载荷因子是否已经达到1，达到1的话就扩容

			Node* ret = Find(key);
			if (ret== NULL)                  //如果要插入的key不存在的，则可以插入
			{
				int index = _HashFunc(key);
				Node* cur = new Node(key,value);
				cur->_next = _tables[index];
				_tables[index] = cur;
				_size++;
				return true;
			}
			return false;
		}

		bool Remove(const K& key)
		{
			int index = _HashFunc(key);
			if (index >= 0)
			{
				Node* prev = NULL;
				Node* cur = _tables[index];
				while (cur)
				{
					if (cur->_key ==key)
					{
						if (prev == NULL)
						{
							_tables[index] = cur->_next;         //删除第一个结点
						}
						else
						{
							prev->_next = cur->_next;
						}
						delete cur;
						_size--;
						return true;
					}
					prev = cur;
					cur = cur->_next;
				}
			}
			return false;
		}

		void Swap(HashTable<K, V, HashFunc>& hash)
		{
			_tables.swap(hash._tables);
			swap(_size,hash._size);
		}

	protected:
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
			return _PrimeList[_PrimeSize - 1];   //否则返回最后一个值
		}

		void _CheckSize()
		{
			if (_tables.size()==0||_size/_tables.size() == 1)       //如果表的长度为0，或者载荷因子为1，则先扩容
			{
				HashTable<K, V, HashFunc> hash;                            //创建一个临时的新hash表
				hash._tables.resize(_GetPrime(_tables.size()));
				for (int  i = 0; i <(int)_tables.size(); i++)             //将当前表的内容导入到新表
				{
					Node* cur = _tables[i];
					while (cur)
					{
						hash.Insert(cur->_key,cur->_value);
						cur = cur->_next;
					}
				}
				Swap(hash);            //交换两个表的内容
			}
		}

		int _HashFunc(const K& key)
		{
			if (_tables.size())
			{
				return (HashFunc()(key))%_tables.size();  //先构造一个匿名对象，再调用仿函数
			}
			return -1;
		}
	private:
		vector<Node*> _tables;
		size_t _size;
	};
}

