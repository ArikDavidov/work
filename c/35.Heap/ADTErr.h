#ifndef __ADTERR_H__
#define __ADTERR_H__

typedef enum
{
    ERR_OK              =0,
    ERR_GENERAL,
    ERR_NOT_INITIALIZED,
    ERR_ALLOCATION_FAILED,
    ERR_REALLOCATION_FAILED,
    ERR_UNDERFLOW,
    ERR_OVERFLOW,
    ERR_TREE_IS_EMPTY,
    ERR_VALUE_ALREADY_EXIST,
    ERR_VECTOR_IS_FULL,
    ERR_STACK_BBBBB = 30

} ADTErr;

#endif /* #ifndef __ADTERR_H__ */



/*
typedef struct{
    int   m_data:
    Node* m_left;
    Node* m_right;
    Node* m_father;
} Node;
*/

