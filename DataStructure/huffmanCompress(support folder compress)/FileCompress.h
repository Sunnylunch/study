#pragma once
#include<string>
#include<cstdio>
#include<cassert>
#include <direct.h>
#include <stdlib.h>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<io.h>
#include<cstring>
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

	const string CompressFile(string filename)
	{
		vector<string> file;
		string path = filename.c_str();
		getFiles(path, file);

		if (file.empty())     //如果为空，则表示是一个文件
		{
			 return _CompressFile(filename);
		}
		else                        //一个文件夹
		{ 
			//首先创建一个新的文件夹
			string newpath=path;               //新文件夹的路径名
			newpath += ".huf";
			_mkdir(newpath.c_str());   //

			for (int i = 0; i < (int)file.size(); i++)
			{
				_CompressFile(file[i],newpath);
			}
			return newpath;          //返回新建的文件夹
		}
	}

	const string UnCompressFile(string filename)
	{
		vector<string> file;
		string path = filename.c_str();
		getFiles(path, file);

		if (file.empty())     //如果为空，则表示是一个文件进行解压缩
		{
			return _UnCompressFile(filename);
		}
		else                        //一个文件夹进行解压缩
		{
			//首先创建一个新的文件夹
			string newpath =filename;               //新文件夹
			for (int i = (int)filename.size() - 1; i >= 0; i--)
			{
				if (filename[i] == '.')
				{
					newpath.resize(i);
					break;
				}
			}
			newpath += ".uhuf";                  //新文件夹的路径名
			_mkdir(newpath.c_str());             //创建一个新的解压缩的文件夹

			for (int i = 0; i < (int)file.size(); i++)
			{
				_UnCompressFile(file[i], newpath);
			}
			return newpath;          //返回新建的文件夹
		}
	}
protected:
	//文件压缩
	const string _CompressFile(const string filename,const string path=string())
	{
		CreatHuffmanTree(filename.c_str());
		//得到压缩文件的文件名
		string CompressFileName = filename;
		CompressFileName += ".huf";

		FILE *fInput = fopen(filename.c_str(),"rb");     //打开原文件
		assert(fInput);
		FILE *fOut=NULL;

		string configFileName = filename;          //配置文件名
		configFileName += ".config";
		FILE *configOut=NULL;

		if (path.empty())            //为空表示是单个文件
		{
			fOut = fopen(CompressFileName.c_str(), "wb");   //打开压缩文件
			if (fOut == NULL)
			{
				fclose(fOut);
				exit(EXIT_FAILURE);
			}
			//编写配置文件,保存字符以及字符出现的次数，用于解压时重建huffmanTree
			configOut = fopen(configFileName.c_str(), "wb");   //打开配置文件
			assert(configOut);
		}
		else             //不为空表示是文件夹
		{
			//得到要创建的路径
			string FileName;          //得到文件名
			int i = filename.size()- 1;
			for (; i >=0;i--)
			{
				if (filename[i] == '\\')
					break;
				FileName += filename[i];
			}
			reverse(FileName.begin(), FileName.end());

			string newpath=path;
			newpath += '\\';
			newpath += FileName;
			newpath += ".huf";
			fOut = fopen(newpath.c_str(), "wb");   //打开压缩文件
			if (fOut == NULL)
			{
				fclose(fOut);
				exit(EXIT_FAILURE);
			}

			//编写配置文件,保存字符以及字符出现的次数，用于解压时重建huffmanTree
			newpath = path;
			newpath += '\\';
			newpath += FileName;
			newpath += ".config";
		    configOut = fopen(newpath.c_str(), "wb");   //打开配置文件
			assert(configOut);
		}

		string line;
		for (int i = 0; i < 256; i++)
		{
			if (_Infos[i]._count!=0)         //将字符以及出现的次数存在一行
			{
				int c=_Infos[i]._data;
				fputc(c,configOut);
				line += ",";
				char buffer[25] = { 0 };      //将次数转换成字符串存储
				line+=_itoa((int)_Infos[i]._count, buffer, 10);
				line += '\n';
				fwrite(line.c_str(),1,line.size(),configOut);
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
		memset(_Infos, 0, 256 * sizeof(CharInfo));
		return CompressFileName;
	}


	//解压缩
	const string _UnCompressFile(string filename,const string path=string())
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

		if (posfix!= ".huf")                 //如果要解压的文件不是huffman压缩的，则不能解压
		{
			return string();
		}
		//去掉后缀
		name.resize(i);

		string UnCompressFileName = name;      //得到压缩文件名 
		UnCompressFileName += ".uhuf";

		string configName = name;
		configName+=".config";   //得到配置文件名

		//打开压缩文件
		FILE *fInput = fopen(filename.c_str(),"rb");
		assert(fInput);

		FILE *configInput=fopen(configName.c_str(), "rb");       //打开配置文件
		assert(configInput);

		FILE *fOut = NULL;              //解压缩文件
		if (path.empty())             //如果为空，表示是单个文件解压
		{
			//打开解压缩文件
			fOut = fopen(UnCompressFileName.c_str(), "wb");
			if (fOut == NULL)
			{
				fclose(fInput);
				exit(EXIT_FAILURE);
			}
		}
		else                           //文件夹进行解压缩
		{
			string FileName;         //先得到压缩的文件名
			for (int i = (int)name.size() - 1; i >= 0; i--)
			{
				if (name[i] == '\\')
				{
					break;
				}
				FileName += name[i];
			}
			reverse(FileName.begin(), FileName.end());

			string newpath = path;
			newpath += "\\";
			newpath += FileName;
			newpath += ".uhuf";

			//打开解压缩文件
			fOut = fopen(newpath.c_str(), "wb");
			if (fOut == NULL)
			{
				fclose(fInput);
				exit(EXIT_FAILURE);
			}
		}

		string line;
		int c = 0;
		while ((c = fgetc(configInput))!=EOF)          //读取一行
		{
			GetLine(configInput, line);                  
			_Infos[c]._count = atoi((&line[1]));       //获得字符出现的次数
			line.clear();
		}
		fclose(configInput);    //关闭配置文件

		int ch = 0;
		//构建huffman树
		CharInfo invalid;
		for (int i = 0; i < 256; i++)   //将Infos中每个data初始化相应的字符
		{
			_Infos[i]._data = i;
		}
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
					//if (cur->_data._data == '\n')
					//	fputc(13, fOut);
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
		memset(_Infos, 0, 256 * sizeof(CharInfo));
	    return UnCompressFileName;
	}

protected:
	void CreatHuffmanTree(const char * filename)
	{
		assert(filename != NULL);
		for (int i = 0; i < 256; i++)   //将Infos中每个data初始化相应的字符
		{
			_Infos[i]._data = i;
		}

		FILE *fInput = fopen(filename, "rb");   //打开文件
		assert(fInput);
		int ch = 0;

		while ((ch = fgetc(fInput)) != EOF)    //读文件，统计字符出现次数
		{
			_Infos[ch]._count++;
		}

		//构建huffman树
		CharInfo invalid;
		HuffmanTree<CharInfo> ht(_Infos, 256, invalid);

		//得到huffman编码
		string str;
		GetHufCode(ht.GetRoot(), str);
		fclose(fInput);
	}


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

	void getFiles(string path, vector<string>& files)
	{
		//文件句柄
		long   hFile = 0;
		//文件信息
		struct _finddata_t fileinfo;
		string p;
		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				//如果是目录,迭代之
				//如果不是,加入列表
				if ((fileinfo.attrib &  _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				}
				else
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
	}
private:
	CharInfo _Infos[256];
};
