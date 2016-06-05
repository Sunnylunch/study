
//firstly
void BubbleSort(int *arr, int len)
{
	assert(arr);
	int i = 0;
	int j = 0;
	int tmp = 0;
	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < len -i- 1; j++)       //ÿ����һ�ˣ����Ȼ������һ���Ѿ����򣬿��Լ���ѭ����С����ķ�Χ
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
		flag = 1;                              //flag��ʼʱΪ1
		for (j = 0; j < len - i - 1; j++)       //ÿ����һ�ˣ����Ȼ������һ���Ѿ����򣬿�����С����ķ�Χ
		{
			if (arr[j]>arr[j + 1])             //ֻҪҪ�������ݣ���flag�ͻᱻ�޸�
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 0;                    //ֻҪ��������δ��ȫ������һ�����޸�flagΪ0
			}
		}
		if (flag)                             //�������һ�ˣ������Ѿ������򲻽���if,flagû���޸�
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
	int m = 0;                  //������¼���һ�ν�����λ��
	int k = len-1;
	for (i = 0; i < len - 1; i++)
	{
		m = 0;
		flag = 1;
		for (j = 0; j < k; j++)       //�������ķ�Χֻ�ӵ�һ��Ԫ�أ�����һ�����һ�ν�����λ��k
		{
			if (arr[j]>arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 0;                    //ֻҪ��������δ��ȫ������һ�����޸�flagΪ0
				m = j;
			}
		}
		if (flag)                             //�������һ�ˣ������Ѿ������򲻽���if,flagû���޸�
		{
			break;
		}
		k = m;                             //��k�ó����һ�ν�����λ��
	}
}


//fourthly
void BubbleSort(int *arr, int len)
{
	assert(arr);
	int i = 0;
	int j = 0;
	int flag = 0;
	int m = 0;       //��¼���һ�ν�����λ��
	int n = 0;
	int k = len - 1;
	for (i = 0; i < len - 1; i++)
	{
		m = 0;
		flag = 1;
		//����ɨ�������ֵ
		for (j = n; j < k; j++)       //�������ķ�Χֻ�ӵ�һ��Ԫ�أ�����һ�����һ�ν�����λ��k
		{
			if (arr[j]>arr[j + 1])
			{

				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = 0;                    //ֻҪ��������δ��ȫ������һ�����޸�flagΪ0
				m = j;
			}
		}
		k = m;
		if (flag)                    //�������һ�ˣ������Ѿ������򲻽���if,flagû���޸�
		{
			break;
		}
		//����ɨ������Сֵ
		for (j = k; j>n; j--)       //�������ķ�Χֻ�ӵ�һ��Ԫ�أ�����һ�����һ�ν�����λ��k
		{
			if (arr[j]<arr[j - 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = tmp;
				flag = 0;                    //ֻҪ��������δ��ȫ������һ�����޸�flagΪ0
			}
		}
		n++;
		if (flag)                    //�������һ�ˣ������Ѿ������򲻽���if,flagû���޸�
		{
			break;
		}                           //��k�ó����һ�ν�����λ��
	}
}