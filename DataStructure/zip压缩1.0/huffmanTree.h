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
public:
	HuffmanTree()
		:_root(NULL)
	{}

	HuffmanTree(T  *a, size_t size, const T& invalid = T())
	{
		//��С�ѵıȽϷ�ʽ
		struct NodeLess
		{
			bool operator()(Node* l, Node* r)
			{
				assert(l);
				assert(r);
				return l->_data < r->_data;
			}
		};

		//���������ݽ���һ����С�ѣ�����Ԫ�ص�������Node*,����Ϊ�˱��������ĸ��ڵ�
		Heap<Node*, NodeLess>  minHeap;
		for (size_t i = 0; i <size; i++)
		{
			if (a[i]._count != invalid._count)           //����ַ����ֵĴ�����Ϊ0���ͼ������
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

		//����������һ������Huffman���ĸ��ڵ�
		_root = minHeap.Top();
	}

	Node* GetRoot()
	{
		return _root;
	}


	~HuffmanTree()
	{
		if (_root != NULL)
		{
			Destory(_root);
		}
	}
protected:
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
