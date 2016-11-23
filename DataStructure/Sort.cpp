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
////以下以升序为例
////InsertSort
void InsertSort(int *a,int len)
{
	assert(a);
	int index = 1;                    //有序区长度
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
//	int index =len-1;          //无序区长度
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
//		if (min != pos)                      //将无序区最小的值交换到无序区的第一个位置
//		{
//			a[pos] = a[pos] ^ a[min];
//			a[min] = a[pos] ^ a[min];
//			a[pos] = a[pos] ^ a[min];
//		}
//		index--;
//	}
//}


//void SelectSort(int *a,int len)        //选择排序优化，每次选择一个最大的值和一个最小的值
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
//		if (max==i)          //有可能最大值就在i这个位置，这时候必须对max做出处理
//		{
//			max =min;
//		}
//		swap(a[max],a[j]);
//		i++;
//		j--;
//	}
//}



////ShellSort
//void ShellSort(int *a, int len)     //插入排序的变形，通过预排序使得元素大致有序，再通过插入排序使得数组整体有序
//{
//	int gap = len;           //增量
//	while (gap > 1)
//	{
//		gap = gap / 3 + 1;              //增量要减小，直到增减为1
//		for (int index = gap; index<len;++index)
//		{
//			int pos = index-gap;          //有序区的最后一个元素
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
//void AdjustDown(int*& a,int index,int len)           //下调算法
//{
//	if (a == NULL)
//		return;
//	int parent = index;               //parent表示父亲的下标
//	for (int maxchild=parent*2;maxchild< len;maxchild=2*parent)
//	{
//		if ((maxchild + 1 < len) && a[maxchild] < a[maxchild + 1])   //找出parent的孩子中最大的
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



//方法1：左右双指针交换法

//QuickSort——以最后一个元素作为基准元素，从左边开始找大于基准元素的值，从右边找小于基准元素的值
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


//方法2：挖洞法，利用左右双指针[begin,end]

//void QuickSort(int *a,int begin,int end)
//{
//	assert(a);
//	int div=PartSort(a,begin,end);
//	if (div-1>begin)                 //这个区间的元素个数大于一个的时候就要在进行划分排序
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
//		if (blank == right)        //从左边开始找一个比基准数大的值
//		{
//			while (left<right&&a[left]<=key)
//			{
//				left++;
//			}
//			a[blank] = a[left];
//			blank = left;
//		}
//		else if (blank == left)    //从右边开始找一个比基准值小的值
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


//三数取中法：如果每次选择的基准数都是接近最大的数或者接近最小的数的时候，快排的效率就会变成O(N*N)，因为这样划分的
//的区间就起不到作用了，但是每次选择一个接近最大或者最小的概率是很低的，但是针对于数组已经有序的情况快排
//依旧是O(N*N)，所以我们这时候选择基准数的时候可以利用三数取中法来避免有序的时候O(N*N)的算法
//int GetMid(int *a,int left,int right)
//{
//	int mid = ((left^right)>>1)+ (left&right);  //求平均值
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



//当区间的值小于13个的时候就直接用直接插入法进行排序，这样能提高效率
//int GetMid(int *a, int left, int right)
//{
//	int mid = ((left^right) >> 1) + (left&right);  //求平均值
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
//	if (begin<end)                   //当区间中值的个数大于13个是才快排
//	{
//		if (end - begin>13)
//		{
//			int div = Partsort(a, begin, end);
//			QuickSort(a, begin, div-1);
//			QuickSort(a, div+1, end);
//		}
//		else                   //区间中值的个数小于13个时进行直接插入排序
//		{
//			InsertSort(a+begin, end - begin+1);
//		}
//	}
//}
//int GetMid(int *a, int left, int right)
//{
//	int mid = ((left^right) >> 1) + (left&right);  //求平均值
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
////利用前后指针来快速的实现划分左右子区间
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
//	int mid = ((left^right) >> 1) + (left&right);  //求平均值
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
//		if (a[cur] < a[end])              //如果a[cur]小于基准值，则prev++
//		{
//			prev++;
//			if (prev != cur)              //如果prev不等于cur，则说明a[prev]大于基准值
//				swap(a[prev],a[cur]);
//		}
//		cur++;
//	}
//	prev++;
//	swap(a[prev],a[end]);
//	return prev;
//}
////
//////利用栈实现非递归快速排序
//void QuickSort(int *a,int begin,int end)
//{
//	assert(a);
//	stack<int> s;
//	s.push(end);
//	s.push(begin);
//
//	while (!s.empty())
//	{
//		int left = s.top();       //先取左边界
//		s.pop();
//		int right =s.top();         //再取右边界
//		s.pop();
//		int div = PartSort(a,left,right); 
//		if (div-1>left)                      //只有子区间的值大于1个的时候才继续划分
//		{
//			s.push(div - 1);
//			s.push(left);
//		}
//
//		if (right>div + 1)                     //只有子区间的值大于1个的时候才继续划分
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

