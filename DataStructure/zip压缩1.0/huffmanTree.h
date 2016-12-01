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
		//最小堆的比较方式
		struct NodeLess
		{
			bool operator()(Node* l, Node* r)
			{
				assert(l);
				assert(r);
				return l->_data < r->_data;
			}
		};

		//将这组数据建成一个最小堆，堆中元素的类型是Node*,这是为了保存后面结点的父节点
		Heap<Node*, NodeLess>  minHeap;
		for (size_t i = 0; i <size; i++)
		{
			if (a[i]._count != invalid._count)           //如果字符出现的次数不为0，就加入堆中
			{
				Node* _node = new Node(a[i]);
				minHeap.Push(_node);
			}
		}

		//用huffman算法，从堆里面取出最小的两个结点并删除，将这两个结点构成一棵树在插入堆中
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

		//堆里面的最后一个就是Huffman树的根节点
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
