#pragma once
#include"heap.h"

template<typename T>
struct HuffmanNode
{
	T _data;
	HuffmanNode<T>* _left;
	HuffmanNode<T>* _right;
	HuffmanNode<T>* _parent;
	HuffmanNode(const T& data = T())
		:_data(data)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};




template<typename T>
class HuffmanTree
{
	typedef HuffmanNode<T> Node;

	//��С�ѵıȽϷ�ʽ
	struct NodeLess
	{
		bool operator()(Node* l, Node* r)
		{
			assert(l);
			assert(r);
			return l->_data< r->_data;
		}
	};

public:
	HuffmanTree()
		:_root(NULL)
	{}

	HuffmanTree(T* a, size_t size)
	{

		//���������ݽ���һ����С�ѣ�����Ԫ�ص�������Node*,����Ϊ�˱��������ĸ��ڵ�
		Heap<Node*, NodeLess>  minHeap;
		for (size_t i = 0; i <size; i++)
		{
			if (a[i]._data!=0)         //ֻ���ַ��ĸ�����Ϊ0�ż�����С��
			{
				Node* _node = new Node(a[i]);
				minHeap.Push(_node);
			}
		}

		//��huffman�㷨���Ӷ�����ȡ����С��������㲢ɾ��������������㹹��һ�����ڲ������
		Node* frist = NULL;
		Node* second = NULL;
		Node* parent = NULL;
		while (minHeap.Size()>1)
		{
			frist = minHeap.Top();
			minHeap.Pop();
			second = minHeap.Top();
			minHeap.Pop();

			parent = new Node(frist->_data + second->_data);
			parent->_left = frist;
			parent->_right = second;

			frist->_parent = parent;
			second->_parent = parent;

			minHeap.Push(parent);
		}
		_root = minHeap.Top();

		//�õ�huffman����
		GetHuffmanCode();
	}

	void SaveHuffmanCode(T *a)        //��huffman���뱣������
	{		
		_SaveHuffmanCode(_root,a);
	}


	void Swap(HuffmanTree<T>& ht)
	{
	    swap(_root,ht._root);
	}

	const T& GetChar(vector<int>& buffer)
	{
		assert(_root);
		Node* cur = _root;
		int i = 0;
		while (cur->_left != NULL&&cur->_right != NULL&&(i<(int)buffer.size()))
		{
			if (buffer[i] == 1)
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
			i++;
		}
		return cur->_data;
	}

	const T& GetRoot()
	{
		assert(_root);
		return _root->_data;
	}


	~HuffmanTree()
	{
		if (_root != NULL)
		{
			Destory(_root);
		}
	}
protected:
	void _SaveHuffmanCode(Node* root, T *a)        //��huffman���뱣������
	{
		if (root == NULL)
			return;
		_SaveHuffmanCode(root->_left,a);
		_SaveHuffmanCode(root->_right,a);
		if (root->_left == NULL&&root->_right == NULL)    //����ҵ�Ҷ�ӽ��
		{
			a[root->_data._data]._code = root->_data._code;
		}
	}


	//�õ�huffman����
	void GetHuffmanCode()
	{
		PostOder(_root);
	}

	void PostOder(Node* root)        //�������Ѱ��Ҷ�ӽڵ�
	{
		if (root == NULL)
			return;
		PostOder(root->_left);
		PostOder(root->_right);
		if (root->_left == NULL&&root->_right == NULL)    //����ҵ�Ҷ�ӽ��
		{
			SetCode(root);
		}
    }

	void SetCode(Node* leaft)         //�õ�huffman����
	{
		assert(leaft!=NULL);
		Node* cur = leaft;
		Node* parent = cur->_parent;
		while (parent != NULL)
		{
			if (parent->_left== cur)        //���cur�������׵�����
			{
				leaft->_data.PushFront('0');      //PushBack��0ѹ��huffman����
			}
			else                              //���cur�������׵��Һ���
			{
				leaft->_data.PushFront('1');      //PushBack��1ѹ��huffman����
			}
			cur = parent;
			parent = cur->_parent;
		}
	}

	void Destory(Node * root)
	{
		if (root == NULL)
			return;
		Node* cur = root;
		Destory(cur->_left);
		Destory(cur->_right);
		delete cur;
		cur = NULL;
	}
private:
	Node* _root;
};