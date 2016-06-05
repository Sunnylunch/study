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
	if (NULL==list->pHead)            //������ֱ�ӷ���
	{
		return;
	}
	else
	{
		pLinkNode cur = list->pHead;     //curָ���һ�����
		while (cur != NULL)         
		{
			list->pHead = cur->next;    //pHeadָ��cur����һ����㣬��cur�����һ�����ʱ��pHeadָ���
			free(cur);
			cur = list->pHead;          //curָ��ǰ��һ�����,������Ϊ��ʱ��curָ���
		}
	}

}

void PushBack(pLinkList list, DataType x)
{
	assert(list);
	pLinkNode newNode = NULL;
	CreateNode(&newNode,x);
	if (NULL == (list->pHead))             //����ǿ�����ֱ�Ӳ���ͷָ��֮��
	{
		list->pHead = newNode;
	}
	else
	{
		pLinkNode cur = list->pHead;
		while (NULL != (cur->next))            //�ҵ����һ�����cur
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
		if (NULL == cur->next)                 //���ֻ��һ�����
		{
			free(cur);
			list->pHead= NULL;
		}
		else
		{
			while (NULL != cur->next->next)         //����һ����㣬���ҵ������ڶ������
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
	newNode->next =list->pHead;           //newNode��ָ������ָ���һ�����
	list->pHead= newNode;                 //ͷָ��ָ��newNode
}

void PopFront(pLinkList list)
{
	assert(list);
	if (NULL == list->pHead)              //������
	{
		return;
	}
	pLinkNode cur = list->pHead;         //curָ���һ�����
	list->pHead = cur->next;             //ָ���һ������ָ����
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

void Insert(pLinkList list, pLinkNode pos, DataType x)  //��pos�������Ԫ��
{
	assert(list);
	pLinkNode newNode = NULL;
	CreateNode(&newNode, x);
	pLinkNode cur = list->pHead;
	while (NULL != cur)                                  //���ҵ����λ��
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
		printf("û��������\n");
	}
	
}

void Remove(pLinkList list, DataType x)
{
	assert(list);
	pLinkNode cur = list->pHead;
	pLinkNode p = list->pHead;
	if (NULL == list->pHead)              //������ֱ�ӷ���
	{
		return;
	}
	if (NULL == cur->next)                 //���ֻ��һ�����
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
		if (cur->data == x)                   //���жϵ�һ������ǲ���Ҫɾ���Ľ��
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
				p->next = cur->next;   //p����ָ����ָ��Ҫɾ������ָ����
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
		if (NULL == list->pHead->next)          //���Ҫֻ��һ�����
		{
			if (cur->data == x)                 //�������ɾ��
			{
				list->pHead = cur->next;
				free(cur);
				return;
			}
		}
		else if (list->pHead->data == x)         //�ж��ǲ��ǵ�һ����㣬����ɾ���������ж�
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
	//Ҫɾ���Ľ���ڵ�һ�����֮��
	cur = cur->next;
	p = list->pHead ;
	while (NULL != cur)
	{
		if (cur->data == x)
		{
			p->next = cur->next;           //p����ָ����ָ��Ҫɾ������ָ����
			free(cur);
			cur = p;
		}
		p = cur;
		cur = cur->next;
	}
}

void Erase(pLinkList list, pLinkNode pos)   //ɾ��pos����Ľ��
{
	assert(list);
	pLinkNode cur = list->pHead;
	pLinkNode p = list->pHead;
	if (NULL == cur)
	{
		return;
	}
	if (NULL == cur->next)                  //���ֻ��һ�����
	{
		if (cur == pos)
		{
			free(cur);
			list->pHead = NULL;
		}
	}
	else
	{
		if (cur == pos)                        //����ǵ�һ�����
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
