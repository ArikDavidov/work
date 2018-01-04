#ifndef __MEM_MANAGER_T_H__
#define __MEM_MANAGER_T_H__

#include <cstddef>	// size_t

class MemManager_t
{
public:
	MemManager_t();
	virtual ~MemManager_t();

	unsigned int SetPosition(unsigned int _position);
	unsigned int GetPosition() const;
	unsigned int GetActualSize() const;
	bool         IsEmpty() const;
	
	virtual unsigned int Write(const void* _src, size_t _nBytes) = 0;
	virtual unsigned int Write(const void* _src, size_t _nBytes, unsigned int _position) = 0;
	virtual unsigned int Read(void* _dest, size_t _nBytes) = 0;
	virtual unsigned int Read(void* _dest, size_t _nBytes, unsigned int _position) = 0;
	
private:
	MemManager_t(const MemManager_t& _memManager);
	MemManager_t & operator=(const MemManager_t& _memManager);

protected:
	unsigned int m_position;
	unsigned int m_actualSize;
};

	
inline unsigned int MemManager_t::GetPosition() const
{
	return m_position;
}

inline unsigned int MemManager_t::GetActualSize() const
{
	return m_actualSize;
}

inline bool MemManager_t::IsEmpty() const
{
	return (0 == m_actualSize);
}


#endif /* __MEM_MANAGER_T_H__ */


