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
	LongType _count;                //保存字符出现的次数
	string _Code;                   //保存Huffman编码
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
		for (int i = 0; i < 256; i++)   //将Infos中每个data初始化相应的字符
		{
			_Infos[i]._data = i;
		}
	}

	HuffFileCompress(const char * filename)
	{
		assert(filename!=NULL);
		for (int i = 0; i < 256; i++)   //将Infos中每个data初始化相应的字符
		{
			_Infos[i]._data = i;
		}
	
		FILE *fInput = fopen(filename,"r");   //打开文件
		assert(fInput);
		int ch = 0;

		int i = 0;
		while ((ch = fgetc(fInput)) !=EOF)    //读文件，统计字符出现次数
		{
			i++;
			_Infos[ch]._count++;
		}

		//构建huffman树
		CharInfo invalid;
		HuffmanTree<CharInfo> ht(_Infos,256,invalid);

		//得到huffman编码
		string str;
		GetHufCode(ht.GetRoot(),str);
		fclose(fInput);
	}


	//文件压缩
	const string CompressFile(const string filename)
	{
		assert(!filename.empty());
		//得到压缩文件的文件名
		string CompressFileName = filename;
		CompressFileName += ".huf";

		FILE *fInput = fopen(filename.c_str(),"rb");     //打开原文件
		assert(fInput);

		FILE *fOut = fopen(CompressFileName.c_str(),"wb");   //打开压缩文件
		if (fOut == NULL)
		{
			fclose(fOut);
			exit(EXIT_FAILURE);
		}

		//编写配置文件,保存字符以及字符出现的次数，用于解压时重建huffmanTree
		string configFileName = filename;          //配置文件名
		configFileName += ".config";
		FILE *configOut = fopen(configFileName.c_str(),"wb");   //打开配置文件
		assert(configOut);
		string line;
		for (int i = 0; i < 256; i++)
		{
			if (_Infos[i]._count!=0)         //将字符以及出现的次数存在一行
			{
				int c=_Infos[i]._data;
				fputc(c,configOut);
			//	fputc(' ',configOut);
				line += ",";
				char buffer[25] = { 0 };      //将次数转换成字符串存储
				line+=_itoa((int)_Infos[i]._count, buffer, 10);
				line += '\n';
				fputs(line.c_str(),configOut);
				line.clear();
			}
		}
		fclose(configOut);                  //关闭配置文件

		int c=0;                //用来保存huffman编码所构成的字符
		int pos =7;             //判断处理的位数，如果到8则进行写入
		int ch = fgetc(fInput);
		while (ch!=EOF)
		{
			string &code=_Infos[ch]._Code;
			for (size_t i = 0; i < code.size(); i++)     //处理ch这个字符的编码
			{
				c |= ((code[i]-'0') << pos);             //从高位开始相或
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

		if (pos<7)   //处理最后一个字符编码不是8位的情况
		{
			fputc(c, fOut);
		} 
		fclose(fOut);
		fclose(fInput);

		return CompressFileName;
	}


	//解压缩
	const string UnCompressFile(string filename)
	{
		assert(!filename.empty());
		//得到解压缩之后的文件的名字
		string name;
	    name= filename;
		int i = 0;
		string posfix;
		for (i =(int)filename.size()-1; i>=0; --i)       //找到后缀出现的位置
		{
			posfix.push_back(filename[i]);
			if (filename[i] == '.')
				break;
		}
		reverse(posfix.begin(),posfix.end());       //让posfix保存要解压文件的后缀
		if (posfix != ".huf")                 //如果要解压的文件不是huffman压缩的，则不能解压
		{
			return NULL;
		}


		//去掉后缀
		name.resize(i);

		string UnCompressFileName = name;      //得到压缩文件名 
		UnCompressFileName += ".uhuf";

		string configName = name;
		configName+=".config";   //得到配置文件名

		//打开压缩文件
		FILE *fInput = fopen(filename.c_str(),"rb");
		FILE *fInput2 =fInput;
		assert(fInput);

		//打开解压缩文件
		FILE *fOut = fopen(UnCompressFileName.c_str(),"wb");
		if (fOut == NULL)
		{
			fclose(fInput);
			exit(EXIT_FAILURE);
		}

		int ch = 0;

		//读取配置文件
		FILE *configInput = fopen(configName.c_str(),"rb");       //打开配置文件名
		string line;
		int c = 0;
		while ((c = fgetc(configInput))!=EOF)          //读取一行
		{
			GetLine(configInput, line);                  
			_Infos[c]._count = atoi((&line[1]));       //获得字符出现的次数
			line.clear();
		}
		fclose(configInput);    //关闭配置文件

		//构建huffman树
		CharInfo invalid;
		HuffmanTree<CharInfo> ht(_Infos, 256, invalid);
		LongType count = ht.GetRoot()->_data._count;      //获取字符的总个数

		int pos=7;
		c = 1;
		HuffmanNode<CharInfo> *root= ht.GetRoot();           //得到huffman树的根节点
		HuffmanNode<CharInfo> *cur = root;      
		while (count > 0)                         //以字符的总个数作为结束标志
		{
			ch = fgetc(fInput);
			//处理ch的二进制
			while (pos >= 0 && count > 0)
			{
				//寻找叶子结点(编码所对应的字符)
				if (ch&(c << pos))
				{
					cur = cur->_right;
				}
				else
				{
					cur = cur->_left;
				}
				if (cur->_left == NULL&&cur->_right == NULL)    //找到huffman所对应的字符
				{
					//写文件
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
	//得到huffman编码
	void GetHufCode(HuffmanNode<CharInfo>* root, string str)
	{
		if (root == NULL)
			return;
		if (root->_left == NULL&&root->_right == NULL)
		{
			_Infos[root->_data._data]._Code = str;  //将huffman编码保存在infos里面
			return;
		}
		GetHufCode(root->_left, str + '0');    //向左子树走压0	
		GetHufCode(root->_right, str + '1');   //向右子树走压1		
	}

	bool GetLine(FILE*& Input,string &line)        //读取一行字符
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
