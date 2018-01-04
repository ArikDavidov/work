#include "Dispatcher.h"


Dispatcher::Dispatcher()
{
}

Dispatcher::~Dispatcher()
{
}

Dispatcher::RegisterHandler(std::tr1::shared_ptr<IHandler> _handler)
{
    m_handlers.insert(_handler.GetSocket(), _handler);
}


