#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

#define MAGIC_NUM 4121996

typedef struct Node Node;

struct Node
{
    int   m_data;
    Node* m_left;
    Node* m_right;
    Node* m_father;
};

struct Tree
{
	Node* m_root;
	size_t m_magicNum;	
};

Tree* TreeCreate()
{
	Tree* tree = NULL;
	
	tree = malloc(sizeof(Tree));
	if (NULL == tree)
	{
		return NULL;
	}

	tree->m_root = NULL;
	tree->m_magicNum = MAGIC_NUM;

	return tree;
}

static void DestroyNodes(Node* _node)
{
	if (NULL == _node)
	{
		return;
	}

	DestroyNodes(_node->m_left);	
	DestroyNodes(_node->m_right);
	free(_node);
}

void TreeDestroy(Tree* _tree)
{
	if (NULL == _tree || MAGIC_NUM != _tree->m_magicNum)
	{
		return;
	}

	DestroyNodes(_tree->m_root);
	_tree->m_magicNum = 0;
	free(_tree);
}

static Node* CreateNode(int _data)
{
	Node* node;

	node = calloc(1, sizeof(Node));
	if (NULL == node)
	{
		return NULL;
	}
	
	node->m_data = _data;		

	return node;
}

static Node* FindPlaceInTree(Node* _node, int _data)
{
	Node* res = _node;

	if (NULL == _node || _node->m_data == _data)
	{ /* The node was found */
		return res;
	}

	if(_data < _node->m_data)
	{
		/* If smaller than current node - go left */
		return FindPlaceInTree(_node->m_left, _data);
	}
	/* If bigger than current node - go right */
	return FindPlaceInTree(_node->m_right, _data);
}

static ADTErr InsertNodeToPlace(Node* _place, Node* _node)
{
	if (_place->m_data == _node->m_data)
	{		
		free(_node);
		return ERR_VALUE_ALREADY_EXIST;
	}

	_node->m_father = _place;
	if (_node->m_data < _place->m_data)
	{
		_place->m_left  = _node;
	}
	else
	{
		_place->m_right = _node;
	}

	return ERR_OK;
}

ADTErr TreeInsert(Tree* _tree, int _data)
{
	Node* node = NULL;
	Node* place = NULL;
	ADTErr res = ERR_OK;
	
	if (NULL == _tree)
	{
		return ERR_NOT_INITIALIZED;
	}
	node = CreateNode(_data);
	if (NULL == node)
	{
		return ERR_ALLOCATION_FAILED;
	}

	if (NULL == _tree->m_root)
	{ /* The tree is empty */
		_tree->m_root = node;
	}
	else
	{
		place = FindPlaceInTree(_tree->m_root, _data);
		res = InsertNodeToPlace(place, node);
	}

	return res;
}

int TreeIsDataFound(Tree* _tree, int _data)
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

void TreePrint(Tree* _tree, TreeTransverse _transverseMode)
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






