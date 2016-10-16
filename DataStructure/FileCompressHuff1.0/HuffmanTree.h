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

	//最小堆的比较方式
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

		//将这组数据建成一个最小堆，堆中元素的类型是Node*,这是为了保存后面结点的父节点
		Heap<Node*, NodeLess>  minHeap;
		for (size_t i = 0; i <size; i++)
		{
			if (a[i]._data!=0)         //只有字符的个数不为0才加入最小堆
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
		_root = minHeap.Top();

		//得到huffman编码
		GetHuffmanCode();
	}

	void SaveHuffmanCode(T *a)        //把huffman编码保存起来
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
	void _SaveHuffmanCode(Node* root, T *a)        //把huffman编码保存起来
	{
		if (root == NULL)
			return;
		_SaveHuffmanCode(root->_left,a);
		_SaveHuffmanCode(root->_right,a);
		if (root->_left == NULL&&root->_right == NULL)    //如果找到叶子结点
		{
			a[root->_data._data]._code = root->_data._code;
		}
	}


	//得到huffman编码
	void GetHuffmanCode()
	{
		PostOder(_root);
	}

	void PostOder(Node* root)        //后序遍历寻找叶子节点
	{
		if (root == NULL)
			return;
		PostOder(root->_left);
		PostOder(root->_right);
		if (root->_left == NULL&&root->_right == NULL)    //如果找到叶子结点
		{
			SetCode(root);
		}
    }

	void SetCode(Node* leaft)         //得到huffman编码
	{
		assert(leaft!=NULL);
		Node* cur = leaft;
		Node* parent = cur->_parent;
		while (parent != NULL)
		{
			if (parent->_left== cur)        //如果cur是它父亲的左孩子
			{
				leaft->_data.PushFront('0');      //PushBack将0压入huffman编码
			}
			else                              //如果cur是它父亲的右孩子
			{
				leaft->_data.PushFront('1');      //PushBack将1压入huffman编码
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