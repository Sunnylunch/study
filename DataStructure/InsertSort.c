
//firstly
void InsertSort(int *arr , int len)
{
	int i = 0;
	int j = 0;
	int tmp = 0;
	for (i = 1; i < len; i++)
	{
		tmp = arr[i];
		for (j = i; j>0&&arr[j-1]>tmp; j--)       //���������ҵ�һ����ȷ��λ��
		{
			arr[j] = arr[j - 1];                  //����ǰ��¼����
		}
		arr[j] = tmp;                             //��tmp���뵽�ҵ���λ��
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
		mid = (left&right) + ((left^right) >> 1);      //��ȡƽ��ֵ�����Է�ֹ���
		while(left<=right)                             //����BinarySearch������������һ�����ʵ�λ��
		{
			if (arr[mid]>tmp)                           //��������£�tmpҪ�����λ�ÿ϶�С�ڵ���mid
			{
				right = mid-1;
				k = mid;
			}
			else if (arr[mid] <=tmp)          //��������£�tmpҪ�����λ�ÿ϶�����mid
			{
				left = mid+1;
				k = mid+1;                  
			}
			mid = (left&right) + ((left^right) >> 1);
		}
		for (j = i; j>k; j--)       //�����λ����������Ԫ�غ���
		{
			arr[j] = arr[j - 1];
		}
		arr[k] = tmp;               //��tmp�ŵ����λ��
	}
}