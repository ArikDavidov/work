#ifndef __MEM_PAGE_T_H__
#define __MEM_PAGE_T_H__

#include "MemManager_t.h"


//#include <cstddef>

class MemPage_t : public MemManager_t
{
public:
	MemPage_t();
	virtual ~MemPage_t();
	
	// unsigned int SetPosition(unsigned int _position);
	// unsigned int GetPosition() const;
	// unsigned int GetActualSize() const;
	// bool         IsEmpty() const;
	
	bool IsFull() const;
	unsigned int GetCapacity() const;
	
	static unsigned int SetDefaultCapacity(unsigned int _defaultCapacity);
	static unsigned int GetDefaultCapacity();
	
	virtual unsigned int Write(const void* _src, size_t _nBytes);
	virtual unsigned int Write(const void* _src, size_t _nBytes, unsigned int _position);
	virtual unsigned int Read(void* _dest, size_t _nBytes);
	virtual unsigned int Read(void* _dest, size_t _nBytes, unsigned int _position);
	
private:
	MemPage_t(const MemPage_t& _memPage);
	MemPage_t & operator=(const MemPage_t& _memPage);

protected:
	char*        		m_page;
	unsigned int 		m_capacity;
	static unsigned int m_defaultCapacity;
};


inline bool MemPage_t::IsFull() const
{
	return (m_capacity == m_actualSize);
}

inline unsigned int MemPage_t::GetCapacity() const
{
	return m_capacity;
}



#endif /* __MEM_PAGE_T_H__ */




