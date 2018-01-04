#ifndef __BIT_SET_H__
#define __BIT_SET_H__

#include "Functors.h"

#include <climits>      // CHAR_BIT
#include <cstddef>      // std::size_t
#include <stdexcept>    // std::runtime_error
#include <cstring>      // std::memset
#include <algorithm>    // std::transform
#include <numeric>      // std::accumulate
#include <iostream>

namespace advcpp
{

template <std::size_t SIZE, typename T = unsigned int>
class BitSet
{
private:
    static const std::size_t NUM_BITS      = SIZE;
    static const std::size_t BITS_IN_TYPE  = sizeof(T)* CHAR_BIT;
    static const std::size_t ARRAY_SIZE    = SIZE / BITS_IN_TYPE
                                           + ((SIZE % BITS_IN_TYPE) ? 1: 0);
public:
    class Reference {
    public:
        explicit Reference(T& _t, std::size_t _offset);
        Reference(const Reference&);
        Reference& operator=(const Reference& _ref);
        Reference& operator=(bool _val);
        bool operator==(bool _val);
        bool operator==(const Reference& _ref);
        operator bool() const;

    private:        
        T&          m_arrayElement;
        std::size_t m_offset;
    };
    
    explicit BitSet();
    explicit BitSet(const bool* _boolArray);
    
    ~BitSet();
    BitSet(const BitSet& _bs);
    BitSet& operator=(const BitSet& _bs);
    
    std::size_t Count() const;
    BitSet& Flip();
    bool Any() const;
    bool All() const;
    bool None() const;
    bool IsBitOn(std::size_t _pos) const;       // throws out_of_range
    void Set(std::size_t _pos, bool _val);      // throws out_of_range

    BitSet& operator<<=(std::size_t _offset);
    BitSet& operator>>=(std::size_t _offset);
    BitSet& operator&=(const BitSet& _bs);
    BitSet& operator|=(const BitSet& _bs);
    BitSet& operator^=(const BitSet& _bs);
    bool    operator==(const BitSet& _bs);
    bool    operator!=(const BitSet& _bs);

    Reference operator[](std::size_t _pos);
    bool      operator[](std::size_t _pos) const;

    template <typename Operator>
    void DoOperator(const BitSet& _bs, Operator _op);
    
private:
    void SetBitsOutOfRangeToZero();
    void SetBitsOutOfRangeToOne();

    T* m_array; // * is better because swap is O(1)
};


template <size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::operator==(const BitSet& _bs)
{
    return std::equal(m_array, &m_array[ARRAY_SIZE], _bs.m_array);
}

template <size_t SIZE, typename T>
template <typename Operator>
inline void BitSet<SIZE, T>::DoOperator(const BitSet& _bs, Operator _op)
{
    std::transform(m_array, &m_array[ARRAY_SIZE], _bs.m_array, m_array, _op);
}

template <size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator|=(const BitSet& _bs)
{
    DoOperator(_bs, OperatorOr<T>());

    return *this;
}

template <size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator&=(const BitSet& _bs)
{
    DoOperator(_bs, OperatorAnd<T>());

    return *this;
}

template <size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator^=(const BitSet& _bs)
{
    DoOperator(_bs, OperatorXor<T>());

    return *this;
}

template <std::size_t SIZE, typename T>
std::ostream& operator<<(std::ostream& _os, const BitSet<SIZE, T>& _bs)
{
    for (std::size_t i = 0; i < SIZE; ++i)
    {
        std::cout << _bs[i];
    }

    return _os;
}

template <size_t SIZE, typename T>
inline BitSet<SIZE, T> operator|(const BitSet<SIZE, T>& _left,
                          const BitSet<SIZE, T>& _right)
{
    BitSet<SIZE, T> tmp(_left);

    tmp |= _right;
    
    return tmp;
}

template <size_t SIZE, typename T>
inline BitSet<SIZE, T> operator&(const BitSet<SIZE, T>& _left,
                          const BitSet<SIZE, T>& _right)
{
    BitSet<SIZE, T> tmp(_left);

    tmp &= _right;
    
    return tmp;
}

template <size_t SIZE, typename T>
inline BitSet<SIZE, T> operator^(const BitSet<SIZE, T>& _left,
                          const BitSet<SIZE, T>& _right)
{
    BitSet<SIZE, T> tmp(_left);

    tmp ^= _right;
    
    return tmp;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> operator<<(const BitSet<SIZE, T>& _bs,
                            std::size_t _offset)
{
    BitSet<SIZE, T> tmp(_bs);
    tmp <<= _offset;

    return tmp;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T> operator>>(const BitSet<SIZE, T>& _bs,
                            std::size_t _offset)
{
    BitSet<SIZE, T> tmp(_bs);
    tmp >>= _offset;

    return tmp;
}

template <size_t SIZE, typename T>
BitSet<SIZE, T> operator~(const BitSet<SIZE, T>& _bs)
{
    BitSet<SIZE, T> tmp(_bs);

    tmp.Flip();

    return tmp;
}

template <size_t SIZE, typename T>
bool BitSet<SIZE, T>::operator!=(const BitSet& _bs)
{
    return !(*this == _bs);
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>::Reference::Reference(T& _t, std::size_t _offset)
: m_arrayElement(_t)
, m_offset(_offset)
{
}

template <std::size_t SIZE, typename T>
inline BitSet<SIZE, T>::Reference::operator bool() const
{
    T mask = static_cast<T>(1) << m_offset;
    
    return m_arrayElement & mask;
}

template <std::size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::Reference::operator==(bool _val)
{
    return bool(*this) == _val;
}

template <std::size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::Reference::operator==
            (const Reference& _ref)
{
    return bool(*this) == bool(_ref);
}

template <std::size_t SIZE, typename T>
typename BitSet<SIZE, T>::Reference&
    BitSet<SIZE, T>::Reference::operator=(const Reference& _ref)
{
    return (*this = bool(_ref));
}

template <std::size_t SIZE, typename T>
typename BitSet<SIZE, T>::Reference&
    BitSet<SIZE, T>::Reference::operator=(bool _val)
{
    T mask = static_cast<T>(1) << m_offset;

    if (_val)
    {
        m_arrayElement |= mask;
    }
    else
    {
        m_arrayElement &= ~mask;
    }

    return *this;
}


template <std::size_t SIZE, typename T>
BitSet<SIZE, T>::BitSet()
{
    m_array = new T[ARRAY_SIZE];
    std::fill(m_array, &m_array[ARRAY_SIZE], 0);
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>::BitSet(const bool* _boolArray)
{
    m_array = new T[ARRAY_SIZE];
    std::fill(m_array, &m_array[ARRAY_SIZE], 0);

    std::copy(_boolArray, &_boolArray[ARRAY_SIZE], m_array);
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>::BitSet(const BitSet& _bs)
{
    m_array = new T[ARRAY_SIZE];
    std::copy(_bs.m_array, &_bs.m_array[ARRAY_SIZE], m_array);
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator=(const BitSet& _bs)
{
    std::copy(_bs.m_array, &_bs.m_array[ARRAY_SIZE], m_array);
    
    return *this;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>::~BitSet()
{
    delete[] m_array;
}

template <std::size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::IsBitOn(std::size_t _pos) const
{
    if (_pos >= SIZE)
    {
        throw std::runtime_error("out_of_range");
    }
    
    return (*this)[_pos];
}

template <std::size_t SIZE, typename T>
inline void BitSet<SIZE, T>::Set(std::size_t _pos, bool _val)
{
    if (_pos >= SIZE)
    {
        throw std::runtime_error("out_of_range");
    }
	
	(*this)[_pos] = _val;
}

template <std::size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::operator[](std::size_t _pos) const
{
    T element = m_array[_pos / BITS_IN_TYPE];
    T mask    = static_cast<T>(1) << (_pos % BITS_IN_TYPE);
    
    return element & mask;
}

template <std::size_t SIZE, typename T>
inline typename BitSet<SIZE, T>::Reference
        BitSet<SIZE, T>::operator[](std::size_t _pos)
{
    T& element         = m_array[_pos / BITS_IN_TYPE];
    std::size_t offset = _pos % BITS_IN_TYPE;
    
    return Reference(element, offset);
}

template <std::size_t SIZE, typename T>
std::size_t BitSet<SIZE, T>::Count() const
{
    return std::accumulate(m_array, &m_array[ARRAY_SIZE], 0, PopCount<T>());
}

template <std::size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::Any() const
{
    T* ret = std::find_if(m_array, &m_array[ARRAY_SIZE], NotZero<T>());
    
    return ret != &m_array[ARRAY_SIZE];
}

template <size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::None() const
{
    return !Any();
}

template <std::size_t SIZE, typename T>
inline bool BitSet<SIZE, T>::All() const
{
    const_cast<BitSet*>(this)->SetBitsOutOfRangeToOne();
    
    T* ret = std::find_if(m_array, &m_array[ARRAY_SIZE], NotAllPoped<T>());
    
    const_cast<BitSet*>(this)->SetBitsOutOfRangeToZero();

    return ret == &m_array[ARRAY_SIZE];
}

template <std::size_t SIZE, typename T>
inline BitSet<SIZE, T>& BitSet<SIZE, T>::Flip()
{
    
	std::for_each(m_array, &m_array[ARRAY_SIZE], DoFlip<T>());
   
    SetBitsOutOfRangeToZero();
    
    return *this;
}

template <std::size_t SIZE, typename T>
void BitSet<SIZE, T>::SetBitsOutOfRangeToOne()
{
    T mask = ~0;
    mask <<= SIZE % BITS_IN_TYPE
    	   + ((SIZE % BITS_IN_TYPE) ? 0 : BITS_IN_TYPE);
    m_array[ARRAY_SIZE - 1] |= mask; 
}

template <std::size_t SIZE, typename T>
void BitSet<SIZE, T>::SetBitsOutOfRangeToZero()
{
    T mask = ~0;
    mask >>= (BITS_IN_TYPE - (SIZE % BITS_IN_TYPE)
    					   - ((SIZE % BITS_IN_TYPE) ? 0 : BITS_IN_TYPE));
    m_array[ARRAY_SIZE - 1] &= mask;
}

template <std::size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator<<=(std::size_t _offset)
{
    for (std::size_t i = SIZE - _offset - 1; i < SIZE; --i)
    {
        (*this)[i + _offset] = (*this)[i];
    }
    
    for (std::size_t i = 0; i < _offset; ++i)
    {
        (*this)[i] = false;
    }
    
    return *this;
}
    
template <std::size_t SIZE, typename T>
BitSet<SIZE, T>& BitSet<SIZE, T>::operator>>=(std::size_t _offset)
{
    for (std::size_t i = _offset; i < SIZE; ++i)
    {
        (*this)[i - _offset] = (*this)[i];
    }
    
    for (std::size_t i = SIZE - _offset; i < SIZE; ++i)
    {
        (*this)[i] = false;
    }
    
    return *this;
}


}   // namespace advcpp

#endif // __BIT_SET_H__


