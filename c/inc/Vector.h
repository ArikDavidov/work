#ifndef __VECTOR_H__
#define __VECTOR_H__

/** 
 * @brief Create a Generic Vector data type
 * that stores pointer to user provided elements of generic type
 * The Vector is heap allocated and can grow and shrink on demand.
 * 
 * @author Ariel Davidov (arik.davidov@gmail.co.il) 
 */ 

#include <stddef.h>  /* size_t */

typedef enum
{
    VECTOR_OK,		
    VECTOR_NOT_INITIALIZED,
    VECTOR_ALLOCATION_FAILED,
    VECTOR_REALLOCATION_FAILED,
    VECTOR_OVERFLOW,
    VECTOR_VECTOR_IS_FULL
} VectorErr;

typedef struct Vector Vector;
typedef int	(*VectorElementAction)(void* _element, size_t _index, void* _context);

/**  
 * @brief Dynamically create a new vector object of given capacity and  
 * @param[in] _initialCapacity - initial capacity, number of elements that can be stored initially
 * @param[in] _blockSize - the vector will grow or shrink on demand by this size 
 * @return Vector * - on success / NULL on fail 
 *
 * @warning if _blockSize is 0 the vector will be of fixed size.
 * @warning if both _initialCapacity and _blockSize are zero function will return NULL.
 */
Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize);

/**  
 * @brief Dynamically deallocate a previously allocated vector.
 * @param[in] _vec - Vector to be deallocated.
 * @params[in] _elementDestroy : A function pointer to be used to destroy all elements in the vector
 *             or a null if no such destroy is required
 * @return void
 */
void VectorDestroy(Vector** _vec, void (*_elementDestroy)(void* _item));

/**  
 * @brief Add an Item to the back of the Vector.
 * The vector will grow by one block size if num of elements reachet the capacity.
 * @param[in] _vec - Vector to append integer to.
 * @param[in] _item - Item to add.
 * @return success or error code 
 * @retval VECTOR_OK on success
 * @retval VECTOR_NOT_INITIALIZED if one of the parameters is null.
 * @retval VECTOR_VECTOR_IS_FULL if the number of elements reached the capacity of the vector
 *         and the vector is of fixed size.
 * @retval VECTOR_REALLOCATION_FAILED if the vector failed to grow when the number of elements 
 *         reached the capacity of the vector.
 */
VectorErr VectorAppend(Vector* _vec, void* _item);

/**  
 * @brief Delete an Element from the back of the Vector.
 * The vector will shrink by one block size if the capaity exides the num of items
 * by at least 2 block sizes.
 * The vector will not shrink below it's original capacity.
 * @param[in] _vec - Vector to delete element from.
 * @param[out] _item - pointer to variable that will receive deleted item value.
 * @return success or error code
 * @retval VECTOR_OK on success
 * @retval VECTOR_NOT_INITIALIZED if one of the parameters is null.
 * 
 * @warning _item can't be null. this will be assertion violation
 */
VectorErr VectorRemove(Vector* _vec, void** _item);

/**  
 * @brief Get value of item at specific index from the the Vector 
 * @param[in] _vec - Vector to use.
 * @param[in] _index - index of item to get value from.
 * @param[out] _item - pointer to variable that will recieve the item's value.
 * @return success or error code 
 * @retval VECTOR_OK on success
 * @retval VECTOR_NOT_INITIALIZED if one of the parameters is null.
 * @retval VECTOR_OVERFLOW if the index is of non existing item.
 */
VectorErr VectorGet(const Vector* _vec, size_t _index, void** _item);

/**  
 * @brief Set an item at specific index to a new value.
 * @param[in] _vec - Vector to use.
 * @param[in] _index - index of an existing item.
 * @param[in] _item - new value to set.
 * @return success or error code
 * @retval VECTOR_OK on success
 * @retval VECTOR_NOT_INITIALIZED if one of the parameters is null.
 * @retval VECTOR_OVERFLOW if the index is of non existing item.
 *
 * @warning The function doesn't destroy the element being overwritten. If the element
  *         is no longer needed, the user must get and destroy it befor the VectorSet.
 */
VectorErr VectorSet(Vector* _vec, size_t _index, void* _item);

/**  
 * @brief Get the number of actual items currently in the vector.
 * @param[in] _vec - Vector to use.
 * @return number of items on success, 0 if vector is empty or invalid.
 */
size_t VectorSize(const Vector* _vec);

/**  
 * @brief Get the current capacity of the vector.
 * @param[in] _vec - Vector to use.
 * @return capacity of vector on success, 0 if vector is invalid.
 */
size_t VectorCapacity(const Vector* _vec);


#endif /* #ifndef __VECTOR_H__ */

