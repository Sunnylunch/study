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

enum { SlipBlock =32* 1024 };              //����һ������Ĵ�С����32K��С

typedef long long LongType;

struct CharInfo
{
	unsigned char _data;
	LongType _count;                //�����ַ����ֵĴ���
	string _Code;                   //����Huffman����
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
		for (int i = 0; i < 256; i++)   //��Infos��ÿ��data��ʼ����Ӧ���ַ�
		{
			_Infos[i]._data = i;
		}
		_windows.reserve(N);             //����һ�����ڣ���С��N
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
		//�Ƚ���ZIP һ��ѹ��
		string fristCompress = _ZIP_FileCompress(filename);

		//����Huffman����ѹ��
		string SecondCompress=HufCompressFile(fristCompress);

		return SecondCompress;
	}

	string UnCompress(const string& filename)
	{
		//����Huffmanһ�ν�ѹ
		string fristUnCompress = HufUnCompressFile(filename);
		//����ZIP���ν�ѹ
		string SecondUnCompress = _ZIP_UnCompress(fristUnCompress);

		return SecondUnCompress;
	}

protected:                //huffman����ѹ��
	//Huffman�ļ�ѹ��
	const string HufCompressFile(const string& filename)
	{
		GetHuffmanTree(filename);            //���ȹ���huffman��

		//�õ�ѹ���ļ����ļ���
		string CompressFileName = filename;
		CompressFileName += ".huf";

		FILE *fInput = fopen(filename.c_str(), "rb");     //��ԭ�ļ�
		assert(fInput);

		FILE *fOut = fopen(CompressFileName.c_str(), "wb");   //��ѹ���ļ�
		if (fOut == NULL)
		{
			fclose(fOut);
			exit(EXIT_FAILURE);
		}

		//��д�����ļ�,�����ַ��Լ��ַ����ֵĴ��������ڽ�ѹʱ�ؽ�huffmanTree
		string configFileName = filename;          //�����ļ���
		configFileName += ".config";
		FILE *configOut = fopen(configFileName.c_str(), "wb");   //�������ļ�
		assert(configOut);
		string line;
		for (int i = 0; i < 256; i++)
		{
			if (_Infos[i]._count != 0)         //���ַ��Լ����ֵĴ�������һ��
			{
				int c = _Infos[i]._data;
				fputc(c, configOut);
				line += ",";
				char buffer[25] = { 0 };      //������ת�����ַ����洢
				line += _itoa((int)_Infos[i]._count, buffer, 10);
				line += '\n';
				fputs(line.c_str(), configOut);
				line.clear();
			}
		}
		fclose(configOut);                  //�ر������ļ�

		int c = 0;                //��������huffman���������ɵ��ַ�
		int pos = 7;             //�жϴ����λ���������8�����д��
		int ch = fgetc(fInput);
		while (ch != EOF)
		{
			string &code = _Infos[ch]._Code;
			for (size_t i = 0; i < code.size(); i++)     //����ch����ַ��ı���
			{
				c |= ((code[i] - '0') << pos);             //�Ӹ�λ��ʼ���
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

		if (pos<7)   //�������һ���ַ����벻��8λ�����
		{
			fputc(c, fOut);
		}
		fclose(fOut);
		fclose(fInput);

		return CompressFileName;
	}

	//Huffman��ѹ��
	const string HufUnCompressFile(string filename)
	{
		assert(!filename.empty());
		//�õ���ѹ��֮����ļ�������
		string name;
		name = filename;
		int i = 0;
		string posfix;
		for (i = (int)filename.size() - 1; i >= 0; --i)       //�ҵ���׺���ֵ�λ��
		{
			posfix.push_back(filename[i]);
			if (filename[i] == '.')
				break;
		}
		reverse(posfix.begin(), posfix.end());       //��posfix����Ҫ��ѹ�ļ��ĺ�׺
		if (posfix != ".huf")                 //���Ҫ��ѹ���ļ�����huffmanѹ���ģ����ܽ�ѹ
		{
			return NULL;
		}

		//ȥ����׺
		name.resize(i);

		string UnCompressFileName = name;      //�õ�ѹ���ļ��� 
		UnCompressFileName += ".uhuf";

		string configName = name;
		configName += ".config";   //�õ������ļ���

		//��ѹ���ļ�
		FILE *fInput = fopen(filename.c_str(), "rb");
		FILE *fInput2 = fInput;
		assert(fInput);

		//�򿪽�ѹ���ļ�
		FILE *fOut = fopen(UnCompressFileName.c_str(), "wb");
		if (fOut == NULL)
		{
			fclose(fInput);
			exit(EXIT_FAILURE);
		}

		int ch = 0;

		//��ȡ�����ļ�
		FILE *configInput = fopen(configName.c_str(), "rb");       //�������ļ���
		string line;
		int c = 0;
		while ((c = fgetc(configInput)) != EOF)          //��ȡһ��
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

		int pos = 7;
		c = 1;
		HuffmanNode<CharInfo> *root = ht.GetRoot();           //�õ�huffman���ĸ��ڵ�
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
	string _ZIP_FileCompress(const string& filename)     //��ԭ�ļ�����
	{
		assert(filename.c_str());
		string FirstCompressFileName = filename;      //�õ���һ��ѹ�����ļ���
		FirstCompressFileName += ".fzip";             //��һ����׺  .zip

		FILE *fInput = fopen(filename.c_str(), "rb+"); //��ֻ���ķ�ʽ��Ҫ������ļ�
		assert(fInput);

		FILE *fOut = fopen(FirstCompressFileName.c_str(), "wb+");  //�Զ�����д�ķ�ʽ�򿪵�һ��ѹ�����ļ�
		assert(fOut);

		FILE *pWindows = fopen(filename.c_str(), "rb+");  //����ָ�򻬶�������ʼλ�õ�ָ��
		assert(pWindows);

		int ch = 0;
		ch = fgetc(fInput);

		LongType count = 0;
		//��ԭ�ļ��ж����ַ������ж��費��Ҫ����ѹ����ֻ�е��ظ����ַ�����3������ʱ��ѹ��
		unsigned char buf = 0;
		int flag = 7;     //���buf�����˼�λ

		while (ch != EOF)
		{
			long distance = 0;
			int length = 0;
			long OFFSET = ftell(fInput);          //�ļ��ĵ�ǰλ�þ�����ʼλ�õ�ƫ����

			//���û������ڵĴ�С
			if (OFFSET > SlipBlock)
			{
				fseek(pWindows, OFFSET - 1 - SlipBlock, SEEK_SET);  //�ļ�ָ���˻ص��������ڵ���ʼλ��
				distance = SlipBlock;
			}
			else
			{
				fseek(pWindows, 0, SEEK_SET);   //�����ǰλ��ƫ����û�л����,������ָ�������ڳ�ʼλ��
				distance = OFFSET - 1;
			}

			if (distance > 1)
			{
				fseek(fInput, OFFSET - 1, SEEK_SET);    //��ǰ�˻�һ���ַ�
				length = FindRepetition(pWindows, fInput, distance);
				fseek(fInput, OFFSET, SEEK_SET);     //ǰ����ԭ��λ��
			}

			if (length>0)             //���ظ���,��1��ʾ���ظ���
			{
				fseek(fInput, length - 1, SEEK_CUR);

				buf |= (1 << flag);        //�Ȱ�flag��һλ��� ���ó�1
				flag--;
				if (flag < 0)    //buf��8λ�Ծ�������ϣ�����д��
				{
					fputc(buf, fOut);
					flag = 7;
					buf = 0;
				}

				//��������distance��lengthд��
				int pos = 15;
				while (pos >= 0)                    //���������ֽڵ�distance
				{
					if (distance&(1 << pos))        //���length�ĵ�posλΪ1
						buf |= (1 << flag);         //��buf��д1
					else
						buf &= (~(1 << flag));       //��buf��д0
					flag--;
					if (flag < 0)                    //buf��8λ�Ծ�������ϣ�����д��
					{
						fputc(buf, fOut);
						flag = 7;
						buf = 0;
					}
					pos--;
				}

				pos = 7;                             //������д��length
				while (pos >= 0)
				{
					if (length&(1 << pos))           //���length�ĵ�posλΪ1
						buf |= (1 << flag);           //��buf��д1
					else
						buf &= (~(1 << flag));       //��buf��д0
					flag--;
					if (flag < 0)                    //buf��8λ�Ծ�������ϣ�����д��
					{
						fputc(buf, fOut);
						flag = 7;
						buf = 0;
					}
					pos--;
				}
				count += 3;              //����һ��distance��һ��length��count�������ֽ�
			}
			else                             //����ַ�����ͨ�ַ�
			{
				buf &= (~(1 << flag));       //��flag��һλ���ó�0
				flag--;
				if (flag < 0)                //buf��8λ�Ѿ�������ϣ�����д��
				{
					fputc(buf, fOut);
					flag = 7;
					buf = 0;
				}

				//����������ch����ַ�
				int pos = 7;
				while (pos >= 0)
				{
					if (ch&(1 << pos))                //���ch�ĵ�posλΪ1
						buf |= (1 << flag);           //��buf��д1
					else
						buf &= (~(1 << flag));        //��buf��д0
					flag--;
					if (flag < 0)                     //buf��8λ�Ծ�������ϣ�����д��
					{
						fputc(buf, fOut);
						flag = 7;
						buf = 0;
					}
					pos--;
				}
				count++;              //����һ���ַ���count++һ��
			}
			ch = fgetc(fInput);
		}

		if (flag != 7)       //�������bitλ����һ������������ں��油0
		{
			fputc(buf, fOut);
		}
		fwrite(&count,1,8,fOut);
		fclose(fInput);
		fclose(fOut);
		fclose(pWindows);                             //�رմ���ָ����ָ����ļ�
		return FirstCompressFileName;
	}

	//LZ77��ѹ
	string _ZIP_UnCompress(const string& CompressFileName)        //��Ҫ��ѹ���ļ�����
	{
		string UnCompressFileName = CompressFileName;      //��ѹ���ļ���
		UnCompressFileName += ".ufzip";

		FILE* fInput = fopen(CompressFileName.c_str(), "rb+");
		assert(fInput);

		FILE* fOut = fopen(UnCompressFileName.c_str(), "wb+");
		assert(fOut);

		FILE* pWindows = fopen(UnCompressFileName.c_str(), "rb+");  //���崰��ָ��
		assert(pWindows);

		LongType count;
		fseek(fInput,-8,SEEK_END);
		fread(&count,1,8,fInput);          //count��������ַ��ĸ���

		fseek(fInput,0,SEEK_SET);
		//��ѹ��
		int c = 0;
		int ch = 0;
		ch = fgetc(fInput);

		unsigned char buf = 0;
		int status = 0;             //������¼�����Ǵ����ַ����Ǿ���ͳ���
		int flag = 7;               //��¼buf�����˵ڼ�λ
		while (count>0)
		{
			int distance = 0;
			int length = 0;
			status = ch&(1 << flag);       //�ж�״̬
			flag--;
			if (flag < 0)
			{
				ch = fgetc(fInput);
				flag = 7;
			}

			if (status != 0)            //��һλΪ1����ʾ����ͳ���
			{
				//��ԭdistance��������ȡ�����ֽ�
				int pos = 15;
				while (pos >= 0)
				{
					if (ch&(1 << flag))
						distance |= (1 << pos);           //����һλд1
					else
						distance &= (~(1 << pos));           //����һλд0
					flag--;
					if (flag < 0)
					{
						ch = fgetc(fInput);
						flag = 7;
					}
					pos--;
				}
				//��ȡlength
				pos = 7;
				while (pos >= 0)
				{
					if (ch&(1 << flag))
						length |= (1 << pos);           //����һλд1
					else
						length &= (~(1 << pos));           //����һλд0
					flag--;
					if (flag < 0)
					{
						ch = fgetc(fInput);
						flag = 7;
					}
					pos--;
				}

				//���ƻ����������ظ����ַ�
				fflush(fOut);                                  //��������������ȫ����д���ļ�
				int OFFSET = ftell(fOut);                      //��¼���λ�ã�д������λ��
				fseek(pWindows, OFFSET - distance, SEEK_SET);  //�ô���ָ��ָ�򴰿���ʼλ��
				while (length--)
				{
					int c = fgetc(pWindows);
					fputc(c, fOut);
				}
				count -= 3;
			}
			else              //ԭ�ַ�
			{
				int pos = 7;
				while (pos >= 0)
				{
					if (ch&(1 << flag))
						buf |= (1 << pos);           //����һλд1
					else
						buf &= (~(1 << pos));           //����һλд0
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
	//����huffman��
	void GetHuffmanTree(const string& filename)
	{
		assert(!filename.empty());
		FILE *fInput = fopen(filename.c_str(), "rb");   //���ļ�
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

	//��ȡһ��
	bool GetLine(FILE*& Input, string &line)        //��ȡһ���ַ�
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
		long OFFSET1= ftell(pWindows);     //��¼���ھ����ļ���ʼ�ľ���
		long OFFSET2= ftell(fInput);       //��¼��ǰҪ�Ƚϵ��ַ��������ļ���ʼ�ľ���
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
			_frist = OFFSET1;           //��¼���ص����ڵ����ݵ���ʼλ��
			_last = _windows.size() + OFFSET1;
		}

		int length = GetRepetionlength(fInput, distance, OFFSET1);
		return length;
	} 

	int  GetRepetionlength(FILE *fInput, long& distance, long pWindowsPos)     //�õ��ظ��ĳ���
	{
		long OFFSET = ftell(fInput);                //�õ�Ҫ�Ƚϵ��ַ���λ��

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
					return length;             //����ظ����ֵ��ַ��ĳ��ȴ���3����ͷ����ظ�����
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
