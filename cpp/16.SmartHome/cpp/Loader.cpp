#include "Loader.h"

#include <dirent.h>
#include <dlfcn.h>
#include <iostream>
#include <cassert>


Loader::Loader()
{
}

Loader::~Loader()
{
    std::map<std::string, void*>::iterator it;
    for (it = m_handles.begin(); it != m_handles.end(); ++it)
    {
        dlclose(it->second);
    }
}

void Loader::ObtainSupportedTypes()
{
    DIR* dirp;
    struct dirent* dp;

//  dirp = opendir(s_folder);
    dirp = opendir("./SO");
    assert(dirp);
    
    while (0 != (dp = readdir(dirp)))
    {
        // Skipping '..' and '.' enteries
        if (DT_DIR == dp->d_type)
        {
            continue;
        }

        std::cout << dp->d_name << std::endl;
        
//      ObtainFromFile(s_folder + "/" + dp->d_name);
        ObtainFromFile(std::string("./SO/") + dp->d_name);
    }

    closedir(dirp);
}


void Loader::ObtainFromFile(const std::string& _path)
{
    void* handle = dlopen(_path.c_str(), RTLD_LAZY);
    if(!handle)
    {
        std::cerr << dlerror() << std::endl;
        return;
    }

    GetNextSupportedFunc GetNext = 
            (GetNextSupportedFunc)dlsym(handle, "GetNextSupportedType");

    std::pair<iter_t,bool> ret;
    std::string nextType;
    
    while ((nextType = GetNext()) != "")
    {
        ret = m_filePaths.insert(std::pair<std::string, 
                                 std::string>(nextType, _path));
        if (!ret.second)
        {
            std::cerr << "Type \"" << ret.first->first 
                      << "\" already supported in " << ret.first->second 
                      << std::endl;
        }
    }

    dlclose(handle);
}

void* Loader::GetHandle(const std::string& _type)
{
    iter_t pathIter = m_filePaths.find(_type);
    if (pathIter == m_filePaths.end())
    {
        std::cerr << "Error: type " << _type 
                  << " is not supported." << std::endl;
        return 0;
    }
    
    // Chek if already open
    std::map<std::string, void*>::iterator handleIter;
    handleIter = m_handles.find(pathIter->second);
    if (handleIter != m_handles.end())
    {
        return handleIter->second;
    }
//  m_handle = dlopen(("SO/" + it->second).c_str(), RTLD_LAZY);
    void* handle = dlopen(pathIter->second.c_str(), RTLD_LAZY);
    if(!handle)
    {
        std::cerr << dlerror() << std::endl;
        return 0;
    }

    m_handles[pathIter->second] = handle;

    return handle;
}


//void* Loader::GetHandle(const std::string& _type)
//{
//    
//    std::string path = GetPath(_type);
//    
//    void* handle = GetHandleIfAlreadyOpen(path);
//    if (handle)
//    {
//        return handle;
//    }

//    if(!(handle = dlopen(path.c_str(), RTLD_LAZY)))
//    {
//        std::cerr << dlerror() << std::endl;
//        return 0;
//    }

//    m_handles[path] = handle;

//    return handle;
//}

//const std::string& GetPath(const std::string& _type)
//{
//    iter_t pathIter = m_filePaths.find(_type);
//    if (pathIter == m_filePaths.end())
//    {
//        // TODO throw...
//        std::cerr << "Error: type " << _type 
//                  << " is not supported." << std::endl;
//    }
//    
//    return pathIter->second;
//}

//GetHandleIfAlreadyOpen(const std::string& _path)
//{
//    std::map<std::string, void*>::iterator handleIter;
//    handleIter = m_handles.find(pathIter->second);
//    if (handleIter != m_handles.end())
//    {
//        return handleIter->second;
//    }
//}


