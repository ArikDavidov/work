#include "List.h"

#include <stdio.h>
#include <stdlib.h>

#define LIST_MAGIC 0xBAADA555

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

#define LIST_FIRST(L)	((L)->m_head.m_next)
#define LIST_LAST(L)	((L)->m_tail.m_prev)
#define LIST_END(L)		(&(L)->m_tail)

#define IS_EMPTY(L)		(LIST_FIRST((L)) == LIST_END((L)))
#define IS_A_LIST(L)	((L) && LIST_MAGIC == (L)->m_magicNum)

#define IS_FIRST(I)		(NULL == ((Node*)(I))->m_prev->m_prev)
#define IS_END(I) 		(NULL == ((Node*)(I))->m_next)


static void NodesDestroy(List* _list, UserActionFunc _destoryFunc)
{
	Node* currentNode = LIST_FIRST(_list);
	Node* nextNode    = NULL;
	
	while (currentNode != LIST_END(_list))
	{
		nextNode = currentNode->m_next;
		_destoryFunc(currentNode->m_data, NULL);
		free(currentNode);
		currentNode = nextNode;
	}
}

static void NodeInsertBefore(Node* _dest, Node* _node)
{	
	typedef struct
	{
		const char* m_key;
		const char* m_value;
	} TestPair;
	
	printf("NodeInsertBefore: %s\n", (char*)((TestPair*)_node->m_data)->m_key);
	
	_node->m_prev = _dest->m_prev;
	_dest->m_prev->m_next = _node;
	_dest->m_prev = _node;
	_node->m_next = _dest;
}

/*
static void NodesInsertBefore(Node* _dest, Node* _begin, Node* _end)
{
	_begin->m_prev = _dest->m_prev;
	_dest->m_prev->m_next = _begin;
	_dest->m_prev = _end;
	_end->m_next = _dest;
}
*/

static Node* NodeCreateAndInsertBefore(Node* _dest, void* _data)
{
	Node* node = NULL;
	typedef struct
	{
		const char* m_key;
		const char* m_value;
	} TestPair;


	node = malloc(sizeof(Node));
	if (NULL == node)
	{
		return NULL;
	}
	
	node->m_data = _data;
	printf("%p\n", (void*)node->m_data);
	printf("NodeCreateAndInsertBefore: %s\n", (char*)((TestPair*)_data)->m_key);
	NodeInsertBefore(_dest, node);
	
	return node;
}

static void NodeRemove(Node* _node)
{
	_node->m_prev->m_next = _node->m_next;
	_node->m_next->m_prev = _node->m_prev;
}
/*
static Node* NodesRemove(Node* _begin, Node* _end)
{
	Node* tmpEnd = _end->m_prev;

	_end->m_prev = _begin->m_prev;	
	_begin->m_prev->m_next = _end;

	return tmpEnd;
}
*/
List* ListCreate(void)
{
	List* list = NULL;
	
	list = malloc(sizeof(List));
	if (NULL == list)
	{
		return NULL;
	}	
	
	list->m_magicNum    = LIST_MAGIC;
	list->m_head.m_next = LIST_END(list);
	list->m_head.m_prev = &list->m_head;
	list->m_tail.m_next = LIST_END(list);
	list->m_tail.m_prev = &list->m_head;
	
	return list;
}

void ListDestroy(List** _list, UserActionFunc _destoryFunc)
{
	if (NULL == _list || NULL == *_list || NULL == _destoryFunc || LIST_MAGIC != (*_list)->m_magicNum)
	{
		return;
	}
	
	(*_list)->m_magicNum = 0;
	NodesDestroy(*_list, _destoryFunc);
	free(*_list);
	*_list = NULL;
}

ListErrors ListPushHead(List* _list, void* _data)
{
	Node* node;
	
	typedef struct
	{
		const void* m_key;
		const void* m_value;
	} Pair;

	if (!(IS_A_LIST(_list)))
	{
		return LIST_UNINITIALIZED;
	}
	printf("ListPushHead:%s\n",(char*)((Pair*)_data)->m_key);
	node = NodeCreateAndInsertBefore(LIST_FIRST(_list), _data);
	if (NULL == node)
	{
		return LIST_ALLOCATION_FAILED;
	}
	printf("AfterNodeCreateAndInsertBefore: %s\n", (char*)((Pair*)node->m_data)->m_key);
	printf("AfterNodeCreateAndInsertBefore: %s\n", (char*)((Pair*)LIST_FIRST(_list)->m_data)->m_key);
		
	return LIST_OK;
}

ListErrors ListPushTail(List* _list, void* _data)
{
	Node* node;
	
	if (!(IS_A_LIST(_list)))
	{
		return LIST_UNINITIALIZED;
	}

	node = NodeCreateAndInsertBefore(LIST_END(_list), _data);
	if (NULL == node)
	{
		return LIST_ALLOCATION_FAILED;
	}

	return LIST_OK;	
}

ListErrors ListPopHead(List* _list, void* *_data)
{
	Node* currentNode;
	
	if (NULL == _list || NULL == _data || LIST_MAGIC != _list->m_magicNum)
	{
		return LIST_UNINITIALIZED;
	}

	currentNode = LIST_FIRST(_list);
	
	if (currentNode == LIST_END(_list))
	{
		return LIST_LIST_IS_EMPTY;
	}
	
	NodeRemove(currentNode);
	*_data = currentNode->m_data;
	free(currentNode);

	return LIST_OK;
}

ListErrors ListPopTail(List* _list, void* *_data)
{
	Node* currentNode;
	
	if (NULL == _list || NULL == _data || LIST_MAGIC != _list->m_magicNum)
	{
		return LIST_UNINITIALIZED;
	}

	currentNode = LIST_LAST(_list);
	
	if (currentNode == &_list->m_head)
	{
		return LIST_LIST_IS_EMPTY;
	}
	
	NodeRemove(currentNode);
	*_data = currentNode->m_data;
	free(currentNode);

	return LIST_OK;	
}

size_t ListCountItems(const List* _list)
{
	size_t i = 0;
	Node* currentNode = NULL;
	
	if (!(IS_A_LIST(_list)))
	{
		return 0;
	}
	
	currentNode = LIST_FIRST(_list);
	
	while (currentNode != LIST_END(_list))
	{
		++i;
		currentNode = currentNode->m_next;
	}
	
	return i;
}


/**
 * @brief The function perform an action on each individual item in the list. 
 * @param[in] _list: Pointer to a list.
 * @param[in] _action: Pointer to a function of the action to perform.
 * @param[in] _context: Pointer context value for the action.
 * @return The number of times (items) the action was perform on.
 *
 * @warning On NULL pointer to a list or funciton, the return value will be 0.
 */
size_t ListForEach(const List* _list, UserActionFunc _action, void* _context);



	
int ListIsEmpty(const List* _list)
{
	if (!(IS_A_LIST(_list)))
	{
		return 0;
	}
	
	return (IS_EMPTY(_list)) ? 1 : 0;
}	

ListErrors FindFirstForward(const List* _list, PredicateFunc _predicateFunc, void* _context, void* *_item)
{
	Node* currentNode;
	
	if (!IS_A_LIST(_list))
	{
		return LIST_UNINITIALIZED;
	}

	currentNode = LIST_FIRST(_list);

	*_item = NULL;
	while (currentNode != LIST_END(_list))
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

ListItr ListItrBegin(const List* _list)
{
	if (!(IS_A_LIST(_list)))
	{
		return NULL;
	}
	
	return (ListItr)LIST_FIRST(_list);
}

ListItr ListItrEnd(const List* _list)
{
	if (!(IS_A_LIST(_list)))
	{
		return NULL;
	}
	
	return (ListItr)LIST_END(_list);
}


int ListItrEquals(const ListItr _a, const ListItr _b)
{
	return (_a == _b) ? 1 : 0;
}


ListItr ListItrNext(ListItr _itr)
{
	if (NULL == _itr)
	{
		return NULL;
	}
	
	return (ListItr)(((Node*)_itr)->m_next);
}

ListItr ListItrPrev(ListItr _itr)
{
	if (NULL == _itr)
	{
		return NULL;
	}

	if (IS_FIRST(_itr))
	{
		return _itr;
	}
	
	return (ListItr)((Node*)_itr)->m_prev;
}

void* ListItrGet(ListItr _itr)
{
	if (NULL == _itr || IS_END(_itr))
	{
		return NULL;
	}
	
	return ((Node*)_itr)->m_data;
}

void* ListItrSet(ListItr _itr, void* _element)
{
	void* dataPtr;
	
	if (NULL == _itr || NULL == _element || IS_END(_itr))
	{
		return NULL;
	}
	
	dataPtr = ((Node*)_itr)->m_data;
	((Node*)_itr)->m_data = _element;
	
	return dataPtr;
}

ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
	Node* node;

	if (NULL == _itr || NULL == _element || NULL == ((Node*)_itr)->m_prev)
	{
		return NULL;
	}

	node = NodeCreateAndInsertBefore((Node*)_itr, _element);
	
	return (void*)node;
}

void* ListItrRemove(ListItr _itr)
{
	void*  dataPtr;

	if (NULL == _itr)
	{
		return NULL;
	}
	
	dataPtr = ((Node*)_itr)->m_data;

	NodeRemove((Node*)_itr);

	return dataPtr;
}










