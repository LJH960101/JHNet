#include "Singleton.h"
#include <thread>
#include <boost/asio.hpp>

class CSocketNetwork{
    DEFINE_SINGLETON(CSocketNetwork);

public:
    bool Start(u_int16_t port_);

private:
    void _SocketThread(u_int16_t port_);
  
    std::thread* m_iocpThread = nullptr;
    boost::asio::io_context m_ioContext;
};