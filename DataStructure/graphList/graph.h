#pragma once
#include<vector>
#include<cassert>
#include<queue>
#include<algorithm>
using namespace std;
#include"UnionSet.h"


template<typename V,typename E>
class GraphList
{
public:
	struct Node         //内部类，在邻接表上挂的结点的类型
	{
		size_t _src;    //_tables[i]在_vertex中的位置
		size_t _dst;    //与_tables[i]有边的点在_vertex中的位置
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
	GraphList(bool isdirect = false)
		:_isdirect(isdirect)
	{}
	GraphList(V* vertex,size_t n,bool isdirect=false)
		:_vertex(vertex,vertex+n)
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
		vector<bool> visited(_vertex.size(),false);
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
		vector<bool> visited(_vertex.size(),false);
		queue<size_t> q;       
		q.push(index);              //将起点的坐标入队

		while (!q.empty())
		{
			size_t front = q.front();
			q.pop();

			cout << _vertex[front].c_str() << "->";
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

	////最小生成树就是在用N-1条边将一个连通图里面的所有顶点都连接起来，并且所有边的权重之和最小
	////克鲁斯卡尔算法，寻找最短的边，如果不构成回路的话，则就是最小生成树中的一条边
	//bool MinTree(GraphList<V,E>& minTree)
	//{
	//	if (_isdirect)             //如果是有向图的话，则就直接返回false
	//	{
	//		return false;
	//	}

	//	minTree._vertex = _vertex;        //将这个图的所有顶点都放入到minTree里面
	//	minTree._tables.resize(_tables.size());

	//	struct Compare
	//	{
	//		bool operator()(Node* l,Node* r)
	//		{
	//			return (l->_weight) >(r->_weight);
	//		}
	//	};

	//	//建立一个小堆，用来查找图里面最小的边
	//	vector<Node*> minHeap;
	//	for (size_t i = 0; i < _tables.size();++i)
	//	{
	//		Node* cur = _tables[i];
	//		while (cur)
	//		{
	//			minHeap.push_back(cur);
	//			cur = cur->_next;
	//		}
	//	}
	//	make_heap(minHeap.begin(),minHeap.end(),Compare());    //建小堆

	//	size_t n = 0;
	//	UnionSet ufs(_vertex.size());
	//	while (n < _tables.size() - 1)
	//	{
	//		if (minHeap.empty())
	//		{
	//			return false;
	//		}
	//		pop_heap(minHeap.begin(),minHeap.end(),Compare());
	//		Node* minEdge = minHeap.back();     //得到最小边
	//		minHeap.pop_back();

	//		//到并查集里面判断加入这条边会不会形成环
	//		size_t root1 = ufs.GetRoot(minEdge->_src);
	//		size_t root2 = ufs.GetRoot(minEdge->_dst);
	//		if (root1!=root2)                                    //这两个结点不再并查集里面
	//		{
	//			ufs.Merge(minEdge->_src, minEdge->_dst);         //把这条边添加到并查集里面
	//			minTree._AddEdge(minEdge->_src, minEdge->_dst,minEdge->_weight);  //添加这条边
	//			n++;
	//		}
	//	}
	//	return true;
	//}



//最小生成树就是用N-1条边将图中的所有顶点都连接起来，而且这些边的权重之和要最小
//普里姆算法
	bool MinTree(GraphList<V, E>& minTree)
	{
		if (_isdirect)             //如果是有向图的话，则就直接返回false
		{
			return false;
		}
		minTree._vertex = _vertex;        //将这个图的所有顶点都放入到minTree里面
		minTree._tables.resize(_tables.size());

		struct Compare
		{
			bool operator()(Node* l,Node* r)
			{
				return l->_weight > r->_weight;
			}
		};

		vector<Node*> minHeap;
		UnionSet ufs(_vertex.size());         //建立一个并查集，最开始每个顶点都是一个单独的集合
		size_t n = 0;

		Node* cur = _tables[0];
		while (n<_tables.size()-1)
		{
			while (cur)                        //将这个点所有的边都放入最小堆中
			{
				minHeap.push_back(cur);
				push_heap(minHeap.begin(),minHeap.end(),Compare());
				cur = cur->_next;
			}
			pop_heap(minHeap.begin(),minHeap.end(),Compare());
			if (minHeap.empty())
			{
				return false;
			}
			Node* minEdge = minHeap.back();
			minHeap.pop_back();

			size_t root1 =ufs.GetRoot(minEdge->_src);
			size_t root2 =ufs.GetRoot(minEdge->_dst);
			if (root1!=root2)
			{
				ufs.Merge(minEdge->_src, minEdge->_dst);
				minTree._AddEdge(minEdge->_src, minEdge->_dst, minEdge->_weight);
				cur = _tables[minEdge->_dst];
				n++;
			}
		}
		return true;
	}
	
protected:
	void _DFS(size_t src,vector<bool>& visited)
	{
		Node* cur = _tables[src];
		printf("%s:->", _vertex[src].c_str());
		visited[cur->_src] = true;                  //将已经访问过的结点标记起来

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
		for (size_t i = 0; i < _vertex.size(); ++i)
		{
			if (_vertex[i] == src)
				return i;
		}
		assert(false);
		return -1;
	}
private:
	vector<V> _vertex;       //用来存储顶点
	vector<Node*> _tables;
	bool _isdirect;
};


