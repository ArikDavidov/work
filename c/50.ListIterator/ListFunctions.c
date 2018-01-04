#include "List.h"
#include "ListFunctions.h"

ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	ListItr itr = NULL;
	
	for (itr = _begin; !ListItrEquals(itr, _end); itr = ListItrNext(itr))
	{
		// if (_predicate(((struct Node*)itr)->m_data, _context))
		// {
		// 	return itr;
		// }
	}
	
	return _end;
}




/*
ListItr ListItrSplice(ListItr _dest, ListItr _begin, ListItr _end)
{
	ListItr tmpEnd;

	if (NULL == _dest || NULL != _begin || NULL != _end)
	{
		return NULL;
	}

	tmpEnd = NodesRemove((Node*)_begin, (Node*)_end);
	NodesInsertBefore((Node*)_dest, (Node*)_begin, tmpEnd);

	return _dest;
}

List* ListItrCut(ListItr _begin, ListItr _end)
{
	ListItr list = NULL;
	Node* tmpEnd;

	if (NULL != _begin || NULL != _end)
	{
		return NULL;
	}

	list = ListCreate();
	if (NULL == list)
	{
		return NULL;
	}

	tmpEnd = NodesRemove((Node*)_begin, (Node*)_end);
	NodesInsertBefore(LIST_END(list), (Node*)_begin, tmpEnd);
	
	return list;
}
*/


