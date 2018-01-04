#ifndef __BUFFER_T_H__
#define __BUFFER_T_H__


class Buffer_t
{
public:
	Buffer_t (unsigned int _capacity = m_defaultCapacity);
	Buffer_t(const char* _src, unsigned int _len, unsigned int _destOffset = 0);
	Buffer_t(const Buffer_t& _buf);
	~Buffer_t();
	
	const char* GetBuf() const;

	const char operator[](const unsigned int _i) const;
	char & operator[](const unsigned int _i);
	
	static float GetGrowthFactor();
	static float SetGrowthFactor(float _growthFactor);
	static unsigned int GetDefaultCapacity();
	static unsigned int SetDefaultCapacity(unsigned int _defaultCapacity);
	
private:
	const  char* m_buf;

	unsigned int CalculateCapacity(_numOfChars);
	static unsigned int m_defaultCapacity;
	static float m_growthFactor;	//recomended: between 1.3 and 1.5

protected:
	unsigned int m_numOfChars;
	unsigned int m_capacity;
};


inline const char* Buffer_t::GetBuf() const
{
	return m_buf;
}




#endif /* __BUFFER_T_H__ */




