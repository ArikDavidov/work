#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "ADTErr.h"

typedef struct Queue Queue;

Queue*  QueueCreate(size_t _size);
void    QueueDestroy(Queue* _queue);
ADTErr  QueueInsert(Queue* _queue, int _item);
ADTErr  QueueRemove(Queue* _queue, int* _item);
int     QueueIsEmpty(Queue* _queue);
void    QueuePrint(Queue* _queue);

#endif /* #ifndef __QUEUE_H__ */

/*
void TestCreate();
void TestCreateZeroSize();

void TestInsert();
void TestInsertNULL();

void TestIsEmptyAfterCreate();
void TestIsEmptyWhenNotEmpty();
void TestIsEmptyQueueNULL();

void TestRemove();
void TestRemoveTooMuch();
void TestRemoveQueueNULL();
void TestRemoveItemPtrNULL();

void TestRemoveAndInsertSeveralTimes();
*/
