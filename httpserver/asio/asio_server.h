#ifndef SESSION_H
#define SESSION_H

#include "../http/http_conn.h"
#include <boost/asio.hpp>

using namespace boost::asio::ip;
class session
{
public:
    session(boost::asio::io_context &ioc) : m_socket(ioc) {}
    tcp::socket &Socket()
    {
        return m_socket;
    }
    void Start();
    void handle_read(const boost::system::error_code &error, size_t bytes_transfered);
    void handle_write(const boost::system::error_code &error);

private:
    tcp::socket m_socket;
    http_conn usr;
};

class asio_server
{
public:
    asio_server(boost::asio::io_context &ioc, unsigned int port);
    void start_accept();
    void hander_accept(session *new_session, const boost::system::error_code &error);

private:
    boost::asio::io_context &m_ioc;
    tcp::acceptor m_acceptor;
};

#endif