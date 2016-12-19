#include<iostream>
using namespace std;
#include<cassert>


//��һ�����飬���ո������±�������򣬽�ʹ�����������ķ�ʽ��Ҫ���ܶ������������
//���� ԭ���� A B C D E,�ָ�����λ��Ϊ3 0 1 4 2 �����Ľ����D A B E C 

//template<typename T>
//void SwapSort(T* pArr,int* pPos,int n)
//{
//	int count = 0;
//	int flag = 0;    //��¼�ʼ��ʱ��ӵ�λ��
//	char tmp;
//	int i = 0;    
//	while (i<n)
//	{
//		while (i == pPos[i])
//		{
//			i++;
//		}
//		if (i == n)          //��ʾ����λ�ö��Ѿ���ȷ������
//			break;
//
//		tmp = pArr[i];      //��i���λ����һ����
//		flag = i;
//
//		while (1)
//		{
//			count++;
//			swap(pArr[i], pArr[pPos[i]]);
//			int j = pPos[i];        //�Ȱ�pPos[i]��λ�ü�¼����
//			pPos[i] = i;            //��ΪpArr[i]�Ѿ���ȷ���룬���Ը���pPos
//			i = j;
//			if (flag== pPos[i])      //�������¿�Ҫ�����tmp
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