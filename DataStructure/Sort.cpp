#include<iostream>
#include<cassert>
#include<stack>
using namespace std;

//void PrintArray(int *a,int len)
//{
//	for (int i = 0; i < len; i++)
//	{
//		cout << a[i] << " ";
//	}
//	cout << endl;
//}
//
////����������Ϊ��
////InsertSort
void InsertSort(int *a,int len)
{
	assert(a);
	int index = 1;                    //����������
	while (index < len)
	{
		int pos = index - 1;
		int tmp = a[index];
		while (pos >= 0 && a[pos]>tmp)
		{
			a[pos + 1] = a[pos];
			pos--;
		}
		a[pos + 1] = tmp;
		index++;
	}
}
//
//
////SelectSort
//void SelectSort(int *a,int len)
//{
//	assert(a);
//	int index =len-1;          //����������
//	while (index >= 1)
//	{
//		int pos = len - 1 - index;
//		int i = pos + 1;
//		int min = pos;
//		while (i<len)
//		{
//			if (a[min]>a[i])
//			{
//				min = i;
//			}
//			i++;
//		}
//		if (min != pos)                      //����������С��ֵ�������������ĵ�һ��λ��
//		{
//			a[pos] = a[pos] ^ a[min];
//			a[min] = a[pos] ^ a[min];
//			a[pos] = a[pos] ^ a[min];
//		}
//		index--;
//	}
//}


//void SelectSort(int *a,int len)        //ѡ�������Ż���ÿ��ѡ��һ������ֵ��һ����С��ֵ
//{
//	assert(a);
//	int i = 0;
//	int j = len-1;
//	while (i<j)
//	{
//		int left = i;
//		int right =j;
//		int max = left;
//		int min = left;
//		while (left <= right)
//		{
//			if (a[left] < a[min])
//			{
//				min = left;
//			}
//			if (a[left]>a[max])
//			{
//				max = left;
//			}
//			left++;
//		}
//		swap(a[min],a[i]);
//		if (max==i)          //�п������ֵ����i���λ�ã���ʱ������max��������
//		{
//			max =min;
//		}
//		swap(a[max],a[j]);
//		i++;
//		j--;
//	}
//}



////ShellSort
//void ShellSort(int *a, int len)     //��������ı��Σ�ͨ��Ԥ����ʹ��Ԫ�ش���������ͨ����������ʹ��������������
//{
//	int gap = len;           //����
//	while (gap > 1)
//	{
//		gap = gap / 3 + 1;              //����Ҫ��С��ֱ������Ϊ1
//		for (int index = gap; index<len;++index)
//		{
//			int pos = index-gap;          //�����������һ��Ԫ��
//			int tmp = a[index];
//			while (pos > 0 && a[pos] > tmp)
//			{
//				a[pos + gap] = a[pos];
//				pos -= gap;
//			}
//			a[pos + gap] = tmp;
//		}
//	}
//}

//
//void AdjustDown(int*& a,int index,int len)           //�µ��㷨
//{
//	if (a == NULL)
//		return;
//	int parent = index;               //parent��ʾ���׵��±�
//	for (int maxchild=parent*2;maxchild< len;maxchild=2*parent)
//	{
//		if ((maxchild + 1 < len) && a[maxchild] < a[maxchild + 1])   //�ҳ�parent�ĺ���������
//			maxchild++;
//		if (a[parent] < a[maxchild])
//		{
//			swap(a[parent], a[maxchild]);
//			parent = maxchild;
//		}
//		else
//			return;
//	}
//}
//
//void HeapSort(int* a,int len)
//{
//	int last = len/ 2;
//	for (int i = last; i >=0; i--)
//	{
//		AdjustDown(a,i,len);
//	}
//	last = len - 1;
//	while (last>0)
//	{
//		swap(a[0], a[last]);
//		AdjustDown(a, 0, last);
//		last--;
//	}
//}
//
//



//����1������˫ָ�뽻����

//QuickSort���������һ��Ԫ����Ϊ��׼Ԫ�أ�����߿�ʼ�Ҵ��ڻ�׼Ԫ�ص�ֵ�����ұ���С�ڻ�׼Ԫ�ص�ֵ
//int PartSort(int *a,int begin,int end)
//{
//	int left = begin;
//	int right = end;
//	while (left < right)
//	{
//		while (left < right&&a[left]<=a[end])
//		{
//			left++;
//		}
//		while (left < right&&a[right] >=a[end])
//		{
//			right--;
//		}
//		if (left<right)
//			swap(a[left],a[right]);
//	}
//	swap(a[left], a[end]);
//	return left;
//}
//


//����2���ڶ�������������˫ָ��[begin,end]

//void QuickSort(int *a,int begin,int end)
//{
//	assert(a);
//	int div=PartSort(a,begin,end);
//	if (div-1>begin)                 //��������Ԫ�ظ�������һ����ʱ���Ҫ�ڽ��л�������
//	    QuickSort(a,begin,div-1);
//	if (div+1<end)
//		QuickSort(a,div+1,end);
//}
//
//
//int PartSort(int *a,int begin,int end)
//{
//	int left = begin;
//	int right = end;
//	int key = a[end];
//	int blank = end;
//	while (left<right)
//	{
//		if (blank == right)        //����߿�ʼ��һ���Ȼ�׼�����ֵ
//		{
//			while (left<right&&a[left]<=key)
//			{
//				left++;
//			}
//			a[blank] = a[left];
//			blank = left;
//		}
//		else if (blank == left)    //���ұ߿�ʼ��һ���Ȼ�׼ֵС��ֵ
//		{
//			while (left<right&&a[right]>=key)
//			{
//				right--;
//			}
//			a[blank] = a[right];
//			blank = right;
//		}
//	}
//	a[blank] = key;
//	return blank;
//}
//
//void QuickSort(int *a,int begin,int end)
//{
//	assert(a);
//	if (begin < end)
//	{
//		int div=PartSort(a,begin,end);
//		QuickSort(a,begin,div-1);
//		QuickSort(a,div+1,end);
//	}
//}


//����ȡ�з������ÿ��ѡ��Ļ�׼�����ǽӽ����������߽ӽ���С������ʱ�򣬿��ŵ�Ч�ʾͻ���O(N*N)����Ϊ�������ֵ�
//��������𲻵������ˣ�����ÿ��ѡ��һ���ӽ���������С�ĸ����Ǻܵ͵ģ���������������Ѿ�������������
//������O(N*N)������������ʱ��ѡ���׼����ʱ�������������ȡ�з������������ʱ��O(N*N)���㷨
//int GetMid(int *a,int left,int right)
//{
//	int mid = ((left^right)>>1)+ (left&right);  //��ƽ��ֵ
//	if (a[left] < a[mid])
//	{
//		if (a[mid] < a[right])
//			return mid;
//		else if (a[left] < a[right])
//			return right;
//		else
//			return left;
//	}
//	else
//	{
//		if (a[left] < a[right])
//			return left;
//		else if (a[mid]>a[right])
//			return mid;
//		else
//			return right;
//	}
//}
//
//int PartSort(int *a,int begin,int end)
//{
//	int key = GetMid(a,begin,end);
//	swap(a[key],a[end]);
//	int left = begin;
//	int right = end;
//	while (left < right)
//	{
//		while (left < right&&a[left] <=a[end])
//			left++;
//		while (left < right&&a[right] >=a[end])
//			right--;
//		if (left < right)
//			swap(a[left],a[right]);
//	}
//	swap(a[left],a[end]);
//	return left;
//}
//
//void QuickSort(int *a,int begin,int end)
//{
//	assert(a);
//	if (begin < end)
//	{
//		int div = PartSort(a,begin,end);
//		QuickSort(a,begin,div-1);
//		QuickSort(a,div+1,end);
//	}
//}



//�������ֵС��13����ʱ���ֱ����ֱ�Ӳ��뷨�����������������Ч��
//int GetMid(int *a, int left, int right)
//{
//	int mid = ((left^right) >> 1) + (left&right);  //��ƽ��ֵ
//	if (a[left] < a[mid])
//	{
//		if (a[mid] < a[right])
//			return mid;
//		else if (a[left] < a[right])
//			return right;
//		else
//			return left;
//	}
//	else
//	{
//		if (a[left] < a[right])
//			return left;
//		else if (a[mid]>a[right])
//			return mid;
//		else
//			return right;
//	}
//}
//
//int Partsort(int *a, int begin, int end)
//{
//	int key = GetMid(a, begin, end);
//	swap(a[key], a[end]);
//	int left = begin;
//	int right = end;
//	while (left < right)
//	{
//		while (left < right&&a[left] <= a[end])
//			left++;
//		while (left < right&&a[right] >= a[end])
//			right--;
//		if (left < right)
//			swap(a[left], a[right]);
//	}
//	swap(a[left], a[end]);
//	return left;
//}
//
//void QuickSort(int *a, int begin, int end)
//{
//	assert(a); 
//	if (begin<end)                   //��������ֵ�ĸ�������13���ǲſ���
//	{
//		if (end - begin>13)
//		{
//			int div = Partsort(a, begin, end);
//			QuickSort(a, begin, div-1);
//			QuickSort(a, div+1, end);
//		}
//		else                   //������ֵ�ĸ���С��13��ʱ����ֱ�Ӳ�������
//		{
//			InsertSort(a+begin, end - begin+1);
//		}
//	}
//}
//int GetMid(int *a, int left, int right)
//{
//	int mid = ((left^right) >> 1) + (left&right);  //��ƽ��ֵ
//	if (a[left] < a[mid])
//	{
//		if (a[mid] < a[right])
//			return mid;
//		else if (a[left] < a[right])
//			return right;
//		else
//			return left;
//	}
//	else
//	{
//		if (a[left] < a[right])
//			return left;
//		else if (a[mid]>a[right])
//			return mid;
//		else
//			return right;
//	}
//}
//
//int PartSort(int* a,int begin,int end)
//{
//	int key = GetMid(a,begin,end);
//	swap(a[key],a[end]);
//	int prev = begin - 1;
//	int cur = begin;
//	while (cur<end)
//	{
//		if (a[cur] < a[end])
//		{
//			prev++;
//			if (prev != cur)
//				swap(a[prev], a[cur]);
//		}
//		cur++;
//	}
//	prev++;
//	swap(a[prev], a[end]);
//	return prev;
//}
//
////����ǰ��ָ�������ٵ�ʵ�ֻ�������������
//void QuickSort(int *a,int begin,int end)
//{
//	assert(a);
//	if (begin < end)
//	{
//		if (end - begin>13)
//		{
//			int div = PartSort(a,begin,end);
//			QuickSort(a,begin,div-1);
//			QuickSort(a,div+1,end);
//		}
//		else
//		{
//			InsertSort(a+begin,end-begin+1);
//		}
//	}
//}

//
//int GetMid(int *a, int left, int right)
//{
//	int mid = ((left^right) >> 1) + (left&right);  //��ƽ��ֵ
//	if (a[left] < a[mid])
//	{
//		if (a[mid] < a[right])
//			return mid;
//		else if (a[left] < a[right])
//			return right;
//		else
//			return left;
//	}
//	else
//	{
//		if (a[left] < a[right])
//			return left;
//		else if (a[mid]>a[right])
//			return mid;
//		else
//			return right;
//	}
//}
//
//int PartSort(int *a,int begin,int end)
//{
//	int key = GetMid(a,begin,end);
//	swap(a[key],a[end]);
//	int prev = begin - 1;
//	int cur = begin;
//	while (cur < end)
//	{
//		if (a[cur] < a[end])              //���a[cur]С�ڻ�׼ֵ����prev++
//		{
//			prev++;
//			if (prev != cur)              //���prev������cur����˵��a[prev]���ڻ�׼ֵ
//				swap(a[prev],a[cur]);
//		}
//		cur++;
//	}
//	prev++;
//	swap(a[prev],a[end]);
//	return prev;
//}
////
//////����ջʵ�ַǵݹ��������
//void QuickSort(int *a,int begin,int end)
//{
//	assert(a);
//	stack<int> s;
//	s.push(end);
//	s.push(begin);
//
//	while (!s.empty())
//	{
//		int left = s.top();       //��ȡ��߽�
//		s.pop();
//		int right =s.top();         //��ȡ�ұ߽�
//		s.pop();
//		int div = PartSort(a,left,right); 
//		if (div-1>left)                      //ֻ���������ֵ����1����ʱ��ż�������
//		{
//			s.push(div - 1);
//			s.push(left);
//		}
//
//		if (right>div + 1)                     //ֻ���������ֵ����1����ʱ��ż�������
//		{
//			s.push(right);
//			s.push(div + 1);
//		}
//	}
//}

//
//void _MergeSort(int *a,int begin,int end,int *tmp)
//{
//	int mid = ((begin^end) >> 1) + (begin&end);
//	if (mid > begin)
//		_MergeSort(a,begin,mid,tmp);
//	if (mid + 1 < end)
//		_MergeSort(a,mid+1,end,tmp);
//
//	int begin1 = begin;
//	int end1 = mid;
//	int begin2 = mid + 1;
//	int end2 = end;
//	int index = begin;
//
//	while(begin1<=end1&&begin2<=end2)
//	{
//		if (a[begin1] < a[begin2])
//		{
//			tmp[index++] = a[begin1++];
//		}
//		else
//		{
//			tmp[index++] = a[begin2++];
//		}
//	}
//
//	while(begin1 <= end1)
//	{
//		tmp[index++] = a[begin1++];
//	}
//
//	while (begin2 <= end2)
//	{
//		tmp[index++] = a[begin2++];
//	}
//
//	while (begin <= end)
//	{
//		a[begin] = tmp[begin++];
//	}
//}
//
//void MergeSort(int *a,int begin,int end)
//{
//	assert(a);
//	int *tmp = new int[end-begin+1];
//	_MergeSort(a,begin,end,tmp);
//	delete tmp;
//}

void _MergeSort(int *a,int begin,int end,int* tmp)
{
	int mid = ((begin^end) >> 1) + (begin&end);
	if (begin<mid)
	{
		if (mid - begin>13)
		{
			_MergeSort(a, begin, mid, tmp);
		}
		else
		{
			InsertSort(a+begin, end - begin + 1);
		}
	}

	if (mid + 1 < end)
	{
		if (end - mid - 1 > 13)
		{
			_MergeSort(a,mid+1,end,tmp);
		}
		else
		{
			InsertSort(a+mid+1,end-mid);
		}
	}

	int begin1 = begin;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = end;
	int index = begin;

	while (begin1 <= end1&&begin2 <= end2)
	{
		if (a[begin1] < a[begin2])
			tmp[index++] = a[begin1++];
		else
			tmp[index++] = a[begin2++];
	}

	while (begin1 <= end1)
		tmp[index++] = a[begin1++];

	while (begin2 <=end2)
		tmp[index++] = a[begin2++];

	while(begin<=end)
	{
		a[begin] = tmp[begin++];
	}
}

void MergeSort(int* a,int begin,int end)
{
	assert(a);
	int *tmp = new int[end-begin+1];
	_MergeSort(a,begin,end,tmp);
	delete tmp;
}

void test()
{
	//int a[] = { -3, 9, -2, 7,1, 4, 7, 2, 10 };
	//int a[] = {10,5,7,8,5,3,1,5,2,0};
	int a[100];
	for (int i = 0; i <100; i++)
	{
		a[i] = 99-i;
	}
	int sz = sizeof(a) / sizeof(a[0]);
	//InsertSort(a,sz);
	////SelectSort(a,sz);
	//PrintArray(a, sz);

	//ShellSort(a2,sz);
	//PrintArray(a,sz);
   	//HeapSort(a2, sz);
	//QuickSort(a,0,sz-1);
	//SelectSort(a,sz);
	//QuickSort(a,0,sz-1);
	MergeSort(a,0,sz-1);
 }


int main()
{
	test();
	system("pause");
	return 0;
}

