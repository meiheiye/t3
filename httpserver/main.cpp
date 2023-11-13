#include "./asio/asio_server.h"

int main()
{
    Connection_pool *pool = Connection_pool::get_instance();
    pool->init_con(); // 初始化连接池

    Data data;
    data.get_data(); // 读取数据库

    boost::asio::io_context ioc;
    asio_server s(ioc, 9006);
    ioc.run();
    return 0;
}