#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<string>
#include<cstdio>
#include<cassert>
#include<cstdlib>
#include<algorithm>
using namespace std;
#include"HuffmanTree.h"

const size_t N =2*32*1024;

enum { SlipBlock =32* 1024 };              //定义一个滑块的大小，是32K大小

typedef long long LongType;

struct CharInfo
{
	unsigned char _data;
	LongType _count;                //保存字符出现的次数
	string _Code;                   //保存Huffman编码
	CharInfo(LongType count = 0)
		:_count(count)
	{}

	CharInfo operator+(CharInfo& ch)
	{
		return CharInfo(_count + ch._count);
	}

	bool operator<(CharInfo &ch)
	{
		return _count < ch._count;
	}
};


class ZipCompress
{
public:
	ZipCompress()
	{
		for (int i = 0; i < 256; i++)   //将Infos中每个data初始化相应的字符
		{
			_Infos[i]._data = i;
		}
		_windows.reserve(N);             //开辟一个窗口，大小是N
		_frist=0;
		_last=0;
		time = 0;
	}

	size_t Gettime()
	{
		return time;
	}

	string Compress(const string& filename)
	{
		//先进行ZIP 一次压缩
		string fristCompress = _ZIP_FileCompress(filename);

		//进行Huffman二次压缩
		string SecondCompress=HufCompressFile(fristCompress);

		return SecondCompress;
	}

	string UnCompress(const string& filename)
	{
		//进行Huffman一次解压
		string fristUnCompress = HufUnCompressFile(filename);
		//进行ZIP二次解压
		string SecondUnCompress = _ZIP_UnCompress(fristUnCompress);

		return SecondUnCompress;
	}

protected:                //huffman二次压缩
	//Huffman文件压缩
	const string HufCompressFile(const string& filename)
	{
		GetHuffmanTree(filename);            //首先构建huffman树

		//得到压缩文件的文件名
		string CompressFileName = filename;
		CompressFileName += ".huf";

		FILE *fInput = fopen(filename.c_str(), "rb");     //打开原文件
		assert(fInput);

		FILE *fOut = fopen(CompressFileName.c_str(), "wb");   //打开压缩文件
		if (fOut == NULL)
		{
			fclose(fOut);
			exit(EXIT_FAILURE);
		}

		//编写配置文件,保存字符以及字符出现的次数，用于解压时重建huffmanTree
		string configFileName = filename;          //配置文件名
		configFileName += ".config";
		FILE *configOut = fopen(configFileName.c_str(), "wb");   //打开配置文件
		assert(configOut);
		string line;
		for (int i = 0; i < 256; i++)
		{
			if (_Infos[i]._count != 0)         //将字符以及出现的次数存在一行
			{
				int c = _Infos[i]._data;
				fputc(c, configOut);
				line += ",";
				char buffer[25] = { 0 };      //将次数转换成字符串存储
				line += _itoa((int)_Infos[i]._count, buffer, 10);
				line += '\n';
				fputs(line.c_str(), configOut);
				line.clear();
			}
		}
		fclose(configOut);                  //关闭配置文件

		int c = 0;                //用来保存huffman编码所构成的字符
		int pos = 7;             //判断处理的位数，如果到8则进行写入
		int ch = fgetc(fInput);
		while (ch != EOF)
		{
			string &code = _Infos[ch]._Code;
			for (size_t i = 0; i < code.size(); i++)     //处理ch这个字符的编码
			{
				c |= ((code[i] - '0') << pos);             //从高位开始相或
				pos--;
				if (pos<0)
				{
					fputc(c, fOut);
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

	//Huffman解压缩
	const string HufUnCompressFile(string filename)
	{
		assert(!filename.empty());
		//得到解压缩之后的文件的名字
		string name;
		name = filename;
		int i = 0;
		string posfix;
		for (i = (int)filename.size() - 1; i >= 0; --i)       //找到后缀出现的位置
		{
			posfix.push_back(filename[i]);
			if (filename[i] == '.')
				break;
		}
		reverse(posfix.begin(), posfix.end());       //让posfix保存要解压文件的后缀
		if (posfix != ".huf")                 //如果要解压的文件不是huffman压缩的，则不能解压
		{
			return NULL;
		}

		//去掉后缀
		name.resize(i);

		string UnCompressFileName = name;      //得到压缩文件名 
		UnCompressFileName += ".uhuf";

		string configName = name;
		configName += ".config";   //得到配置文件名

		//打开压缩文件
		FILE *fInput = fopen(filename.c_str(), "rb");
		FILE *fInput2 = fInput;
		assert(fInput);

		//打开解压缩文件
		FILE *fOut = fopen(UnCompressFileName.c_str(), "wb");
		if (fOut == NULL)
		{
			fclose(fInput);
			exit(EXIT_FAILURE);
		}

		int ch = 0;

		//读取配置文件
		FILE *configInput = fopen(configName.c_str(), "rb");       //打开配置文件名
		string line;
		int c = 0;
		while ((c = fgetc(configInput)) != EOF)          //读取一行
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

		int pos = 7;
		c = 1;
		HuffmanNode<CharInfo> *root = ht.GetRoot();           //得到huffman树的根节点
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
	string _ZIP_FileCompress(const string& filename)     //将原文件传入
	{
		assert(filename.c_str());
		string FirstCompressFileName = filename;      //得到第一次压缩的文件名
		FirstCompressFileName += ".fzip";             //加一个后缀  .zip

		FILE *fInput = fopen(filename.c_str(), "rb+"); //以只读的方式打开要读入的文件
		assert(fInput);

		FILE *fOut = fopen(FirstCompressFileName.c_str(), "wb+");  //以二进制写的方式打开第一次压缩的文件
		assert(fOut);

		FILE *pWindows = fopen(filename.c_str(), "rb+");  //定义指向滑动窗口起始位置的指针
		assert(pWindows);

		int ch = 0;
		ch = fgetc(fInput);

		LongType count = 0;
		//从原文件中读入字符，再判断需不需要进行压缩，只有当重复的字符出现3个以上时才压缩
		unsigned char buf = 0;
		int flag = 7;     //标记buf处理了几位

		while (ch != EOF)
		{
			long distance = 0;
			int length = 0;
			long OFFSET = ftell(fInput);          //文件的当前位置距离起始位置的偏移量

			//设置滑动窗口的大小
			if (OFFSET > SlipBlock)
			{
				fseek(pWindows, OFFSET - 1 - SlipBlock, SEEK_SET);  //文件指针退回到滑动窗口的起始位置
				distance = SlipBlock;
			}
			else
			{
				fseek(pWindows, 0, SEEK_SET);   //如果当前位置偏移量没有滑块大,将窗口指针设置在初始位置
				distance = OFFSET - 1;
			}

			if (distance > 1)
			{
				fseek(fInput, OFFSET - 1, SEEK_SET);    //向前退回一个字符
				length = FindRepetition(pWindows, fInput, distance);
				fseek(fInput, OFFSET, SEEK_SET);     //前进到原来位置
			}

			if (length>0)             //有重复的,用1表示有重复的
			{
				fseek(fInput, length - 1, SEEK_CUR);

				buf |= (1 << flag);        //先把flag这一位标记 设置成1
				flag--;
				if (flag < 0)    //buf这8位以经处理完毕，进行写入
				{
					fputc(buf, fOut);
					flag = 7;
					buf = 0;
				}

				//接下来把distance和length写入
				int pos = 15;
				while (pos >= 0)                    //处理两个字节的distance
				{
					if (distance&(1 << pos))        //如果length的第pos位为1
						buf |= (1 << flag);         //向buf中写1
					else
						buf &= (~(1 << flag));       //向buf中写0
					flag--;
					if (flag < 0)                    //buf这8位以经处理完毕，进行写入
					{
						fputc(buf, fOut);
						flag = 7;
						buf = 0;
					}
					pos--;
				}

				pos = 7;                             //接下来写入length
				while (pos >= 0)
				{
					if (length&(1 << pos))           //如果length的第pos位为1
						buf |= (1 << flag);           //向buf中写1
					else
						buf &= (~(1 << flag));       //向buf中写0
					flag--;
					if (flag < 0)                    //buf这8位以经处理完毕，进行写入
					{
						fputc(buf, fOut);
						flag = 7;
						buf = 0;
					}
					pos--;
				}
				count += 3;              //处理一个distance和一个length，count加三个字节
			}
			else                             //这个字符是普通字符
			{
				buf &= (~(1 << flag));       //把flag这一位设置成0
				flag--;
				if (flag < 0)                //buf这8位已经处理完毕，进行写入
				{
					fputc(buf, fOut);
					flag = 7;
					buf = 0;
				}

				//接下来处理ch这个字符
				int pos = 7;
				while (pos >= 0)
				{
					if (ch&(1 << pos))                //如果ch的第pos位为1
						buf |= (1 << flag);           //向buf中写1
					else
						buf &= (~(1 << flag));        //向buf中写0
					flag--;
					if (flag < 0)                     //buf这8位以经处理完毕，进行写入
					{
						fputc(buf, fOut);
						flag = 7;
						buf = 0;
					}
					pos--;
				}
				count++;              //处理一个字符，count++一次
			}
			ch = fgetc(fInput);
		}

		if (flag != 7)       //如果最后的bit位不够一个整数，则就在后面补0
		{
			fputc(buf, fOut);
		}
		fwrite(&count,1,8,fOut);
		fclose(fInput);
		fclose(fOut);
		fclose(pWindows);                             //关闭窗口指针所指向的文件
		return FirstCompressFileName;
	}

	//LZ77解压
	string _ZIP_UnCompress(const string& CompressFileName)        //将要解压的文件传入
	{
		string UnCompressFileName = CompressFileName;      //解压缩文件名
		UnCompressFileName += ".ufzip";

		FILE* fInput = fopen(CompressFileName.c_str(), "rb+");
		assert(fInput);

		FILE* fOut = fopen(UnCompressFileName.c_str(), "wb+");
		assert(fOut);

		FILE* pWindows = fopen(UnCompressFileName.c_str(), "rb+");  //定义窗口指针
		assert(pWindows);

		LongType count;
		fseek(fInput,-8,SEEK_END);
		fread(&count,1,8,fInput);          //count保存的是字符的个数

		fseek(fInput,0,SEEK_SET);
		//解压缩
		int c = 0;
		int ch = 0;
		ch = fgetc(fInput);

		unsigned char buf = 0;
		int status = 0;             //用来记录现在是处理字符还是距离和长度
		int flag = 7;               //记录buf处理到了第几位
		while (count>0)
		{
			int distance = 0;
			int length = 0;
			status = ch&(1 << flag);       //判断状态
			flag--;
			if (flag < 0)
			{
				ch = fgetc(fInput);
				flag = 7;
			}

			if (status != 0)            //这一位为1，表示距离和长度
			{
				//还原distance，连续读取两个字节
				int pos = 15;
				while (pos >= 0)
				{
					if (ch&(1 << flag))
						distance |= (1 << pos);           //在这一位写1
					else
						distance &= (~(1 << pos));           //在这一位写0
					flag--;
					if (flag < 0)
					{
						ch = fgetc(fInput);
						flag = 7;
					}
					pos--;
				}
				//读取length
				pos = 7;
				while (pos >= 0)
				{
					if (ch&(1 << flag))
						length |= (1 << pos);           //在这一位写1
					else
						length &= (~(1 << pos));           //在这一位写0
					flag--;
					if (flag < 0)
					{
						ch = fgetc(fInput);
						flag = 7;
					}
					pos--;
				}

				//复制滑动窗口中重复的字符
				fflush(fOut);                                  //将缓冲区的内容全部都写入文件
				int OFFSET = ftell(fOut);                      //记录这个位置，写入的这个位置
				fseek(pWindows, OFFSET - distance, SEEK_SET);  //让窗口指针指向窗口起始位置
				while (length--)
				{
					int c = fgetc(pWindows);
					fputc(c, fOut);
				}
				count -= 3;
			}
			else              //原字符
			{
				int pos = 7;
				while (pos >= 0)
				{
					if (ch&(1 << flag))
						buf |= (1 << pos);           //在这一位写1
					else
						buf &= (~(1 << pos));           //在这一位写0
					flag--;
					if (flag < 0)
					{
						ch = fgetc(fInput);
						flag = 7;
					}
					pos--;
				}
				fputc(buf, fOut);
				count--;
				buf = 0;
			}
		}
		fclose(fInput);
		fclose(fOut);
		fclose(pWindows);
		return UnCompressFileName;
	}
protected:
	//构建huffman树
	void GetHuffmanTree(const string& filename)
	{
		assert(!filename.empty());
		FILE *fInput = fopen(filename.c_str(), "rb");   //打开文件
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

	//读取一行
	bool GetLine(FILE*& Input, string &line)        //读取一行字符
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

	int FindRepetition(FILE* pWindows,FILE *fInput, long& distance)
	{ 
		long OFFSET1= ftell(pWindows);     //记录窗口距离文件开始的距离
		long OFFSET2= ftell(fInput);       //记录当前要比较的字符串距离文件开始的距离
		int ch = 0;

		if ((size_t)OFFSET2>_last)
		{
			_windows.clear();
			for (size_t i = 0; i<N; i++)
			{
				ch = fgetc(pWindows);
				if (ch == EOF)
					break;
				_windows.push_back(ch);
			}
			_frist = OFFSET1;           //记录加载到窗口的数据的起始位置
			_last = _windows.size() + OFFSET1;
		}

		int length = GetRepetionlength(fInput, distance, OFFSET1);
		return length;
	} 

	int  GetRepetionlength(FILE *fInput, long& distance, long pWindowsPos)     //得到重复的长度
	{
		long OFFSET = ftell(fInput);                //得到要比较的字符的位置

		vector<unsigned char> v;
		if (Getch(fInput, v)==false)
			return 0;

		size_t size = OFFSET-pWindowsPos;
		size_t index = pWindowsPos-_frist;

		int length = 0;

		for(; index<size; ++index)
		{
			if (_windows[index] == v[0])
			{
				size_t flag = index;
				size_t i = 0;
				while ((flag < size) && (length<255))
				{
					if (i==v.size()-1)
					{
						if (Getch(fInput, v)==false)
							break;
					}
					if (_windows[flag] == v[i])
					{
						length++;
						flag++;
						i++;
					}
					else
						break;
				}
				if (length > 3)
				{
					distance = OFFSET - (index+_frist);
					return length;             //如果重复出现的字符的长度大于3，则就返回重复长度
				}
				length = 0;
			}
		}
		return 0;    
	} 

	bool Getch(FILE *fInput, vector<unsigned char>& v)
	{
		int ch =0;
		for (int i =10; (ch!= EOF)&&(i>0); --i)
		{
			ch = fgetc(fInput);
			v.push_back(ch);
		}

		if (ch == EOF)
			return false;
		else
			return true;
	}

private:
	size_t time;
	CharInfo _Infos[257];
	vector<unsigned char> _windows;
	size_t _frist;
	size_t _last;
};
