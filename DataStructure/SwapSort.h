#include<iostream>
using namespace std;
#include<cassert>


//对一个数组，按照给定的下标进行排序，仅使用两两交换的方式，要求不能对数组进行扩容
//例： 原数组 A B C D E,现给定新位置为3 0 1 4 2 排序后的结果是D A B E C 

//template<typename T>
//void SwapSort(T* pArr,int* pPos,int n)
//{
//	int count = 0;
//	int flag = 0;    //记录最开始的时候坑的位置
//	char tmp;
//	int i = 0;    
//	while (i<n)
//	{
//		while (i == pPos[i])
//		{
//			i++;
//		}
//		if (i == n)          //表示所有位置都已经正确填入了
//			break;
//
//		tmp = pArr[i];      //在i这个位置挖一个洞
//		flag = i;
//
//		while (1)
//		{
//			count++;
//			swap(pArr[i], pArr[pPos[i]]);
//			int j = pPos[i];        //先把pPos[i]的位置记录下来
//			pPos[i] = i;            //因为pArr[i]已经正确填入，所以更新pPos
//			i = j;
//			if (flag== pPos[i])      //如果这个新坑要填的是tmp
//			{
//				pArr[i] = tmp;
//				pPos[i] = i;
//				i = flag + 1;
//				break;
//			}
//		}
//	}
//	cout << count << endl;
//}


template<typename T>
void SwapSort(T* pArr, int* pPos, int n)
{
	assert(pArr);
	assert(pPos);
	int count = 0;
	for (int i =0 ;i < n- 1;++i)
	{
		if (i < pPos[i])
		{
			swap(pArr[i], pArr[pPos[i]]);
			count++;
		}
		else if (i>pPos[i])
		{
			if (i!=pPos[pPos[i]])
			{
				swap(pArr[i], pArr[pPos[pPos[i]]]);
				pPos[i] = pPos[pPos[i]];
				count++;
			}
		}
	}
	cout << count << endl;
}



//TEST

void test()
{
	char pArr[] = { 'A', 'B', 'C', 'D', 'E' };
	int sz = sizeof(pArr) / sizeof(pArr[0]);
	int pPos[] = {0,2,1,3,4};
	SwapSort(pArr,pPos,sz);
}

int main()
{
	test();
	system("pause");
	return 0;
}