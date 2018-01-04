#ifndef __MY_HANDLER_H__
#define __MY_HANDLER_H__

#include "IHandler.h"
#include "Socket.h"

namespace net
{


class MyHandler : public IHandler
{
public:
    virtual ~MyHandler();
    
    virtual void MyHandler();

    virtual std::tr1::shared_ptr<Socket> GetSocket() const;

private:
	std::tr1::shared_ptr<Socket> m_sock;
};


inline std::tr1::shared_ptr<Socket> MyHandler::GetSocket() const
{
	return m_sock;
}




}   // namespace net

#endif // __MY_HANDLER_H__



