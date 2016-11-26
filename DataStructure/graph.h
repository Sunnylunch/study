#pragma once
#include<vector>
#include<cassert>
#include<queue>
using namespace std;

//邻接矩阵表示图
template<typename V,typename E>
class GraphMatrix
{
public:
	GraphMatrix(V* vertax,size_t n,bool isdirect=false)   //默认是无向图
		:_size(n)
		, _isdirect(isdirect)
	{
		_vertax = new V[n];             //开辟n个大小的数组用来表示图的顶点
		_matrix = new E* [n];          //开辟一个n*n的二维数组用来保存边
		for (size_t i = 0; i < n; ++i)
		{
			_vertax[i] = vertax[i];
			_matrix[i] = new E[n];
			for (size_t j = 0; j < n; ++j)
			{
				_matrix[i][j] =E();
			}
		}
	}

	~GraphMatrix()
	{
		delete[] _vertax;
		for (size_t i = 0; i < _size; ++i)
		{
			delete[] _matrix[i];
		}
		delete [] _matrix;
	}

	void AddEdge(const V& src,const V& dst,const E& w)
	{
		size_t line = GetIndex(src);
		size_t row = GetIndex(dst);
		_matrix[line][row] = w;
		if (_isdirect == false)    //无向图
		{
			_matrix[row][line] = w;
		}
	}
protected:
	size_t GetIndex(const V& src)    //得到顶点所在_vertax中的下标
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_vertax[i] == src)
				return i;
		}

		assert(false);
		return -1;
	}

private:
	V* _vertax;     //用来保存顶点
	E** _matrix;    //用来保存边
	size_t _size;
	bool _isdirect;     //判断是不是无向图
};




//邻接表
template<typename V,typename E>
class GraphList
{
public:
	struct Node               //内部类，在邻接表上挂的结点的类型
	{
		size_t _src;    //_tables[i]在_vertax中的位置
		size_t _dst;     //与_tables[i]有边的点在_vertax中的位置
		E _weight;
		Node* _next;
		Node(size_t src,size_t dst,E w)
			:_src(src)
			, _dst(dst)
			, _weight(w)
			, _next(NULL)
		{}
	};
public:
	GraphList(V* vertax,size_t n,bool isdirect=false)
		:_vertax(vertax,vertax+n)
		, _isdirect(isdirect)
	{
		_tables.resize(n);
	}
	~GraphList()
	{
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			Node* cur = _tables[i];
			while(cur)
			{
				Node* del = cur;
				cur = cur->_next;
				delete del;
			}
		}
	}
	void AddEdge(const V& src,const V& dst,const E& w)     //添加边
	{
		size_t index1 = GetIndex(src);
		size_t index2 = GetIndex(dst);
		if (_isdirect == false)         //无向图
		{
			_AddEdge(index1,index2,w);
			_AddEdge(index2,index1,w);
		}
		else           //有向图
		{
			_AddEdge(index1,index2,w);
		}
	}

	void DFS(const V& src)            //深度优先遍历
	{
		vector<bool> visited(_vertax.size(),false);
		_DFS(GetIndex(src),visited);
		for (size_t i = 0; i < visited.size(); ++i)      //如果图不是连通图的话
		{
			if (visited[i]==false)
				_DFS(i, visited);
		}
	}

	void  BFS(const V& src)
	{
		size_t index = GetIndex(src);
		vector<bool> visited(_vertax.size(),false);
		queue<size_t> q;       
		q.push(index);              //将起点的坐标入队

		while (!q.empty())
		{
			size_t front = q.front();
			q.pop();

			cout << _vertax[front].c_str() << "->";
			visited[front] = true;

			Node* cur = _tables[front];
			while (cur)
			{
				if (visited[cur->_dst] == false)
				{
					q.push(cur->_dst);
					visited[cur->_dst] = true;  //如果这个元素已经入队了，则就标记为true
				}
				cur = cur->_next;
			}
		}
	}
protected:
	void _DFS(size_t src,vector<bool>& visited)
	{
		Node* cur = _tables[src];
		printf("%s:->", _vertax[src].c_str());
		visited[cur->_src] = true;

		while (cur)
		{
			if (visited[cur->_dst] == false)
				_DFS(cur->_dst, visited);
			cur = cur->_next;
		}
	}

	void _AddEdge(size_t src, size_t dst, const E& w)
	{
		Node* node = new Node(src,dst,w);

		node->_next = _tables[src];
		_tables[src] = node;
	}

	size_t GetIndex(const V& src)
	{
		for (size_t i = 0; i < _vertax.size(); ++i)
		{
			if (_vertax[i] == src)
				return i;
		}
		assert(false);
		return -1;
	}
private:
	vector<V> _vertax;       //用来存储顶点
	vector<Node*> _tables;
	bool _isdirect;
};
