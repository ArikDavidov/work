#ifndef __LOADER_H__
#define __LOADER_H__

// #include "SmartHomeAPI.h"

#include <string>
#include <map>


class Loader
{
public:
	typedef std::string (*GetNextSupportedFunc)();
	typedef std::map<std::string, std::string>::iterator iter_t;

	explicit Loader();
	virtual ~Loader();

	void  ObtainSupportedTypes();
	void* GetHandle(const std::string& _type);

protected:
	void ObtainFromFile(const std::string& _path);
	
private:
	Loader(const Loader&);
	Loader& operator=(const Loader&);

private:
	std::map<std::string, std::string> m_filePaths;
	std::map<std::string, void*>       m_handles;
	std::string                        m_prevType;
//	void*                              m_handle;
};


#endif	// __LOADER_H__



