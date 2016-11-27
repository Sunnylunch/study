#pragma once
#include<vector>
#include<cassert>
#include<cstdio>
#include<stdlib.h>
#include<algorithm>
using namespace std;

class BigDataSort
{
public:
	BigDataSort(char * bigfile, int n, size_t limit)    //n��ʾҪ�зֳɶ����С�ļ�
		:_bigfile(bigfile)                              //bigfile��ʾҪ������ļ���
		, _limit(limit)                                 //_limit����С�ļ�������ŵ����ݸ���
	{
		_SmallFileName.resize(n);
		for (int i = 0; i < n;++i)                      //�ȴ���n���ļ���
		{
			char name[128] = {0};
			_itoa(i,name,10);
			_SmallFileName[i] = name;
		}
	}

	void Sort()
	{
		separate();                 //�з��ļ�
		SmallFileSort();            //С�ļ��ϲ�
		SmallFileMerge();           //С�ļ��鲢
	}
protected:
	void separate()         //�����ļ����ݷָС�ļ���,_limit��ʾһ��С�ļ��д�Ŷ�������
	{
		FILE *fRead = fopen(_bigfile,"rb");
		assert(fRead);
		for (size_t i = 0; i < _SmallFileName.size(); i++)
		{
			FILE *fWrite = fopen(_SmallFileName[i].c_str(), "wb");         //��д�ķ�ʽ��С�ļ�
			assert(fWrite);

			for (size_t count = 0; count < _limit; count++)
			{
				string line; 
				if (_GetLine(fRead,line))  //�����ȡ�ɹ����������д��С�ļ���
				{
					line += '\n';
					fputs(line.c_str(),fWrite);
					line.clear();
				}
				else
				{
					fclose(fWrite);
					fclose(fRead);
					return;
				}
			}
			fclose(fWrite);        //�ر�С�ļ�
		}
		fclose(fRead);
	}


	void SmallFileSort()           //��С�ļ���������
	{
		for (size_t i = 0; i < _SmallFileName.size(); ++i)
		{
			FILE *fRead = fopen(_SmallFileName[i].c_str(), "rb");
			assert(fRead);
			vector<int> v;
			for (size_t count = 0; count < _limit; ++count)    //����ЩС�ļ��е����ݼ��ص��ڴ�
			{
				int num = 0;
				if (_GetNum(fRead, num))               //�����ȡ�ɹ��������ŵ�vector��
					v.push_back(num);
				else
					break;
			}
			fclose(fRead);

			//����Щ���ݽ��п�������
			sort(v.begin(),v.end());
	
			//����Щ������д���ļ���
			FILE *fWrite = fopen(_SmallFileName[i].c_str(), "wb");
			assert(fWrite);
			for (size_t i = 0; i <v.size(); ++i)       //����ЩС�ļ��е����ݼ��ص��ڴ�
			{
				_InputNum(fWrite,v[i]);         //���ļ���д��һ����
			}
			fclose(fWrite);
		}
	}

	//����Щ�ļ����й鲢����
	void SmallFileMerge()
	{
		while (_SmallFileName.size()>1)       //����ЩС�ļ����ϲ���ֻʣһ���ļ�
		{
			vector<string> v;
			while (_SmallFileName.size() > 1)
			{
				string filename1 = _SmallFileName.back();
				_SmallFileName.pop_back();
				string filename2 = _SmallFileName.back();
				_SmallFileName.pop_back();

				FILE *fRead1 = fopen(filename1.c_str(), "rb");
				assert(fRead1);
				FILE *fRead2 = fopen(filename2.c_str(), "rb");
				assert(fRead2);

				string newfile = filename1 + filename2;     //����һ���µ��ļ�������������������ļ��ϲ���Ľ��
				v.push_back(newfile);                       //�����ļ���������

				FILE* fWrite = fopen(newfile.c_str(), "wb");
				assert(fWrite);

				_Merge(fRead1,fRead2,fWrite);               //���������ļ��е����ݽ��й鲢����

				fclose(fRead1);
				fclose(fRead2);
				fclose(fWrite);

				remove(filename1.c_str());                   //ɾ����Щ�Ѿ��ϲ����ĸ����ļ�
				remove(filename2.c_str());
			}
			for (size_t i = 0; i < v.size(); ++i)
			{
				_SmallFileName.push_back(v[i]);
			}
		}

		//�����ϲ����ļ��ٿ�����ԭ�ļ���
		FILE* fWrite = fopen(_bigfile,"wb");
		assert(fWrite);

		string filename = _SmallFileName[0];
		FILE* fRead= fopen(filename.c_str(), "rb");
		assert(fRead);

		string line;
		while (_GetLine(fRead,line))
		{
			line += '\n';
			fputs(line.c_str(), fWrite);
			line.clear();
		}	
		fclose(fWrite);
		fclose(fRead); 
		remove(filename.c_str());             //ɾ�������ļ�
	}

protected:
	void _Merge(FILE* fRead1,FILE* fRead2,FILE* fWrite)        //��С�ļ����кϲ�
	{
		int num1 = 0;
		int num2 = 0;
		bool file1 = _GetNum(fRead1,num1);
		bool file2 = _GetNum(fRead2,num2);
		while (file1!=false&&file2!=false)          //�鲢���� 
		{
			if (num1<num2)
			{
				_InputNum(fWrite,num1);         //���ļ���д��һ����
				file1 =_GetNum(fRead1, num1);
			}
			else
			{
				_InputNum(fWrite, num2);
				file2 = _GetNum(fRead2, num2);
			}
		}

		while (file1==true)
		{
			_InputNum(fWrite, num1);         //���ļ���д��һ����
			file1 = _GetNum(fRead1, num1);
		}

		while(file2==true)
		{
			_InputNum(fWrite, num2);         //���ļ���д��һ����
			file2 = _GetNum(fRead2, num2);
		}
	}

protected:
	bool _GetNum(FILE *fRead,int& num)  //��ȡһ������,��������ͨ��num����
	{
		int ch = 0;
		string line;
		while ((ch = getc(fRead)) != EOF&&ch != '\n')
		{
			line += ch;
		}
		if (ch == EOF)
			return false;
		else
		{
			num = atoi(line.c_str());
			return true;
		}
	}

	bool _GetLine(FILE* fRead,string& line)   //��ȡһ����������������ת�����ַ�����line����
	{
		int ch = 0;
		while ((ch = getc(fRead)) != EOF&&ch!= '\n')
		{
			line += ch;
		}
		if (ch == EOF)
			return false;
		else
			return true;
	}

	void _InputNum(FILE *fWrite,int num)     //���ļ���дһ��������ת�����ַ���д��
	{
		char buf[120] = { 0 };
		string line;
		line = _itoa(num, buf, 10);
		line += '\n';
		fputs(line.c_str(), fWrite);
	}

private:
	vector<string> _SmallFileName;     //���С�ļ���������
	char* _bigfile;               //��¼Ҫ������ļ���
	size_t _limit;                //��¼С�ļ���������ݸ���
};




void TestBigDataSort()
{
	BigDataSort file("file.txt",10,10000);
	file.Sort();
}