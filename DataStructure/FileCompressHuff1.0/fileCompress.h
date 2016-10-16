#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<cstdio>
#include<string>
#include<queue>
#include<vector>
using namespace std;
#include"HuffmanTree.h"

typedef long long LongType;

struct CharInfo
{
	char _data;
	LongType _count;
	string _code;                 //huffman编码
	CharInfo(const char& data = char())
		:_data(data)              //huffman所对应的字符值
		, _count(0)               //权值
	{}

	//重载HuffmanNode 的比较方式
	bool operator<(CharInfo node)
	{
		return _count <node._count;
	}

	bool operator!=(LongType zero)           //重载HuffNode与0比较
	{
		return _count !=zero;
	}

	void PushFront(char ch)                   //定义压入编码的函数
	{
		_code.insert(_code.begin(),ch);             //头插
	}

	CharInfo operator+(CharInfo r)
	{
		CharInfo node;
		node._count = _count + r._count;
		return node;
	}
};

class FileCompress            //文件压缩类
{
	typedef CharInfo Node;
public:
	FileCompress(const char *fileName)   
	{
		StatisticNum(fileName);                    //统计输入文件中字符出现的次数
		HuffmanTree<Node> ht(_Count, 256);         //构建HuffmanTree，并得到huffman编码
		ht.Swap(_ht);                              //让_ht指向huffman树
		_ht.SaveHuffmanCode(_Count);               //将huffman编码保存到_Count里面
	}

	const char* Compress(const char *fileName)                         //压缩文件
	{
		const char* CompressFile = "CompressFile.txt";    
		FILE  *fWrite= fopen(CompressFile, "w");         //压缩文件
		assert(fWrite);
		FILE  *fRead = fopen(fileName,"r");             //原文件
		if (fRead==NULL)
		{
			fclose(fWrite);
			exit(1);
		}

		queue<int> buffer;           //存储编码的缓冲区
		int ch = 0;
		while ((ch = getc(fRead)) != EOF)
		{
			GetCode(_Count[ch]._code,buffer);
			while (buffer.size()>=8)              //只要缓冲区有8个数据或8个以上
			{
				char c =0;
				for (int i = 7; i>=0; --i)       //将这8位转换成一个字符进行存储
				{
					c|=(buffer.front()<<i);
					buffer.pop();
				}
				fputc(c,fWrite);
			}
		}
		if (buffer.size()>0)
		{
			char c = 0;
			for (int i=7;i>=8-(int)buffer.size(); --i)       //将这8位转换成一个字符进行存储
			{
				c |= (buffer.front()<< i);
				buffer.pop();
			}
			fputc(c, fWrite);
		}
		fputc(EOF, fWrite);
		fclose(fWrite);
		fclose(fRead);
		return CompressFile;
	}

	const char* UnCompress(const char* CompressFile)                       //解压缩
	{
		const char* UnCompressFile = "UnCompressFile.txt";
		FILE *fWrite = fopen(UnCompressFile,"w");                //写到解压缩文件里面
		assert(fWrite);
		FILE *fRead = fopen(CompressFile,"r");
		if (fRead == NULL)
		{
			fclose(fWrite);
			exit(1);
		}

		vector<int> buffer;
		int ch = 0;
		LongType Count = _ht.GetRoot()._count;
		LongType i =0;
		while ((ch = getc(fRead)) != EOF)
		{
			if (i == Count-1)
				break;
			GetBit(ch,buffer);            //得到每一个字符的bit位
			const Node& data= _ht.GetChar(buffer);
			if (data._count != 0)
			{
				i++;
				fputc(data._data, fWrite);          //将转换后得到的字符写入文件
				for (int i = 0; i < (int)data._code.size(); i++)
				{
					vector<int>::iterator it = buffer.begin();
					buffer.erase(it);
				}
			}
		}
		while((i<Count-1)&&(buffer.size()>0))
		{
			const Node& data = _ht.GetChar(buffer);
			if (data._count != 0)
			{
				i++;
				fputc(data._data, fWrite);          //将转换后得到的字符写入文件
				for (int i = 0; i < (int)data._code.size(); i++)
				{
					vector<int>::iterator it = buffer.begin();
					buffer.erase(it);
				}
			}
			else 
			{
				break;
			}
		}
		fputc(EOF,fWrite);
		fclose(fWrite);
		fclose(fRead);
		return UnCompressFile;
	}
protected:
	void StatisticNum(const char* fileName)         //统计输入文件中字符出现的次数
	{
		memset(_Count,0,sizeof(Node)*256);           //初始化为全0
		FILE *Input = fopen(fileName,"r");
		assert(Input);                         //判断打开文件是否成功
		int ch = 0;
		while ((ch=getc(Input))!=EOF)           //读取文件中的字符       
		{
			if (_Count[ch]._count == 0)
			{
				_Count[ch]._data =ch;            //如果第一次遇见这个字符，则把它赋值给_data
			}
			_Count[ch]._count++;
		}

		fclose(Input);
	}

	void GetCode(string& str, queue<int> &buffer)     //得到Huffman 编码
	{
		string str1(str);
		string::iterator it;
		for (it = str1.begin(); it < str1.end(); it++)
		{
			buffer.push((*it) - '0');         //转换成数字
		}
	}

	void GetBit(const char ch, vector<int>& buffer)
	{
		for (int i = 7; i >=0; i--)
		{
			if (ch&(1 << i))          //第i个bit为为1
			{
				buffer.push_back(1);
			}
			else                     //第i个bit为为0
			{
				buffer.push_back(0);
			}
		}
	}
private:
	HuffmanTree<Node> _ht;
	Node _Count[256];
};