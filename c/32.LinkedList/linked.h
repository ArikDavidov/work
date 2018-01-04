#ifndef __LINKED_H__
#define __LINKED_H__

#define NAME_SIZE 128

typedef struct Person Person;

struct Person
{
	int 	m_id;
	char 	m_name[NAME_SIZE];
	int 	m_age;
	Person* m_next;
};

Person * ListInsertHead(Person* _head, Person* _p);
/*
Function that inserts a person to the first position in a list.
Parameters:
	_head - Pointer to the first person in a list. Can be NULL if the list is empty.
	_p    - Pointer to the person to insert. If the pointer is NULL no insertion will be done.
Returns:
	Person* - Pointer to the new first person in the list.
*/
Person * ListRemoveHead(Person* _head, Person** _item);
/*
Function that removes the first person from a list.
Parameters:
	_head - Pointer to the first person in a list.
	_key  - Person's ID.
	_p    - Double pointer that will store the deleted person.
Returns:
	Person* - Pointer to the new first person in the list.
	NULL    - If the list was empty.
			- If the list became empty after the removal.
*/
Person * ListInsertByKey(Person* _head, int _key, Person* _p);
/*
Iterative function that inserts a person to a list by its ID.
The function assumes the list is sorted by ID.
If a person whith the same ID already exists in the list no insertion will be done.
Parameters:
	_head - Pointer to the first person in a list. Can be NULL if the list is empty.
	_key  - Person's ID	
	_p    - Pointer to the person to insert.
Returns:
	Person* - Pointer to the new first person in the list whether the insertion was done or not.
*/
Person * ListInsertByKeyRec(Person* _head, int _key, Person* _p);
/*
Rucursive function that inserts a person to a list by its ID.
The function assumes the list is sorted by ID.
If a person whith the same ID already exists in the list no insertion will be done.
Parameters:
	_head - Pointer to the first person in a list. Can be NULL if the list is empty.
	_key  - Person's ID	
	_p    - Pointer to the person to insert.
Returns:
	Person* - Pointer to the new first person in the list whether the insertion was done or not.
*/
Person * ListRemoveByKey(Person* _head, int _key, Person** _p);
/*
Iterative function that finds a person in a list by his ID and removes him from the list.
The function assumes the list is sorted by ID.
Parameters:
	_head - Pointer to the first person in a list.
	_key  - Person's ID.
	_p    - Double pointer that will store the deleted person.
Returns:
	Person* - Pointer to the first person in a list whether the person was found and removed or not.
	NULL    - If the list was empty.
			- If the list became empty after the removal.
*/
Person * ListRemoveByKeyRec(Person* _head, int _key, Person** _p);
/*
Rucurcive function that finds a person in a list by his ID and removes him from the list.
The function assumes the list is sorted by ID.
Parameters:
	_head - Pointer to the first person in a list.
	_key  - Person's ID.
	_p    - Double pointer that will store the deleted person.
Returns:
	Person* - Pointer to the first person in a list whether the person was found and removed or not.
	NULL    - If the list was empty.
			- If the list became empty after the removal.
*/
void 	PrintList(Person * _head);
#endif /* endif __LINKED_H__ */
