#include "SocketNetwork.h"
#include "Log.h"

#include <thread>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/optional.hpp>

#include <iostream>

IMPLEMENT_SINGLETON(CSocketNetwork);

using boost::asio::ip::tcp;
using namespace std;
 
class CIOCPSession
{
public:
  CIOCPSession(boost::asio::io_context& ioContext_)
    : m_socket(ioContext_)
  {
  }
 
  tcp::socket& GetSocket()
  {
    return m_socket;
  }
 
  void ProcRead()
  {
    m_socket.async_read_some(boost::asio::buffer(m_Receivebuf, MAX_BUF_LENGTH),
        boost::bind(&CIOCPSession::_OnRead, this, 
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
  }

  void ProcWrite(uint32_t size_)
  {
    m_socket.async_write_some(boost::asio::buffer(m_Sendbuf, size_),
        boost::bind(&CIOCPSession::_OnWrite, this,
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
  }
 
private:
  void _OnRead(const boost::system::error_code error_, size_t length_)
  {
    if (!error_)
    {
      cout << "Receive Complete : " << m_Receivebuf << endl;
      ProcRead();
    }
    else
    {
      delete this;
    }
  }

  void _OnWrite(const boost::system::error_code error_, size_t length_)
  {
    if (!error_)
    {
      cout << "Send Complete : " << m_Sendbuf << endl;
    }
    else
    {
      delete this;
    }
  }
 
  enum { MAX_BUF_LENGTH = 1024 };
  tcp::socket m_socket;
  char m_Receivebuf[MAX_BUF_LENGTH];
  char m_Sendbuf[MAX_BUF_LENGTH];
};
 
class CIOCPAcceptor
{
public:
  CIOCPAcceptor(boost::asio::io_context& ioContext_, short port_)
    : m_ioContext(ioContext_),  m_acceptor(ioContext_, tcp::endpoint(tcp::v4(), port_))
  {
    _ProcAccept();
  }
 
private:
  void _ProcAccept()
  {
    CIOCPSession* newSeesion = new CIOCPSession(m_ioContext);
    m_acceptor.async_accept(newSeesion->GetSocket(),
      boost::bind(&CIOCPAcceptor::_OnAccept, this, newSeesion, boost::asio::placeholders::error));
  }
 
  void _OnAccept(CIOCPSession* newSession_, const boost::system::error_code& error_)
  {
    if (!error_)
    {
      newSession_->ProcRead();
    }
    else
    {
      delete newSession_;
    }
    
    _ProcAccept();
  }
 
  boost::asio::io_context &m_ioContext;
  tcp::acceptor m_acceptor;
};

void CSocketNetwork::_SocketThread(u_int16_t port_){  
    try
    {
        CIOCPAcceptor iocpAcceptor(m_ioContext, port_);
        m_ioContext.run();
    }
    catch (exception& e)
    {
        Log(string("_SocketThread Exception : ") + e.what());
        delete m_iocpThread;
        m_iocpThread = nullptr;
    }
}

bool CSocketNetwork::Start(u_int16_t port_){
    if(m_iocpThread!=nullptr){
        Log("CSocketNetwork: m_iocpThread already started.");
        return false;
    }

    m_iocpThread = new std::thread(&CSocketNetwork::_SocketThread, this, port_);

    return true;
}