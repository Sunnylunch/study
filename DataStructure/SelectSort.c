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
			if (arr[j] < arr[k])   //Ѱ����������С��Ԫ�ص��±�
			{
				k = j;
			}
		}
		if (k != i)              //���Ѱ�ҵ�Ԫ���±겻�������������һ��Ԫ���±��򽻻�
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
			if (arr[j] < arr[min])   //Ѱ����������С��Ԫ�ص��±�
			{
				min = j;
			}
			if (arr[j]> arr[max])   //Ѱ������������Ԫ�ص��±�
			{
				max= j;
			}
		}
		if (min!= left)              //���Ѱ�ҵ���СԪ���±겻�������������һ��Ԫ���±��򽻻�
		{
			tmp = arr[left];
			arr[left] = arr[min];
			arr[min] = tmp;
		}
		if (max == left)        //������Ԫ�ص��±������������һ��Ԫ�ص��±꣬��ʱmin��ŵ����ֵ
		{
			max = min;           //��max��Ϊ���ֵ
		}
		if (max !=right)   //���maxû���������ұߣ���max��Ӧ��ֵ�����ұ�
		{
			tmp = arr[right];
			arr[right] = arr[max];
			arr[max] = tmp;
		}
	}
}