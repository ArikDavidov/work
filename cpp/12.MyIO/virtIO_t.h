#ifndef __VIRTIO_H_H__
#define __VIRTIO_H_H__

#include <string>
#include <cstdio>
using namespace std;


class virtIO_t
{
public:
    typedef enum FileStatus {
        ok_e,
        cant_open_file_e,
        bad_access_e,
        writeErr_e,
        readErr_e
    } FileStatus;
    
    virtIO_t();
    virtIO_t(const string& _path, const string& _mode);
    virtual ~virtIO_t() = 0;
    
    virtual FileStatus Open(const string& _path, const string& _mode);
    virtual void Close();
    
    virtual virtIO_t& operator<<(char _output) = 0;
    virtual virtIO_t& operator<<(unsigned char _output) = 0;
    virtual virtIO_t& operator<<(short _output) = 0;
    virtual virtIO_t& operator<<(unsigned short _output) = 0;
    virtual virtIO_t& operator<<(int _output) = 0;
    virtual virtIO_t& operator<<(unsigned int _output) = 0;
    virtual virtIO_t& operator<<(long _output) = 0;
    virtual virtIO_t& operator<<(unsigned long _output) = 0;
    virtual virtIO_t& operator<<(float _output) = 0;
    virtual virtIO_t& operator<<(double _output) = 0;
    
    virtual virtIO_t& operator>>(char& _dest) = 0;
    virtual virtIO_t& operator>>(unsigned char& _dest) = 0;
    virtual virtIO_t& operator>>(short& _dest) = 0;
    virtual virtIO_t& operator>>(unsigned short& _dest) = 0;
    virtual virtIO_t& operator>>(int& _dest) = 0;
    virtual virtIO_t& operator>>(unsigned int& _dest) = 0;
    virtual virtIO_t& operator>>(long& _dest) = 0;
    virtual virtIO_t& operator>>(unsigned long& _dest) = 0;
    virtual virtIO_t& operator>>(float& _dest) = 0;
    virtual virtIO_t& operator>>(double& _dest) = 0;
    
    bool   IsFileOpen() const                   { return (0 == m_pFile); }
    long   GetLength() const;
    string GetPath() const                      { return m_path; }
    string GetMode() const                      { return m_mode; }
    FileStatus GetFileStatus() const            { return m_fStatus; }

protected:    
    void   SetFileStatus(FileStatus _status)	{ m_fStatus = _status; }
    void   ChekIfReadable() const;
    void   ChekIfWritable() const;

protected:
    FILE*      m_pFile;
    FileStatus m_fStatus;

private:
	virtIO_t(const virtIO_t& _io);
    virtIO_t& operator=(const virtIO_t& _io);

private:
    string m_path;
    string m_mode;
};


#endif /* __VIRTIO_H_H__ */

