#include "Tree.h"

#include <stdio.h>
#include <stdlib.h>

/* #define NDEBUG 1 */
#include <assert.h>

#define TREE_MAGIC 0xBAD33333

#define IS_A_TREE(T)		((T) && TREE_MAGIC == (T)->m_magic)
#define IS_A_SENTINEL(N)	((N)->m_parent == (N))
#define ROOT(T)				((T)->m_sentinel.m_left)

typedef struct Node Node;

struct Node
{
    void* m_data;
    Node* m_left;
    Node* m_right;
    Node* m_parent;
};

struct BSTree
{
	size_t	m_magic;
	Node	m_sentinel;
	LessComparator	m_less;
};

BSTree* BSTreeCreate(LessComparator _less)
{
	BSTree* tree = NULL;
	
	if (NULL == _less)
	{
		return NULL;
	}
	
	tree = malloc(sizeof(BSTree));
	if (NULL == tree)
	{
		return NULL;
	}

	tree->m_magic = TREE_MAGIC;
	tree->m_less = _less;
	
	tree->m_sentinel.m_right = NULL;
	tree->m_sentinel.m_left = NULL;
	tree->m_sentinel.m_parent = &tree->m_sentinel;	
	
	return tree;
}

static void NodesFree(Node* _node)
{
	assert(_node);
	
	if (IS_A_SENTINEL(_node))
	{
		return;
	}

	NodesFree(_node->m_left);
	NodesFree(_node->m_right);
	
	free(_node);
}

static void NodesDestroyAndFree(Node* _node, void (*_destroyer)(void*))
{
	assert(_node);
	assert(_destroyer);
	
	if (IS_A_SENTINEL(_node))
	{
		return;
	}
	
	NodesDestroyAndFree(_node->m_left, _destroyer);
	NodesDestroyAndFree(_node->m_right, _destroyer);
	
	_destroyer(_node->m_data);
	free(_node);
}

void BSTreeDestroy(BSTree* _tree, void (*_destroyer)(void*))
{
	if (!IS_A_TREE(_tree))
	{
		return;
	}
	
	if (NULL != ROOT(_tree)) /* The tree is not empty */
	{
		if (!_destroyer) /* No need to destroy data */
		{
			NodesFree(_tree->m_sentinel.m_left);
		}
		else
		{
			NodesDestroyAndFree(_tree->m_sentinel.m_left, _destroyer);
		}	
	}

	_tree->m_magic = 0;
	free(_tree);
}

static Node* CreateNode(BSTree* _tree, void* _data)
{
	Node* node;
	
	assert(_tree);

	node = malloc(sizeof(Node));
	if (!node)
	{
		return NULL;
	}
	
	node->m_data = _data;
	
	node->m_left  = &_tree->m_sentinel;
	node->m_right = &_tree->m_sentinel;

	return node;
}

static int Insert(BSTree* _tree, Node*_node, Node* _currentNode)
{
	assert(_tree);
	assert(_node);
	assert(_currentNode);
	
	if (IS_A_SENTINEL(_currentNode))
	{
		return 0;
	}

	_node->m_parent = _currentNode;

	if(_tree->m_less(_node->m_data, _currentNode->m_data))
	{
		if (!Insert(_tree, _node, _currentNode->m_left))
		{
			_currentNode->m_left = _node;
		}
		return 1;
	}
	
	if (!Insert(_tree, _node, _currentNode->m_right))
	{
		_currentNode->m_right = _node;
	}
	
	return 1;
}

BSTreeItr BSTreeInsert(BSTree* _tree, void* _item)
{
	Node* node = NULL;
	
	if (!IS_A_TREE(_tree))
	{
		return NULL;
	}

	node = CreateNode(_tree, _item);
	if (NULL == node)
	{
		return &_tree->m_sentinel;
	}

	if (!ROOT(_tree))	/* The tree is empty */
	{
		ROOT(_tree) = node;
		node->m_parent = ROOT(_tree);
	}
	else
	{
		Insert(_tree, node, ROOT(_tree));
	}
	
	return node;
}

/*

int TreeIsDataFound(Tree* _tree, void* _data)
{
	Node* node = NULL;
	int res = 0;
	
	if (NULL != _tree && NULL != _tree->m_root)
	{
		node = FindPlaceInTree(_tree->m_root, _data);
		if (_data == node->m_data)
		{
			res = 1;
		}
	}
	return res;
}

void TreePrintPreOrder(Node* _node)
{
	if (NULL == _node)
	{
		return;
	}

	printf(" %d", _node->m_data);
	TreePrintPreOrder(_node->m_left);	
	TreePrintPreOrder(_node->m_right);
}

void TreePrintInOrder(Node* _node)
{
	if (NULL == _node)
	{
		return;
	}

	TreePrintInOrder(_node->m_left);	
	printf(" %d", _node->m_data);
	TreePrintInOrder(_node->m_right);
}

void TreePrintPostOrder(Node* _node)
{
	if (NULL == _node)
	{
		return;
	}

	TreePrintPostOrder(_node->m_left);	
	TreePrintPostOrder(_node->m_right);
	printf(" %d", _node->m_data);
}
void	ForEach(Tree* _tree, TreeTransverse _transverseMode, TreeActionFunction _action, void* _context);
{
	if (NULL != _tree)
	{
		printf("No tree was found.\n");
	}
	if (NULL != _tree->m_root)
	{
		printf("Tree is empty.\n");
	}

	switch(_transverseMode)
	{
		case PRE_ORDER:
			TreePrintPreOrder(_tree->m_root);		break;
		case IN_ORDER:
			TreePrintInOrder(_tree->m_root);		break;
		case POST_ORDER:
			TreePrintPostOrder(_tree->m_root);		break;
	}
	printf("\n");
}
 */

/** 
 * @brief Performs an action function on every element in tree, by given traversal mode
 * @details iteration will stop on the first element for which the action function returns a zero
 * or on reaching end of the conrainer
 *
 * @params _tree : tree to iterate over
 * @params _mode : Traversal mode - TREE_TRAVERSAL_PREORDER, TREE_TRAVERSAL_INORDER or TREE_TRAVERSAL_POSTORDER
 * @params _action : Action function to call for each element
 * @params _context : Context for the _action function
 * @return Iterator refering to the tree end or the element where iteration stopped
 * BSTreeItr BSTreeForEach(const BSTree* _tree, TreeTraversalMode _mode,
                 ActionFunction _action, void* _context)
 */








