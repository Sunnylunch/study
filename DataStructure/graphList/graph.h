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
	struct Node         //�ڲ��࣬���ڽӱ��ϹҵĽ�������
	{
		size_t _src;    //_tables[i]��_vertex�е�λ��
		size_t _dst;    //��_tables[i]�бߵĵ���_vertex�е�λ��
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

	void AddEdge(const V& src,const V& dst,const E& w)     //��ӱ�
	{
		size_t index1 = GetIndex(src);
		size_t index2 = GetIndex(dst);
		if (_isdirect == false)         //����ͼ
		{
			_AddEdge(index1,index2,w);
			_AddEdge(index2,index1,w);
		}
		else           //����ͼ
		{
			_AddEdge(index1,index2,w);
		}
	}

	void DFS(const V& src)            //������ȱ���
	{
		vector<bool> visited(_vertex.size(),false);
		_DFS(GetIndex(src),visited);
		for (size_t i = 0; i < visited.size(); ++i)      //���ͼ������ͨͼ�Ļ�
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
		q.push(index);              //�������������

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
					visited[cur->_dst] = true;  //������Ԫ���Ѿ�����ˣ���ͱ��Ϊtrue
				}
				cur = cur->_next;
			}
		}
	}

	////��С��������������N-1���߽�һ����ͨͼ��������ж��㶼�����������������бߵ�Ȩ��֮����С
	////��³˹�����㷨��Ѱ����̵ıߣ���������ɻ�·�Ļ����������С�������е�һ����
	//bool MinTree(GraphList<V,E>& minTree)
	//{
	//	if (_isdirect)             //���������ͼ�Ļ������ֱ�ӷ���false
	//	{
	//		return false;
	//	}

	//	minTree._vertex = _vertex;        //�����ͼ�����ж��㶼���뵽minTree����
	//	minTree._tables.resize(_tables.size());

	//	struct Compare
	//	{
	//		bool operator()(Node* l,Node* r)
	//		{
	//			return (l->_weight) >(r->_weight);
	//		}
	//	};

	//	//����һ��С�ѣ���������ͼ������С�ı�
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
	//	make_heap(minHeap.begin(),minHeap.end(),Compare());    //��С��

	//	size_t n = 0;
	//	UnionSet ufs(_vertex.size());
	//	while (n < _tables.size() - 1)
	//	{
	//		if (minHeap.empty())
	//		{
	//			return false;
	//		}
	//		pop_heap(minHeap.begin(),minHeap.end(),Compare());
	//		Node* minEdge = minHeap.back();     //�õ���С��
	//		minHeap.pop_back();

	//		//�����鼯�����жϼ��������߻᲻���γɻ�
	//		size_t root1 = ufs.GetRoot(minEdge->_src);
	//		size_t root2 = ufs.GetRoot(minEdge->_dst);
	//		if (root1!=root2)                                    //��������㲻�ٲ��鼯����
	//		{
	//			ufs.Merge(minEdge->_src, minEdge->_dst);         //����������ӵ����鼯����
	//			minTree._AddEdge(minEdge->_src, minEdge->_dst,minEdge->_weight);  //���������
	//			n++;
	//		}
	//	}
	//	return true;
	//}



//��С������������N-1���߽�ͼ�е����ж��㶼����������������Щ�ߵ�Ȩ��֮��Ҫ��С
//����ķ�㷨
	bool MinTree(GraphList<V, E>& minTree)
	{
		if (_isdirect)             //���������ͼ�Ļ������ֱ�ӷ���false
		{
			return false;
		}
		minTree._vertex = _vertex;        //�����ͼ�����ж��㶼���뵽minTree����
		minTree._tables.resize(_tables.size());

		struct Compare
		{
			bool operator()(Node* l,Node* r)
			{
				return l->_weight > r->_weight;
			}
		};

		vector<Node*> minHeap;
		UnionSet ufs(_vertex.size());         //����һ�����鼯���ʼÿ�����㶼��һ�������ļ���
		size_t n = 0;

		Node* cur = _tables[0];
		while (n<_tables.size()-1)
		{
			while (cur)                        //����������еı߶�������С����
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
		visited[cur->_src] = true;                  //���Ѿ����ʹ��Ľ��������

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
	vector<V> _vertex;       //�����洢����
	vector<Node*> _tables;
	bool _isdirect;
};


