#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include "ADTErr.h"

typedef enum
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
} TreeTransverse;

typedef struct Tree Tree;

Tree*  TreeCreate();
void   TreeDestroy(Tree* _tree);
ADTErr TreeInsert(Tree* _tree, int data);
int    TreeIsDataFound(Tree* _tree, int _data);
void   TreePrint(Tree* _tree, TreeTransverse _transverseMode);

#endif /* #ifndef __BINARY_TREE_H__ */

