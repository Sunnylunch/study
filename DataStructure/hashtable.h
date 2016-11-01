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


//����̽��
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
		size_t newsize =hash._table.size();           //�õ�hash�Ĵ�С
		_table.resize(newsize);                       //������

		for (size_t i = 0; i <_table.size(); i++)     //��hash���еĹؼ��뿽�������±���
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
			int start = index;        //��¼��һ�μ����λ��
			while (_table[index]._status!=EMPTY)      //���λ��Ҫ��Ϊ��
			{
				if (_table[index]._key == key)   
				{
					//����Ѿ��ҵ�����ؼ��룬��Ҫ�ж�����ؼ����״̬
					if (_table[index]._status ==EXIST)
					      return &_table[index];
				}
				index++;
				if (index == _table.size())
					index=0;

				if (index == start)                    //�����ʱ���ж���Ϊ�գ������б��ɾ���ģ����Ի��п������ҵ���ʼλ��
					break;                             //����������Ҳ�����
			}
		}
		return NULL;
	}

	bool Insert(const K& key,const V& value)
	{
		_CheckCapacity();               //���ж��費��Ҫ���ӱ�ĳ���
		int index = _HashFunc(key);
		if (index >= 0)         //����Ѿ��ҵ�����hash��ӳ��ĵ�ַ
		{
			while (_table[index]._status==EXIST)  //���ҵ������Ϊ���ڵ�λ��,���ڸ������ӵĴ��ڣ����Բ�����ȫ����EXIST
			{
				index++;
				if (index == _table.size())
					index = 0;
			}
			//������λ�ò��Ǵ��ڵ�״̬���ٲ���

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
		//Ҫɾ��֮ǰ��Ҫ�ҵ����Ҫɾ���Ĺؼ���
		Node* del = Find(key);
		if (del)                 //����Ѿ��ҵ���Ҫɾ���Ĺؼ��룬���������ɾ��
		{
			del->_status = DELETE;
			_size--;                   //Ԫ�صĸ���Ҫ��һ
			return true;
		}
		return false;
	}

	void Swap(HashTable<K,V>& table)
	{
		if (this != &table)         //�����Լ����Լ�����
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
		for (size_t i = 0; i <_PrimeSize; i++)     //����һ���ȵ�ǰhash��������
		{
			if (size < _PrimeList[i])
				return _PrimeList[i];
		}
		return _PrimeList[_PrimeSize-1];   //���򷵻����һ��ֵ
	}

	void _CheckCapacity() //����غ����Ӵ���0.8������ʱ������Ч�ʾͺܵͣ�������ʱ���Ҫ�����Ĵ�С
	{
		//�غ����ӵ���Ԫ�صĸ������Ա�ĳ���
		if (_table.size() == 0 || _size * 10 / _table.size() >= 8)   //��ʱ������Ч�ʺܵͣ���Ҫ����hash��ĳ���
		{
			//����hash���Ѿ����ݣ�����Ҫ���¼������Ԫ�صĹ�ϣ��ַ
			HashTable<K, V> hash;           //�ȴ���һ����ʱ�ı�
			size_t newsize = _GetPrime(_table.size());
			hash._table.resize(newsize);
			for (size_t i = 0; i <_table.size(); i++)     //���ɵı��еĹؼ��뿽����hash��
			{
				if (_table[i]._status == EXIST)
				{
					hash.Insert(_table[i]._key, _table[i]._value);
				}
			}
			//��������hash��
			Swap(hash);
		}
	}
private:
	vector<Node> _table;
	size_t _size;
};