#pragma once
#include<string>
#include<cstdio>
#include<cassert>
#include<cstdlib>
#include<algorithm>
using namespace std;
#include"HuffmanTree.h"

typedef long long LongType;

struct CharInfo
{
	unsigned char _data;
	LongType _count;                //�����ַ����ֵĴ���
	string _Code;                   //����Huffman����
	CharInfo(LongType count=0)
		:_count(count)
	{}

	CharInfo operator+(CharInfo& ch)
	{
		return CharInfo(_count+ch._count);
	}

	bool operator<(CharInfo &ch)
	{
		return _count < ch._count;
	}
};


class HuffFileCompress
{
public:
	HuffFileCompress()
	{
		for (int i = 0; i < 256; i++)   //��Infos��ÿ��data��ʼ����Ӧ���ַ�
		{
			_Infos[i]._data = i;
		}
	}

	HuffFileCompress(const char * filename)
	{
		assert(filename!=NULL);
		for (int i = 0; i < 256; i++)   //��Infos��ÿ��data��ʼ����Ӧ���ַ�
		{
			_Infos[i]._data = i;
		}
	
		FILE *fInput = fopen(filename,"r");   //���ļ�
		assert(fInput);
		int ch = 0;

		int i = 0;
		while ((ch = fgetc(fInput)) !=EOF)    //���ļ���ͳ���ַ����ִ���
		{
			i++;
			_Infos[ch]._count++;
		}

		//����huffman��
		CharInfo invalid;
		HuffmanTree<CharInfo> ht(_Infos,256,invalid);

		//�õ�huffman����
		string str;
		GetHufCode(ht.GetRoot(),str);
		fclose(fInput);
	}


	//�ļ�ѹ��
	const string CompressFile(const string filename)
	{
		assert(!filename.empty());
		//�õ�ѹ���ļ����ļ���
		string CompressFileName = filename;
		CompressFileName += ".huf";

		FILE *fInput = fopen(filename.c_str(),"rb");     //��ԭ�ļ�
		assert(fInput);

		FILE *fOut = fopen(CompressFileName.c_str(),"wb");   //��ѹ���ļ�
		if (fOut == NULL)
		{
			fclose(fOut);
			exit(EXIT_FAILURE);
		}

		//��д�����ļ�,�����ַ��Լ��ַ����ֵĴ��������ڽ�ѹʱ�ؽ�huffmanTree
		string configFileName = filename;          //�����ļ���
		configFileName += ".config";
		FILE *configOut = fopen(configFileName.c_str(),"wb");   //�������ļ�
		assert(configOut);
		string line;
		for (int i = 0; i < 256; i++)
		{
			if (_Infos[i]._count!=0)         //���ַ��Լ����ֵĴ�������һ��
			{
				int c=_Infos[i]._data;
				fputc(c,configOut);
			//	fputc(' ',configOut);
				line += ",";
				char buffer[25] = { 0 };      //������ת�����ַ����洢
				line+=_itoa((int)_Infos[i]._count, buffer, 10);
				line += '\n';
				fputs(line.c_str(),configOut);
				line.clear();
			}
		}
		fclose(configOut);                  //�ر������ļ�

		int c=0;                //��������huffman���������ɵ��ַ�
		int pos =7;             //�жϴ����λ���������8�����д��
		int ch = fgetc(fInput);
		while (ch!=EOF)
		{
			string &code=_Infos[ch]._Code;
			for (size_t i = 0; i < code.size(); i++)     //����ch����ַ��ı���
			{
				c |= ((code[i]-'0') << pos);             //�Ӹ�λ��ʼ���
				pos--;
				if (pos<0)
				{
					fputc(c,fOut);
					pos = 7;
					c = 0;
				}
			}
			ch = fgetc(fInput);
		}

		if (pos<7)   //�������һ���ַ����벻��8λ�����
		{
			fputc(c, fOut);
		} 
		fclose(fOut);
		fclose(fInput);

		return CompressFileName;
	}


	//��ѹ��
	const string UnCompressFile(string filename)
	{
		assert(!filename.empty());
		//�õ���ѹ��֮����ļ�������
		string name;
	    name= filename;
		int i = 0;
		string posfix;
		for (i =(int)filename.size()-1; i>=0; --i)       //�ҵ���׺���ֵ�λ��
		{
			posfix.push_back(filename[i]);
			if (filename[i] == '.')
				break;
		}
		reverse(posfix.begin(),posfix.end());       //��posfix����Ҫ��ѹ�ļ��ĺ�׺
		if (posfix != ".huf")                 //���Ҫ��ѹ���ļ�����huffmanѹ���ģ����ܽ�ѹ
		{
			return NULL;
		}


		//ȥ����׺
		name.resize(i);

		string UnCompressFileName = name;      //�õ�ѹ���ļ��� 
		UnCompressFileName += ".uhuf";

		string configName = name;
		configName+=".config";   //�õ������ļ���

		//��ѹ���ļ�
		FILE *fInput = fopen(filename.c_str(),"rb");
		FILE *fInput2 =fInput;
		assert(fInput);

		//�򿪽�ѹ���ļ�
		FILE *fOut = fopen(UnCompressFileName.c_str(),"wb");
		if (fOut == NULL)
		{
			fclose(fInput);
			exit(EXIT_FAILURE);
		}

		int ch = 0;

		//��ȡ�����ļ�
		FILE *configInput = fopen(configName.c_str(),"rb");       //�������ļ���
		string line;
		int c = 0;
		while ((c = fgetc(configInput))!=EOF)          //��ȡһ��
		{
			GetLine(configInput, line);                  
			_Infos[c]._count = atoi((&line[1]));       //����ַ����ֵĴ���
			line.clear();
		}
		fclose(configInput);    //�ر������ļ�

		//����huffman��
		CharInfo invalid;
		HuffmanTree<CharInfo> ht(_Infos, 256, invalid);
		LongType count = ht.GetRoot()->_data._count;      //��ȡ�ַ����ܸ���

		int pos=7;
		c = 1;
		HuffmanNode<CharInfo> *root= ht.GetRoot();           //�õ�huffman���ĸ��ڵ�
		HuffmanNode<CharInfo> *cur = root;      
		while (count > 0)                         //���ַ����ܸ�����Ϊ������־
		{
			ch = fgetc(fInput);
			//����ch�Ķ�����
			while (pos >= 0 && count > 0)
			{
				//Ѱ��Ҷ�ӽ��(��������Ӧ���ַ�)
				if (ch&(c << pos))
				{
					cur = cur->_right;
				}
				else
				{
					cur = cur->_left;
				}
				if (cur->_left == NULL&&cur->_right == NULL)    //�ҵ�huffman����Ӧ���ַ�
				{
					//д�ļ�
					fputc(cur->_data._data, fOut);
					cur = root;
					count--;
				}
				pos--;
			}
			pos = 7;
		}
		fclose(fInput);
		fclose(fOut);
	    return UnCompressFileName;
	}

protected:
	//�õ�huffman����
	void GetHufCode(HuffmanNode<CharInfo>* root, string str)
	{
		if (root == NULL)
			return;
		if (root->_left == NULL&&root->_right == NULL)
		{
			_Infos[root->_data._data]._Code = str;  //��huffman���뱣����infos����
			return;
		}
		GetHufCode(root->_left, str + '0');    //����������ѹ0	
		GetHufCode(root->_right, str + '1');   //����������ѹ1		
	}

	bool GetLine(FILE*& Input,string &line)        //��ȡһ���ַ�
	{
		assert(Input);
		int ch = 0;
		ch = fgetc(Input);
		if (ch == EOF)
			return false;
		while (ch != EOF&&ch != '\n')
		{
			line += ch;
			ch = fgetc(Input);
		}
		return true;
	}
private:
	CharInfo _Infos[256];
};
