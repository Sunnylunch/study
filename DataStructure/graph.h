#pragma once
#include<vector>
#include<cassert>
#include<queue>
using namespace std;

//�ڽӾ����ʾͼ
template<typename V,typename E>
class GraphMatrix
{
public:
	GraphMatrix(V* vertax,size_t n,bool isdirect=false)   //Ĭ��������ͼ
		:_size(n)
		, _isdirect(isdirect)
	{
		_vertax = new V[n];             //����n����С������������ʾͼ�Ķ���
		_matrix = new E* [n];          //����һ��n*n�Ķ�ά�������������
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
		if (_isdirect == false)    //����ͼ
		{
			_matrix[row][line] = w;
		}
	}
protected:
	size_t GetIndex(const V& src)    //�õ���������_vertax�е��±�
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
	V* _vertax;     //�������涥��
	E** _matrix;    //���������
	size_t _size;
	bool _isdirect;     //�ж��ǲ�������ͼ
};




//�ڽӱ�
template<typename V,typename E>
class GraphList
{
public:
	struct Node               //�ڲ��࣬���ڽӱ��ϹҵĽ�������
	{
		size_t _src;    //_tables[i]��_vertax�е�λ��
		size_t _dst;     //��_tables[i]�бߵĵ���_vertax�е�λ��
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
		vector<bool> visited(_vertax.size(),false);
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
		vector<bool> visited(_vertax.size(),false);
		queue<size_t> q;       
		q.push(index);              //�������������

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
					visited[cur->_dst] = true;  //������Ԫ���Ѿ�����ˣ���ͱ��Ϊtrue
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
	vector<V> _vertax;       //�����洢����
	vector<Node*> _tables;
	bool _isdirect;
};
