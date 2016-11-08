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

	const string CompressFile(string filename)
	{
		vector<string> file;
		string path = filename.c_str();
		getFiles(path, file);

		if (file.empty())     //���Ϊ�գ����ʾ��һ���ļ�
		{
			 return _CompressFile(filename);
		}
		else                        //һ���ļ���
		{ 
			//���ȴ���һ���µ��ļ���
			string newpath=path;               //���ļ��е�·����
			newpath += ".huf";
			_mkdir(newpath.c_str());   //

			for (int i = 0; i < (int)file.size(); i++)
			{
				_CompressFile(file[i],newpath);
			}
			return newpath;          //�����½����ļ���
		}
	}

	const string UnCompressFile(string filename)
	{
		vector<string> file;
		string path = filename.c_str();
		getFiles(path, file);

		if (file.empty())     //���Ϊ�գ����ʾ��һ���ļ����н�ѹ��
		{
			return _UnCompressFile(filename);
		}
		else                        //һ���ļ��н��н�ѹ��
		{
			//���ȴ���һ���µ��ļ���
			string newpath =filename;               //���ļ���
			for (int i = (int)filename.size() - 1; i >= 0; i--)
			{
				if (filename[i] == '.')
				{
					newpath.resize(i);
					break;
				}
			}
			newpath += ".uhuf";                  //���ļ��е�·����
			_mkdir(newpath.c_str());             //����һ���µĽ�ѹ�����ļ���

			for (int i = 0; i < (int)file.size(); i++)
			{
				_UnCompressFile(file[i], newpath);
			}
			return newpath;          //�����½����ļ���
		}
	}
protected:
	//�ļ�ѹ��
	const string _CompressFile(const string filename,const string path=string())
	{
		CreatHuffmanTree(filename.c_str());
		//�õ�ѹ���ļ����ļ���
		string CompressFileName = filename;
		CompressFileName += ".huf";

		FILE *fInput = fopen(filename.c_str(),"rb");     //��ԭ�ļ�
		assert(fInput);
		FILE *fOut=NULL;

		string configFileName = filename;          //�����ļ���
		configFileName += ".config";
		FILE *configOut=NULL;

		if (path.empty())            //Ϊ�ձ�ʾ�ǵ����ļ�
		{
			fOut = fopen(CompressFileName.c_str(), "wb");   //��ѹ���ļ�
			if (fOut == NULL)
			{
				fclose(fOut);
				exit(EXIT_FAILURE);
			}
			//��д�����ļ�,�����ַ��Լ��ַ����ֵĴ��������ڽ�ѹʱ�ؽ�huffmanTree
			configOut = fopen(configFileName.c_str(), "wb");   //�������ļ�
			assert(configOut);
		}
		else             //��Ϊ�ձ�ʾ���ļ���
		{
			//�õ�Ҫ������·��
			string FileName;          //�õ��ļ���
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
			fOut = fopen(newpath.c_str(), "wb");   //��ѹ���ļ�
			if (fOut == NULL)
			{
				fclose(fOut);
				exit(EXIT_FAILURE);
			}

			//��д�����ļ�,�����ַ��Լ��ַ����ֵĴ��������ڽ�ѹʱ�ؽ�huffmanTree
			newpath = path;
			newpath += '\\';
			newpath += FileName;
			newpath += ".config";
		    configOut = fopen(newpath.c_str(), "wb");   //�������ļ�
			assert(configOut);
		}

		string line;
		for (int i = 0; i < 256; i++)
		{
			if (_Infos[i]._count!=0)         //���ַ��Լ����ֵĴ�������һ��
			{
				int c=_Infos[i]._data;
				fputc(c,configOut);
				line += ",";
				char buffer[25] = { 0 };      //������ת�����ַ����洢
				line+=_itoa((int)_Infos[i]._count, buffer, 10);
				line += '\n';
				fwrite(line.c_str(),1,line.size(),configOut);
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
		memset(_Infos, 0, 256 * sizeof(CharInfo));
		return CompressFileName;
	}


	//��ѹ��
	const string _UnCompressFile(string filename,const string path=string())
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

		if (posfix!= ".huf")                 //���Ҫ��ѹ���ļ�����huffmanѹ���ģ����ܽ�ѹ
		{
			return string();
		}
		//ȥ����׺
		name.resize(i);

		string UnCompressFileName = name;      //�õ�ѹ���ļ��� 
		UnCompressFileName += ".uhuf";

		string configName = name;
		configName+=".config";   //�õ������ļ���

		//��ѹ���ļ�
		FILE *fInput = fopen(filename.c_str(),"rb");
		assert(fInput);

		FILE *configInput=fopen(configName.c_str(), "rb");       //�������ļ�
		assert(configInput);

		FILE *fOut = NULL;              //��ѹ���ļ�
		if (path.empty())             //���Ϊ�գ���ʾ�ǵ����ļ���ѹ
		{
			//�򿪽�ѹ���ļ�
			fOut = fopen(UnCompressFileName.c_str(), "wb");
			if (fOut == NULL)
			{
				fclose(fInput);
				exit(EXIT_FAILURE);
			}
		}
		else                           //�ļ��н��н�ѹ��
		{
			string FileName;         //�ȵõ�ѹ�����ļ���
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

			//�򿪽�ѹ���ļ�
			fOut = fopen(newpath.c_str(), "wb");
			if (fOut == NULL)
			{
				fclose(fInput);
				exit(EXIT_FAILURE);
			}
		}

		string line;
		int c = 0;
		while ((c = fgetc(configInput))!=EOF)          //��ȡһ��
		{
			GetLine(configInput, line);                  
			_Infos[c]._count = atoi((&line[1]));       //����ַ����ֵĴ���
			line.clear();
		}
		fclose(configInput);    //�ر������ļ�

		int ch = 0;
		//����huffman��
		CharInfo invalid;
		for (int i = 0; i < 256; i++)   //��Infos��ÿ��data��ʼ����Ӧ���ַ�
		{
			_Infos[i]._data = i;
		}
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
		for (int i = 0; i < 256; i++)   //��Infos��ÿ��data��ʼ����Ӧ���ַ�
		{
			_Infos[i]._data = i;
		}

		FILE *fInput = fopen(filename, "rb");   //���ļ�
		assert(fInput);
		int ch = 0;

		while ((ch = fgetc(fInput)) != EOF)    //���ļ���ͳ���ַ����ִ���
		{
			_Infos[ch]._count++;
		}

		//����huffman��
		CharInfo invalid;
		HuffmanTree<CharInfo> ht(_Infos, 256, invalid);

		//�õ�huffman����
		string str;
		GetHufCode(ht.GetRoot(), str);
		fclose(fInput);
	}


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

	void getFiles(string path, vector<string>& files)
	{
		//�ļ����
		long   hFile = 0;
		//�ļ���Ϣ
		struct _finddata_t fileinfo;
		string p;
		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				//�����Ŀ¼,����֮
				//�������,�����б�
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
