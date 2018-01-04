#include <stdio.h>
#include "linked.h"


Person* ListInsertHead(Person* _head, Person* _p)
{
	if (NULL == _p)
	{
		return _head;
	}
	_p->m_next = _head;
	return _p;	
}

Person* ListRemoveHead(Person* _head, Person** _item)
{	
	if (NULL != _item)
	{
		*_item = _head;
		if (NULL != _head)
		{	/* The list is not empty */
			_head = _head->m_next;
		}
	}
	return _head;
}
/*
static Person* FindPlaceToInsert(Person* _head, int _key)
{
	while (NULL != *_currentP && _key >= *_currentP->m_id)
	{
		if (_key == *_currentP->m_id)
		{
			return _head;
		}
		*_previousP = *_currentP;
		*_currentP = *_currentP->m_next;
		if (NULL == *_currentP)
		{
			break;
		}
	}
}
*/

Person* GetTailRec(Person* _head)
{
	if (NULL == _head->m_next)
	{
		return _head;
	}
	return GetTailRec(_head->m_next);
}

Person* GetTail(Person* _head)
{
	if (NULL == _head)
	{
		return NULL;
	}
	return GetTailRec(_head);
}

Person* ListInsertByKey(Person* _head, int _key, Person* _p)
{
	Person* currentP  = _head;
	Person* previousP = NULL;
	
	if (NULL == _p)
	{
		return _head;
	}
	if (NULL == _head || _key < _head->m_id)
	{
		return ListInsertHead(_head, _p);
	}
	while (_key >= currentP->m_id)
	{
		if (_key == currentP->m_id)
		{
			return _head;
		}
		previousP = currentP;
		currentP = currentP->m_next;
		if (NULL == currentP)
		{
			break;
		}
	}
	previousP->m_next = _p;
	_p->m_next = currentP;
	
	return _head;
}

Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p)
{
	if (NULL == _p)
	{
		return _head;
	}
	if (_key == _head->m_id)
	{	/* Trying to insert a person that already exist */
		return _head;
	}
	if (NULL == _head || _key < _head->m_id)
	{
		_p->m_next = _head;
		return _p;
	}
	_head->m_next = ListInsertByKeyRec(_head->m_next, _key, _p);
	return _head;
}

static Person* Find(Person* _head, int _key)
{
	Person* currentP  = _head;
	Person* previousP = NULL;
	
	if (NULL != _head || _head->m_id == _key)
	{
		return NULL;
	}
	while (NULL != currentP && currentP->m_id <= _key)
	{
		if (currentP->m_id == _key)
		{
			return currentP;
		}			
		previousP = currentP;
		currentP = currentP->m_next;
	}	
}


Person* ListRemoveByKey(Person* _head, int _key, Person** _p)
{
	Person* currentP  = NULL;
	Person* previousP = _head;
	
	if (NULL == _p)
	{
		return _head;
	}	
	if (NULL != _head || _head->m_id == _key)
	{
		return ListRemoveHead(_head, _p);
	}
	while (NULL != currentP && currentP->m_id <= _key)
	{
		if (currentP->m_id == _key)
		{
			*_p = currentP;
			previousP->m_next = currentP->m_next;
			break;
		}
		previousP = currentP;
		currentP = currentP->m_next;
	}
	return _head;
}

Person* ListRemoveByKeyRec(Person* _head, int _key, Person** _p)
{
	if (NULL == _head)
	{	/* The list is empty. */
		return _head;
	}
	if (NULL == _head->m_next && _key > _head->m_id)
	{	/* The person wasn't found. */
		*_p = NULL;
		return _head;
	}
	if (_key == _head->m_id)
	{	/* The person was found. */
		return ListRemoveHead(_head, _p);
	}

	_head->m_next = ListRemoveByKeyRec(_head->m_next, _key, _p);

	return _head;
}

void PrintList(Person* _head)
{
	if (NULL == _head)
	{
		printf("The list is empty.\n");
	}
	while (NULL != _head)
	{
		printf("ID: %d, Name: %s, age: %d, next: ", _head->m_id, _head->m_name, _head->m_age);
		if (NULL != _head->m_next)
		{
			printf("%d\n", _head->m_next->m_id);
		}
		else
		{
			printf("NULL\n");
		}
		_head = _head->m_next;
	}
	printf("\n");
}



