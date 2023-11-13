#include "asio_server.h"

#define BUFF_SIZE 1024

asio_server::asio_server(boost::asio::io_context &ioc, unsigned int port) : m_ioc(ioc),
                                                                            m_acceptor(ioc, tcp::endpoint(tcp::v4(), port))
{
    start_accept();
}

void asio_server::start_accept()
{
    session *new_session = new session(m_ioc);
    m_acceptor.async_accept(new_session->Socket(),
                            std::bind(&asio_server::hander_accept, this, new_session, placeholders::_1));
}

void asio_server::hander_accept(session *new_session, const boost::system::error_code &error)
{
    if (!error)
    {
        new_session->Start();
    }
    else
    {
        delete new_session;
    }
    start_accept();
}

void session::Start()
{
    usr.init_asio();
    m_socket.async_read_some(boost::asio::buffer(usr.get_read_buf(), BUFF_SIZE),
                             std::bind(&session::handle_read, this, placeholders::_1,
                                       placeholders::_2));
}

void session::handle_read(const boost::system::error_code &error, size_t bytes_transfered)
{
    if (!error)
    {
        usr.set_read_index(bytes_transfered);
        usr.process_asio();
        boost::asio::async_write(m_socket, boost::asio::buffer(usr.get_write_buf(), usr.get_write_index() + usr.get_file_size()),
                                 std::bind(&session::handle_write, this, placeholders::_1));
    }
    else
    {
        delete this;
    }
}

void session::handle_write(const boost::system::error_code &error)
{
    if (!error)
    {
        usr.init_asio();
        m_socket.async_read_some(boost::asio::buffer(usr.get_read_buf(), BUFF_SIZE),
                                 std::bind(&session::handle_read, this, placeholders::_1, placeholders::_2));
    }
    else
    {
        delete this;
    }
}
