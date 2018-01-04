#ifndef __MEM_POOL_T_H__
#define __MEM_POOL_T_H__

#include "MemManager_t.h"
#include "MemPage_t.h"

#include <vector>
using namespace std;


class MemPool_t : public MemManager_t
{
public:
	MemPool_t();
	virtual ~MemPool_t();		
	
	// unsigned int SetPosition(unsigned int _position);
	// unsigned int GetPosition() const;
	// unsigned int GetActualSize() const;
	// bool         IsEmpty() const;

	virtual unsigned int Write(const void* _src, size_t _nBytes);
	virtual unsigned int Write(const void* _src, size_t _nBytes, unsigned int _position);
	virtual unsigned int Read(void* _dest, size_t _nBytes);
	virtual unsigned int Read(void* _dest, size_t _nBytes, unsigned int _position);

private:
	MemPool_t(const MemPool_t& _memPool);
	MemPool_t & operator=(const MemPool_t& _memPool);
	
	void InsertNewPage();
	vector<MemPage_t*>::iterator GetPage(unsigned int _position);
	vector<MemPage_t*>::iterator GetNextPage(vector<MemPage_t*>::iterator _itr);
	
protected:
	vector<MemPage_t*> m_pool;
};


#endif /* __MEM_POOL_T_H__ */

