#include"linklist.h"

void CreateNode(pLinkNode *newNode, DataType x)
{
	
	*newNode = (pLinkNode)malloc(sizeof(LinkNode));
	if (NULL == *newNode)
	{
		printf("out of memory\n");
		exit(EXIT_FAILURE);
	}
	(*newNode)->data = x;
	(*newNode)->next = NULL;
}
void InitLinkList(pLinkList list)
{
	assert(list);
	list->pHead = NULL;
}

void DestoryList(pLinkList list)
{
	assert(list);
	if (NULL==list->pHead)            //空链表直接返回
	{
		return;
	}
	else
	{
		pLinkNode cur = list->pHead;     //cur指向第一个结点
		while (cur != NULL)         
		{
			list->pHead = cur->next;    //pHead指向cur的下一个结点，当cur是最后一个结点时，pHead指向空
			free(cur);
			cur = list->pHead;          //cur指向当前第一个结点,当链表为空时，cur指向空
		}
	}

}

void PushBack(pLinkList list, DataType x)
{
	assert(list);
	pLinkNode newNode = NULL;
	CreateNode(&newNode,x);
	if (NULL == (list->pHead))             //如果是空链表，直接插入头指针之后
	{
		list->pHead = newNode;
	}
	else
	{
		pLinkNode cur = list->pHead;
		while (NULL != (cur->next))            //找到最后一个结点cur
		{
			cur = cur->next;
		}
		cur->next = newNode;
	}
}

void PopBack(pLinkList list)
{
	assert(list);
	if (NULL == list->pHead)
	{
		return;
	}
	else
	{
		pLinkNode cur = list->pHead;
		if (NULL == cur->next)                 //如果只有一个结点
		{
			free(cur);
			list->pHead= NULL;
		}
		else
		{
			while (NULL != cur->next->next)         //大于一个结点，先找到倒数第二个结点
			{
				cur = cur->next;
			}
			free(cur->next);
			cur->next= NULL;
		}
	}
}

void PushFront(pLinkList list, DataType x)        
{
	assert(list);
	pLinkNode newNode = NULL;
	CreateNode(&newNode, x);
	newNode->next =list->pHead;           //newNode的指针域先指向第一个结点
	list->pHead= newNode;                 //头指针指向newNode
}

void PopFront(pLinkList list)
{
	assert(list);
	if (NULL == list->pHead)              //空链表
	{
		return;
	}
	pLinkNode cur = list->pHead;         //cur指向第一个结点
	list->pHead = cur->next;             //指向第一个结点的指针域
	free(cur);
	cur = NULL;
}

void PrintList(pLinkList list)
{
	assert(list);
	pLinkNode cur = list->pHead;
	while (NULL != cur)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("over\n");
}

pLinkNode Find(pLinkList list, DataType x)
{
	assert(list);
	pLinkNode cur = list->pHead;
	while (NULL != cur)
	{
		if (cur->data == x)
		{
			break;
		}
		cur = cur->next;
	}
	return cur;              
}

void Insert(pLinkList list, pLinkNode pos, DataType x)  //在pos后面插入元素
{
	assert(list);
	pLinkNode newNode = NULL;
	CreateNode(&newNode, x);
	pLinkNode cur = list->pHead;
	while (NULL != cur)                                  //先找到这个位置
	{
		if (cur == pos)
		{
			break;
		}
		cur = cur->next;
	}
	if (NULL != cur)
	{
		newNode->next=cur->next;
		cur->next = newNode;
	}
	else
	{
		printf("没有这个结点\n");
	}
	
}

void Remove(pLinkList list, DataType x)
{
	assert(list);
	pLinkNode cur = list->pHead;
	pLinkNode p = list->pHead;
	if (NULL == list->pHead)              //空链表直接返回
	{
		return;
	}
	if (NULL == cur->next)                 //如果只有一个结点
	{
		if (cur->data == x)
		{
			list->pHead = cur->next;
			free(cur);
			return;
		}
	}
	else
	{
		if (cur->data == x)                   //先判断第一个结点是不是要删除的结点
		{
			list->pHead = cur->next;
			free(cur);
			return;
		}
		cur = cur->next;
		while (NULL != cur)
		{
			if (cur->data == x)
			{
				p->next = cur->next;   //p结点的指针域指向要删除结点的指针域
				free(cur);
				return;
			}
			p = cur;
			cur = cur->next;
		}
	}
}

void RemoveAll(pLinkList list, DataType x)
{
	assert(list);
	pLinkNode cur = list->pHead;
	pLinkNode p = NULL;
	if (NULL == list->pHead)
	{
		return;
	}
	while (NULL != cur)
	{
		if (NULL == list->pHead->next)          //如果要只有一个结点
		{
			if (cur->data == x)                 //如果是则删除
			{
				list->pHead = cur->next;
				free(cur);
				return;
			}
		}
		else if (list->pHead->data == x)         //判断是不是第一个结点，是则删除，继续判断
		{
				list->pHead = cur->next;
				free(cur);
				cur = list->pHead;
		}
		else
		{
			break;
		}
	}
	//要删除的结点在第一个结点之后
	cur = cur->next;
	p = list->pHead ;
	while (NULL != cur)
	{
		if (cur->data == x)
		{
			p->next = cur->next;           //p结点的指针域指向要删除结点的指针域
			free(cur);
			cur = p;
		}
		p = cur;
		cur = cur->next;
	}
}

void Erase(pLinkList list, pLinkNode pos)   //删除pos后面的结点
{
	assert(list);
	pLinkNode cur = list->pHead;
	pLinkNode p = list->pHead;
	if (NULL == cur)
	{
		return;
	}
	if (NULL == cur->next)                  //如果只有一个结点
	{
		if (cur == pos)
		{
			free(cur);
			list->pHead = NULL;
		}
	}
	else
	{
		if (cur == pos)                        //如果是第一个结点
		{
			list->pHead = cur->next;
			free(cur);
			return;
		}
		cur = cur->next;
		while (NULL != cur)
		{
			if (cur == pos)
			{
				p->next = cur->next;
				free(cur);
				return;
			}
			p= cur;
			cur = cur->next;
		}
	}
}

void BubbleSort(pLinkList list)
{
	assert(list);
	pLinkNode cur = list->pHead;
	pLinkNode p1= list->pHead;
	int flag = 0;
	DataType tmp=0;
	if (NULL == list->pHead)
	{
		return;
	}
	if (NULL == cur->next)
	{
		return;
	}
	pLinkNode p2 = list->pHead->next;
	cur = cur->next;
	while (NULL!=cur)
	{
		flag = 1;
		while (NULL != p2)
		{
			if (p1->data > p2->data)
			{
				tmp = p1->data;
				p1->data = p2->data;
				p2->data = tmp;
				flag = 0;
			}
			p2 = p2->next;
			p1 = p1->next;
		}
		if (flag)
		{
			break;
		}
		p1 = list->pHead;
		p2 = list->pHead->next;
	    cur = cur->next;
	}
}
