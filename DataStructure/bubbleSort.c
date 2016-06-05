
//firstly
void BubbleSort(int *arr, int len)
{
	assert(arr);
	int i = 0;
	int j = 0;
	int tmp = 0;
	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < len -i- 1; j++)       //每排序一趟，则必然后面有一个已经有序，可以减少循环缩小排序的范围
		{
			if (arr[j]>arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}


//second
void BubbleSort(int *arr, int len)
{
	assert(arr);
	int i = 0;
	int j = 0;
	int flag = 0;
	int tmp = 0;
	for (i = 0; i < len - 1; i++)
	{
		flag = 1;                              //flag初始时为1
		for (j = 0; j < len - i - 1; j++)       //每排序一趟，则必然后面有一个已经有序，可以缩小排序的范围
		{
			if (arr[j]>arr[j + 1])             //只要要交换数据，则flag就会被修改
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 0;                    //只要这组数还未完全有序，则一定会修改flag为0
			}
		}
		if (flag)                             //如果排序一趟，发现已经有序，则不进入if,flag没被修改
		{
			break;
		}
	}
}


//thirdly
void BubbleSort(int *arr, int len)
{
	assert(arr);
	int i = 0;
	int j = 0;
	int flag = 0;
	int tmp = 0;
	int m = 0;                  //用来记录最后一次交换的位置
	int k = len-1;
	for (i = 0; i < len - 1; i++)
	{
		m = 0;
		flag = 1;
		for (j = 0; j < k; j++)       //无序区的范围只从第一个元素，到上一趟最后一次交换的位置k
		{
			if (arr[j]>arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 0;                    //只要这组数还未完全有序，则一定会修改flag为0
				m = j;
			}
		}
		if (flag)                             //如果排序一趟，发现已经有序，则不进入if,flag没被修改
		{
			break;
		}
		k = m;                             //将k置成最后一次交换的位置
	}
}


//fourthly
void BubbleSort(int *arr, int len)
{
	assert(arr);
	int i = 0;
	int j = 0;
	int flag = 0;
	int m = 0;       //记录最后一次交换的位置
	int n = 0;
	int k = len - 1;
	for (i = 0; i < len - 1; i++)
	{
		m = 0;
		flag = 1;
		//正序扫描找最大值
		for (j = n; j < k; j++)       //无序区的范围只从第一个元素，到上一趟最后一次交换的位置k
		{
			if (arr[j]>arr[j + 1])
			{

				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 0;                    //只要这组数还未完全有序，则一定会修改flag为0
				m = j;
			}
		}
		k = m;
		if (flag)                    //如果排序一趟，发现已经有序，则不进入if,flag没被修改
		{
			break;
		}
		//反序扫描找最小值
		for (j = k; j>n; j--)       //无序区的范围只从第一个元素，到上一趟最后一次交换的位置k
		{
			if (arr[j]<arr[j - 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = tmp;
				flag = 0;                    //只要这组数还未完全有序，则一定会修改flag为0
			}
		}
		n++;
		if (flag)                    //如果排序一趟，发现已经有序，则不进入if,flag没被修改
		{
			break;
		}                           //将k置成最后一次交换的位置
	}
}