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
	string _code;                 //huffman����
	CharInfo(const char& data = char())
		:_data(data)              //huffman����Ӧ���ַ�ֵ
		, _count(0)               //Ȩֵ
	{}

	//����HuffmanNode �ıȽϷ�ʽ
	bool operator<(CharInfo node)
	{
		return _count <node._count;
	}

	bool operator!=(LongType zero)           //����HuffNode��0�Ƚ�
	{
		return _count !=zero;
	}

	void PushFront(char ch)                   //����ѹ�����ĺ���
	{
		_code.insert(_code.begin(),ch);             //ͷ��
	}

	CharInfo operator+(CharInfo r)
	{
		CharInfo node;
		node._count = _count + r._count;
		return node;
	}
};

class FileCompress            //�ļ�ѹ����
{
	typedef CharInfo Node;
public:
	FileCompress(const char *fileName)   
	{
		StatisticNum(fileName);                    //ͳ�������ļ����ַ����ֵĴ���
		HuffmanTree<Node> ht(_Count, 256);         //����HuffmanTree�����õ�huffman����
		ht.Swap(_ht);                              //��_htָ��huffman��
		_ht.SaveHuffmanCode(_Count);               //��huffman���뱣�浽_Count����
	}

	const char* Compress(const char *fileName)                         //ѹ���ļ�
	{
		const char* CompressFile = "CompressFile.txt";    
		FILE  *fWrite= fopen(CompressFile, "w");         //ѹ���ļ�
		assert(fWrite);
		FILE  *fRead = fopen(fileName,"r");             //ԭ�ļ�
		if (fRead==NULL)
		{
			fclose(fWrite);
			exit(1);
		}

		queue<int> buffer;           //�洢����Ļ�����
		int ch = 0;
		while ((ch = getc(fRead)) != EOF)
		{
			GetCode(_Count[ch]._code,buffer);
			while (buffer.size()>=8)              //ֻҪ��������8�����ݻ�8������
			{
				char c =0;
				for (int i = 7; i>=0; --i)       //����8λת����һ���ַ����д洢
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
			for (int i=7;i>=8-(int)buffer.size(); --i)       //����8λת����һ���ַ����д洢
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

	const char* UnCompress(const char* CompressFile)                       //��ѹ��
	{
		const char* UnCompressFile = "UnCompressFile.txt";
		FILE *fWrite = fopen(UnCompressFile,"w");                //д����ѹ���ļ�����
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
			GetBit(ch,buffer);            //�õ�ÿһ���ַ���bitλ
			const Node& data= _ht.GetChar(buffer);
			if (data._count != 0)
			{
				i++;
				fputc(data._data, fWrite);          //��ת����õ����ַ�д���ļ�
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
				fputc(data._data, fWrite);          //��ת����õ����ַ�д���ļ�
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
	void StatisticNum(const char* fileName)         //ͳ�������ļ����ַ����ֵĴ���
	{
		memset(_Count,0,sizeof(Node)*256);           //��ʼ��Ϊȫ0
		FILE *Input = fopen(fileName,"r");
		assert(Input);                         //�жϴ��ļ��Ƿ�ɹ�
		int ch = 0;
		while ((ch=getc(Input))!=EOF)           //��ȡ�ļ��е��ַ�       
		{
			if (_Count[ch]._count == 0)
			{
				_Count[ch]._data =ch;            //�����һ����������ַ����������ֵ��_data
			}
			_Count[ch]._count++;
		}

		fclose(Input);
	}

	void GetCode(string& str, queue<int> &buffer)     //�õ�Huffman ����
	{
		string str1(str);
		string::iterator it;
		for (it = str1.begin(); it < str1.end(); it++)
		{
			buffer.push((*it) - '0');         //ת��������
		}
	}

	void GetBit(const char ch, vector<int>& buffer)
	{
		for (int i = 7; i >=0; i--)
		{
			if (ch&(1 << i))          //��i��bitΪΪ1
			{
				buffer.push_back(1);
			}
			else                     //��i��bitΪΪ0
			{
				buffer.push_back(0);
			}
		}
	}
private:
	HuffmanTree<Node> _ht;
	Node _Count[256];
};