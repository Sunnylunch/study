//firstly

void SelectSort(int *arr , int len)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int tmp = 0;
	for (i = 0; i < len-1; i++)
	{
		k = i;
		for (j = i + 1; j < len; j++)
		{
			if (arr[j] < arr[k])   //寻找无序区最小的元素的下标
			{
				k = j;
			}
		}
		if (k != i)              //如果寻找的元素下标不等于有序区最后一个元素下标则交换
		{
			tmp = arr[i];
			arr[i] = arr[k];
			arr[k] = tmp;
		}
	}
}



//second
void SelectSort(int *arr, int len)
{
	int left = 0;
	int right = 0;
	int j = 0;
	int tmp = 0;
	int max = 0;
	int min = 0;
	for (left=0,right=len-1 ; left<right ;  right--,left++)
	{
		min =left;
		max = left;
		for (j = left + 1; j <=right; j++)
		{
			if (arr[j] < arr[min])   //寻找无序区最小的元素的下标
			{
				min = j;
			}
			if (arr[j]> arr[max])   //寻找无序区最大的元素的下标
			{
				max= j;
			}
		}
		if (min!= left)              //如果寻找的最小元素下标不等于有序区最后一个元素下标则交换
		{
			tmp = arr[left];
			arr[left] = arr[min];
			arr[min] = tmp;
		}
		if (max == left)        //如果最大元素的下标是有序区最后一个元素的下标，此时min存放的最大值
		{
			max = min;           //将max置为最大值
		}
		if (max !=right)   //如果max没在无序区右边，则将max对应的值放在右边
		{
			tmp = arr[right];
			arr[right] = arr[max];
			arr[max] = tmp;
		}
	}
}