#define  _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<string>
using namespace std;
#include"fileCompress.h"

void test()
{
	FileCompress file("originfile.txt");
	const char* CompressFile=file.Compress("originfile.txt");
	file.UnCompress(CompressFile);
	//string str("aaaaaaaaabbbcc");
	//string::iterator it = str.begin();
	//while (it<str.end())
	//{
	//	cout << *it << endl;
	//	it++;
	//}
}

int main()
{
	test();
	system("pause");
	return 0;
}