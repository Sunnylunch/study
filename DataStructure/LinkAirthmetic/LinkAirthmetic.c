
void BubbleSort(pLinkList list)
{
	assert(list);
	pLinkNode cur = list->pHead;
	pLinkNode tail = NULL;
	int flag = 0;
	DataType tmp = 0;
	if (NULL == list->pHead || NULL == list->pHead->next)
	{
		return;
	}
	while (cur->next != tail)
	{
		flag = 1;
		while (cur->next != tail)
		{
			if (cur->data > cur->next->data)
			{
				tmp = cur->data;
				cur->data = cur->next->data;
				cur->next->data = tmp;
				flag = 0;
			}
			cur = cur->next;
		}
		if (flag)
		{
			break;
		}
		tail = cur;
		cur = list->pHead;
	}
}


void SelectSort(pLinkList list)                  //ѡ������
{
	assert(list);
	if (NULL == list->pHead || NULL == list->pHead->next)  //����ǿ��������ֻ��һ�������ֱ�ӽ���
	{
		return;
	}
	pLinkNode cur = list->pHead;
	pLinkNode p = NULL;
	pLinkNode min = NULL;
	while (cur != NULL)
	{
		p = cur->next;               //pָ���������ڶ���Ԫ��
		min = cur;                    //minָ����������һ��Ԫ��
		while (p != NULL)
		{
			if (min->data > p->data)
			{
				min = p;             //min��¼��С��data�ĵ�ַ
			}
			p = p->next;
		}
		if (min != cur)              //��min��ָ���data����������һ��Ԫ�ؽ��н���
		{
			DataType tmp = cur->data;
			cur->data = min->data;
			min->data = tmp;
		}
		cur = cur->next;              //��������һ����������һ
	}
}

void EraseNotTail(pLinkNode pos)                 //ɾ����β���
{
	assert(pos->next);
	pLinkNode cur = pos->next;
	pos->data = cur->data;
	pos->next = cur->next;
	free(cur);
	cur = NULL;
}

void Reverselist(pLinkList list)                   //��ת����
{
	assert(list);
	if (NULL == list->pHead || NULL == list->pHead->next)
	{
		return;
	}
	pLinkNode newHead = NULL;           //ָ���������ͷ
	pLinkNode tmp = NULL;
	pLinkNode cur = list->pHead;
	while (cur != NULL)
	{
		tmp = cur->next;                 //tmp����cur����һ�����
		cur->next = newHead;             //ָ���������ͷ
		newHead = cur;                   //�����ͷָ���ƶ�
		cur = tmp;                       //curָ����һ�����
	}
	list->pHead = newHead;
}

void InsertFrontNode(pLinkNode pos, DataType x)     //�ڵ�ǰ���ǰ����һ�����
{
	assert(pos);
	pLinkNode newNode = NULL;
	newNode = (pLinkNode)malloc(sizeof(LinkNode));       //����һ���½��
	if (NULL == newNode)
	{
		printf("out of memory\n");
		exit(EXIT_FAILURE);
	}
	newNode->next = pos->next;             //������½ڵ���뵽pos����
	pos->next = newNode;
	newNode->data = pos->data;             //��posָ���data���浽newHead����
	pos->data = x;                         //��x������pos����
}

pLinkNode FindMindNode(pLinkList list)          //�����м�ڵ�
{
	assert(list);
	pLinkNode fast = list->pHead;                //��ָ�룬ÿ��������
	pLinkNode slow = list->pHead;               //��ָ�룬ÿ����һ��
	while (NULL != fast)
	{
		if (NULL != fast->next)                  //���fast����β���
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		else
		{
			break;
		}
	}
	return slow;
}

void DelKnode(pLinkList list, int k)                    //ɾ��������k����㣬kҪ����1��С�������� 
{
	assert(list);
	if (NULL == list->pHead || NULL == list->pHead->next || k <= 1)
	{
		return;
	}
	pLinkNode cur = list->pHead;
	pLinkNode del = list->pHead;                 //delָ��Ҫɾ���Ľ��
	while (cur->next != NULL)
	{
		k--;                                    //cur����k����del�ٿ�ʼ��
		if (k <= 0)
		{
			del = del->next;
		}
		cur = cur->next;
	}
	if (k <= 0)
	{
		del->data = del->next->data;          //del����һ������data���浽del����
		cur = del->next;                      //��סdel��һ�����ĵ�ַ
		del->next = cur->next;                //delָ��del������һ�����
		free(cur);
		cur = NULL;
	}
}




pLinkNode CheckCycle(pLinkList list)             //�ж��Ƿ����,�������򷵻�����λ��
{
	assert(list);
	pLinkNode fast = list->pHead;                 //��ָ��
	pLinkNode slow = list->pHead;                 //��ָ��
	if (NULL == list->pHead)
	{
		return NULL;
	}
	while (fast != NULL)
	{
		if (NULL != fast->next)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		else
		{
			break;
		}
		if (fast == slow)                   //����ָ���������л�
		{
			return slow;
		}
	}
	return NULL;                            //û���򷵻�NULL
}

int  GetCircleLength(pLinkNode meet)         //����������ⷵ�ػ��ĳ���
{
	assert(meet);
	pLinkNode cur = meet->next;
	int count = 1;
	while (cur != meet)
	{
		count++;
		cur = cur->next;
	}
	return count;
}

pLinkNode GetCycleEntryNode(pLinkList list, pLinkNode meet)   //���һ������
{
	assert(list);
	pLinkNode link = list->pHead;             //linkָ�������ͷ
	pLinkNode cycle = meet;                   //cycleָ�������������
	while (link != cycle)
	{
		link = link->next;
		cycle = cycle->next;
	}
	return link;
}



pLinkList Merge(pLinkList list1, pLinkList list2)    //�ϲ�������������
{
	assert(list1);
	assert(list2);
	if ((NULL == list1->pHead) && (NULL == list2->pHead))   //�����������
	{
		return NULL;
	}
	else if (NULL == list1->pHead)
	{
		return list2;
	}
	else if (NULL == list2->pHead)
	{
		return list1;
	}
	pLinkNode last = NULL;
	pLinkNode newHead = NULL;                       //����ͷ���
	if (list1->pHead->data <list2->pHead->data)     //�ѶԵ�һ��������⴦��
	{
		newHead = list1->pHead;
		list1->pHead = list1->pHead->next;
	}
	else
	{
		newHead = list2->pHead;
		list2->pHead = list2->pHead->next;
	}
	last = newHead;                                    //��lastָ�������������β��
	while ((NULL != list1->pHead) && (NULL != list2->pHead))
	{
		if (list1->pHead->data <list2->pHead->data)
		{
			last->next = list1->pHead;
			list1->pHead = list1->pHead->next;
		}
		else
		{
			last->next = list2->pHead;
			list2->pHead = list2->pHead->next;
		}
		last = last->next;
	}
	if (NULL == list1->pHead)                 //��������ʣ�µ�Ԫ�����ӵ�last֮��
	{
		last->next = list2->pHead;
	}
	else
	{
		last->next = list1->pHead;
	}
	list1->pHead = newHead;
	return list1;
}


int CheckCross(pLinkList list1, pLinkList list2)   //�ж������Ƿ��ཻ
{
	assert(list1);
	assert(list2);
	pLinkNode cur1 = list1->pHead;
	pLinkNode cur2 = list2->pHead;
	if ((NULL == list1->pHead) || (NULL == list2->pHead))
	{
		return -1;
	}
	while (NULL != cur1->next)
	{
		cur1 = cur1->next;
	}
	while (NULL != cur2->next)
	{
		cur2 = cur2->next;
	}
	if (cur1 == cur2)
	{
		return  1;                //�ཻ
	}
	else
	{
		return -1;                 //���ཻ
	}
}