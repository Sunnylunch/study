
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


void SelectSort(pLinkList list)                  //选择排序
{
	assert(list);
	if (NULL == list->pHead || NULL == list->pHead->next)  //如果是空链表或者只有一个结点则直接结束
	{
		return;
	}
	pLinkNode cur = list->pHead;
	pLinkNode p = NULL;
	pLinkNode min = NULL;
	while (cur != NULL)
	{
		p = cur->next;               //p指向无序区第二个元素
		min = cur;                    //min指向无序区第一个元素
		while (p != NULL)
		{
			if (min->data > p->data)
			{
				min = p;             //min记录最小的data的地址
			}
			p = p->next;
		}
		if (min != cur)              //将min所指向的data与无序区第一个元素进行交换
		{
			DataType tmp = cur->data;
			cur->data = min->data;
			min->data = tmp;
		}
		cur = cur->next;              //有序区加一，无序区减一
	}
}

void EraseNotTail(pLinkNode pos)                 //删除非尾结点
{
	assert(pos->next);
	pLinkNode cur = pos->next;
	pos->data = cur->data;
	pos->next = cur->next;
	free(cur);
	cur = NULL;
}

void Reverselist(pLinkList list)                   //反转链表
{
	assert(list);
	if (NULL == list->pHead || NULL == list->pHead->next)
	{
		return;
	}
	pLinkNode newHead = NULL;           //指向新链表的头
	pLinkNode tmp = NULL;
	pLinkNode cur = list->pHead;
	while (cur != NULL)
	{
		tmp = cur->next;                 //tmp保存cur的下一个结点
		cur->next = newHead;             //指向新链表的头
		newHead = cur;                   //链表的头指针移动
		cur = tmp;                       //cur指向下一个结点
	}
	list->pHead = newHead;
}

void InsertFrontNode(pLinkNode pos, DataType x)     //在当前结点前插入一个结点
{
	assert(pos);
	pLinkNode newNode = NULL;
	newNode = (pLinkNode)malloc(sizeof(LinkNode));       //创建一个新结点
	if (NULL == newNode)
	{
		printf("out of memory\n");
		exit(EXIT_FAILURE);
	}
	newNode->next = pos->next;             //将这个新节点插入到pos后面
	pos->next = newNode;
	newNode->data = pos->data;             //将pos指向的data保存到newHead里面
	pos->data = x;                         //将x保存在pos里面
}

pLinkNode FindMindNode(pLinkList list)          //查找中间节点
{
	assert(list);
	pLinkNode fast = list->pHead;                //快指针，每次走两步
	pLinkNode slow = list->pHead;               //慢指针，每次走一步
	while (NULL != fast)
	{
		if (NULL != fast->next)                  //如果fast不是尾结点
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

void DelKnode(pLinkList list, int k)                    //删除倒数第k个结点，k要大于1，小于链表长度 
{
	assert(list);
	if (NULL == list->pHead || NULL == list->pHead->next || k <= 1)
	{
		return;
	}
	pLinkNode cur = list->pHead;
	pLinkNode del = list->pHead;                 //del指向要删除的结点
	while (cur->next != NULL)
	{
		k--;                                    //cur先走k步，del再开始走
		if (k <= 0)
		{
			del = del->next;
		}
		cur = cur->next;
	}
	if (k <= 0)
	{
		del->data = del->next->data;          //del的下一个结点的data保存到del里面
		cur = del->next;                      //记住del下一个结点的地址
		del->next = cur->next;                //del指向del的下下一个结点
		free(cur);
		cur = NULL;
	}
}




pLinkNode CheckCycle(pLinkList list)             //判断是否带环,若带环则返回相遇位置
{
	assert(list);
	pLinkNode fast = list->pHead;                 //快指针
	pLinkNode slow = list->pHead;                 //慢指针
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
		if (fast == slow)                   //快慢指针相遇则有环
		{
			return slow;
		}
	}
	return NULL;                            //没环则返回NULL
}

int  GetCircleLength(pLinkNode meet)         //若链表带环这返回环的长度
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

pLinkNode GetCycleEntryNode(pLinkList list, pLinkNode meet)   //查找环的入口
{
	assert(list);
	pLinkNode link = list->pHead;             //link指向链表的头
	pLinkNode cycle = meet;                   //cycle指向链表的相遇点
	while (link != cycle)
	{
		link = link->next;
		cycle = cycle->next;
	}
	return link;
}



pLinkList Merge(pLinkList list1, pLinkList list2)    //合并两个有序链表
{
	assert(list1);
	assert(list2);
	if ((NULL == list1->pHead) && (NULL == list2->pHead))   //考虑特殊情况
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
	pLinkNode newHead = NULL;                       //虚拟头结点
	if (list1->pHead->data <list2->pHead->data)     //把对第一个结点特殊处理
	{
		newHead = list1->pHead;
		list1->pHead = list1->pHead->next;
	}
	else
	{
		newHead = list2->pHead;
		list2->pHead = list2->pHead->next;
	}
	last = newHead;                                    //让last指向虚拟结点链表的尾部
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
	if (NULL == list1->pHead)                 //将集合中剩下的元素链接到last之后
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


int CheckCross(pLinkList list1, pLinkList list2)   //判断链表是否相交
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
		return  1;                //相交
	}
	else
	{
		return -1;                 //不相交
	}
}