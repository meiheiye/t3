#include "Connection_pool.h"
#include <iostream>

using namespace std;

#define MAX_CON_NUM 1

void Connection_pool::init_con()
{
    for (int i = 0; i < MAX_CON_NUM; i++)
    {
        MYSQL *con = NULL;
        con = mysql_init(con);
        con = mysql_real_connect(con, "127.0.0.1", "ljh", "123456", "test", 3306, NULL, 0);
        if (NULL == con)
        {
            std::cout << "connect fail" << std::endl;
        }
        else
        {
            con_queue.push(con);
        }
    }
}

MYSQL *Connection_pool::get_connection()
{
    if (con_queue.empty())
    {
        return NULL;
    }
    MYSQL *con = con_queue.front();
    con_queue.pop();
    return con;
}
void Connection_pool::realse_connection(MYSQL *con)
{
    con_queue.push(con);
}

Connection_pool *Connection_pool::get_instance()
{
    static Connection_pool pool;
    return &pool;
}

connectionRAII::connectionRAII(MYSQL **SQL, Connection_pool *connPool)
{
    *SQL = connPool->get_connection();
    conRAII = *SQL;
    poolRAII = connPool;
}

connectionRAII::~connectionRAII()
{
    poolRAII->realse_connection(conRAII);
}