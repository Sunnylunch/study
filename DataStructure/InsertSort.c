
//firstly
void InsertSort(int *arr , int len)
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	for (i = 1; i < len; i++)
	{
		tmp = arr[i];
		for (j = i; j>0&&arr[j-1]>tmp; j--)       //在有序区找到一个正确的位置
		{
			arr[j] = arr[j - 1];                  //将当前记录后移
		}
		arr[j] = tmp;                             //将tmp插入到找到的位置
	}
}

//second
void InsertSort(int *arr, int len)
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	int mid = 0;
	int k = 0;                                      
	for (i = 1; i < len; i++)
	{
		tmp = arr[i];
		int left = 0;
		int right = i - 1;
		mid = (left&right) + ((left^right) >> 1);      //求取平均值，可以防止溢出
		while(left<=right)                             //利用BinarySearch在有序区查找一个合适的位置
		{
			if (arr[mid]>tmp)                           //这种情况下，tmp要插入的位置肯定小于等于mid
			{
				right = mid-1;
				k = mid;
			}
			else if (arr[mid] <=tmp)          //这种情况下，tmp要插入的位置肯定大于mid
			{
				left = mid+1;
				k = mid+1;                  
			}
			mid = (left&right) + ((left^right) >> 1);
		}
		for (j = i; j>k; j--)       //将这个位置向后的所有元素后移
		{
			arr[j] = arr[j - 1];
		}
		arr[k] = tmp;               //将tmp放到这个位置
	}
}