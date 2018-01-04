#include <stdio.h>
#include "linked.h"

int main()
{
	Person* head = NULL;
	Person* item = NULL;
	Person p1 = {123, "Yosi", 25, NULL};
	Person p2 = {196, "Avi", 45, NULL};
	Person p3 = {398, "Bar", 20, NULL};
	
	head = 	ListInsertHead(head, &p1);
	printf("Inserted person: %d\n", p1.m_id);
	PrintList(head);

	head = ListRemoveHead(head, &item);
	printf("Removed person: %d\n", item->m_id);
	PrintList(head);
	
	head = 	ListInsertHead(head, &p2);
	printf("Inserted person: %d\n", p2.m_id);
	PrintList(head);

	head = ListInsertByKeyRec(head, 123, &p1);
	printf("Inserted person: %d\n", p1.m_id);
	PrintList(head);

	head = ListInsertByKeyRec(head, 398, &p3);
	printf("Inserted person: %d\n", p3.m_id);
	PrintList(head);
	
	/*head = GetTail(head);
	printf("Inserted person: %d\n", p3.m_id);
	PrintList(head);	
	*/
	head = ListRemoveByKeyRec(head, 196, &item);
	printf("Removed person ID: %d\n", item->m_id);
	PrintList(head);

			
	return 0;
}
