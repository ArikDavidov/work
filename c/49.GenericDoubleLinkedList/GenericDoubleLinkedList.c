#include "GenericDoubleLinkedList.h"

#include <stdlib.h>

#define LISL_MAGIC 0xBAADA555

typedef struct Node Node;

struct Node
{
	void* m_data;
	Node* m_next;
	Node* m_prev;
};

struct List
{
	size_t m_magicNum;
	Node   m_head;
	Node   m_tail;
};

static void DestroyNodes(List* _list, UserActionFunc _destoryFunc)
{
	Node* currentNode = _list->m_head.m_next;
	Node* nextNode    = NULL;
	
	while (currentNode != &_list->m_tail)
	{
		nextNode = currentNode->m_next;
		_destoryFunc(currentNode->m_data, NULL);
		free(currentNode);
		currentNode = nextNode;
	}
}

/*
static void InsertNode(Node* _prevNode, Node* _node)
{
	_prevNode->m_next->m_prev = _node;
	_node->m_next = _prevNode->m_next;
	_node->m_prev = _prevNode;
	_prevNode->m_next = _node;
}
*/

static void NodeInsertBefore(Node* _currentNode, Node* _node)
{
	_currentNode->m_prev->m_next = _node;
	_node->m_prev = _currentNode->m_prev;
	_node->m_next = _currentNode;
	_currentNode->m_prev = _node;
}

static void RemoveNode(Node* _node)
{
	_node->m_prev->m_next = _node->m_next;
	_node->m_next->m_prev = _node->m_prev;
}

List* ListCreate(void)
{
	List* list = NULL;
	
	list = malloc(sizeof(List));
	if (NULL == list)
	{
		return NULL;
	}	
	
	list->m_magicNum    = LISL_MAGIC;
	list->m_head.m_next = &list->m_tail;
	list->m_head.m_prev = NULL;
	list->m_tail.m_next = NULL;
	list->m_tail.m_prev = &list->m_head;
	
	return list;
}

void ListDestroy(List** _list, UserActionFunc _destoryFunc)
{
	if (NULL == _list || NULL == *_list || NULL == _destoryFunc || LISL_MAGIC != (*_list)->m_magicNum)
	{
		return;
	}
	
	(*_list)->m_magicNum = 0;
	DestroyNodes(*_list, _destoryFunc);
	free(*_list);
	*_list = NULL;
}

ListErrors ListPushHead(List* _list, void* _data)
{
	Node* node;
	
	if (NULL == _list || LISL_MAGIC != _list->m_magicNum)
	{
		return LIST_UNINITIALIZED;
	}
	node = malloc(sizeof(Node));
	if (NULL == node)
	{
		return LIST_ALLOCATION_FAILED;
	}
	
	node->m_data = _data;
	InsertNode(&_list->m_head, node);

	return LIST_OK;
}

ListErrors ListPushTail(List* _list, void* _data)
{
	Node* node;
	
	if (NULL == _list || LISL_MAGIC != _list->m_magicNum)
	{
		return LIST_UNINITIALIZED;
	}

	node = malloc(sizeof(Node));
	if (NULL == node)
	{
		return LIST_ALLOCATION_FAILED;
	}
	
	node->m_data = _data;
	InsertNode(_list->m_tail.m_prev, node);

	return LIST_OK;	
}

ListErrors ListPopHead(List* _list, void* *_data)
{
	Node* currentNode;
	
	if (NULL == _list || NULL == _data || LISL_MAGIC != _list->m_magicNum)
	{
		return LIST_UNINITIALIZED;
	}

	currentNode = _list->m_head.m_next;
	
	if (currentNode == &_list->m_tail)
	{
		return LIST_LIST_IS_EMPTY;
	}
	
	RemoveNode(currentNode);
	*_data = currentNode->m_data;
	free(currentNode);

	return LIST_OK;
}

ListErrors ListPopTail(List* _list, void* *_data)
{
	Node* currentNode;
	
	if (NULL == _list || NULL == _data || LISL_MAGIC != _list->m_magicNum)
	{
		return LIST_UNINITIALIZED;
	}

	currentNode = _list->m_tail.m_prev;
	
	if (currentNode == &_list->m_head)
	{
		return LIST_LIST_IS_EMPTY;
	}
	
	RemoveNode(currentNode);
	*_data = currentNode->m_data;
	free(currentNode);

	return LIST_OK;	
}

size_t ListCountItems(const List* _list)
{
	size_t i = 0;
	
	if (NULL == _list || LISL_MAGIC != _list->m_magicNum)
	{
		return 0;
	}

	Node* currentNode = _list->m_head.m_next;
	
	while (currentNode != &_list->m_tail)
	{
		++i;
		currentNode = currentNode->m_next;
	}
	
	return i;
}
	
int ListIsEmpty(const List* _list)
{
	if (NULL == _list || LISL_MAGIC != _list->m_magicNum)
	{
		return 0;
	}
	
	return (_list->m_head.m_next == &_list->m_tail) ? 1 : 0;
}	

ListErrors FindFirstForward(const List* _list, PredicateFunc _predicateFunc, void* _context, void* *_item)
{
	Node* currentNode;
	
	if (NULL == _list || LISL_MAGIC != _list->m_magicNum)
	{
		return LIST_UNINITIALIZED;
	}

	currentNode = _list->m_head.m_next;

	*_item = NULL;
	while (currentNode != &_list->m_tail)
	{
		if (_predicateFunc(currentNode->m_data, _context))
		{
			*_item = currentNode->m_data;
			break;
		}
		currentNode = currentNode->m_next;
	}

	return LIST_OK;
}








