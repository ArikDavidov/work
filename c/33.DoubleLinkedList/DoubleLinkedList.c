#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"

typedef struct Node Node;

struct Node
{
	int 	m_data;
	Node* m_next;
	Node* m_prev;
};

struct List
{	
	Node   m_head;
	Node   m_tail;
	size_t m_magicNum;
};

List* ListCreate(void)
{
	List* list = NULL;
	
	list = malloc(sizeof(List));
	if (NULL != list)
	{
		list->m_magicNum = 4121996;
		list->m_head.m_next = &list->m_tail;
		list->m_head.m_prev = NULL;
		list->m_tail.m_next = NULL;
		list->m_tail.m_prev = &list->m_head;
	}	
	return list;
}

static void FreeNodes(List* _list)
{
	Node* currentNode = _list->m_head.m_next;
	Node* nextNode    = NULL;
	
	while (currentNode != &_list->m_tail)
	{	/* The list is not empty */
		nextNode = currentNode->m_next;
		free(currentNode);
		currentNode = nextNode;
	}
}

void ListDestroy(List* _list)
{
	if (NULL != _list && 4121996 == _list->m_magicNum)
	{
		_list->m_magicNum = 0;
		FreeNodes(_list);
		free(_list);
	}
}

static void InsertNode(Node* _prevNode, Node* _node)
{
	_prevNode->m_next->m_prev = _node;
	_node->m_next = _prevNode->m_next;
	_node->m_prev = _prevNode;
	_prevNode->m_next = _node;
}

ADTErr ListPushHead(List* _list, int _data)
{
	Node* node;
	ADTErr res = ERR_GENERAL;
	
	if (NULL == _list)
	{
		return ERR_NOT_INITIALIZED;
	}
	node = malloc(sizeof(Node));
	if (NULL != node)
	{
		node->m_data = _data;
		InsertNode(&_list->m_head, node);
		res = ERR_OK;
	}
	else
	{
		res = ERR_ALLOCATION_FAILED;
	}
	return res;
}

ADTErr ListPushTail(List* _list, int _data)
{
	Node* node;
	ADTErr res = ERR_GENERAL;
	
	if (NULL == _list)
	{
		return ERR_NOT_INITIALIZED;
	}
	node = malloc(sizeof(Node));
	if (NULL != node)
	{
		node->m_data = _data;
		InsertNode(_list->m_tail.m_prev, node);
		res = ERR_OK;
	}
	else
	{
		res = ERR_ALLOCATION_FAILED;
	}
	return res;
}

ADTErr ListPopHead(List* _list, int* _data)
{
	Node* currentNode;
	ADTErr res = ERR_LIST_IS_EMPTY;
	
	if (NULL == _list || NULL == _data)
	{
		return ERR_NOT_INITIALIZED;
	}
	currentNode = _list->m_head.m_next;
	
	if (currentNode != &_list->m_tail)
	{	/*  The list is not empty */
		_list->m_head.m_next = currentNode->m_next;
		currentNode->m_next->m_prev = &_list->m_head;
		*_data = currentNode->m_data;
		free(currentNode);
		res = ERR_OK;
	}
	return res;	
}

/*		
int ListIsEmpty(List* _list)
{
	
}
*/
	
	


