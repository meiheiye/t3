#ifndef CONNECTION_POOL_H
#define CONNECTION_POOL_H

#include <queue>
#include <mysql/mysql.h>

class Connection_pool
{
public:
    static Connection_pool *get_instance();
    void init_con();
    MYSQL *get_connection();
    void realse_connection(MYSQL *con);

private:
    std::queue<MYSQL *> con_queue;
};

class connectionRAII
{

public:
    connectionRAII(MYSQL **con, Connection_pool *connPool);
    ~connectionRAII();

private:
    MYSQL *conRAII;
    Connection_pool *poolRAII;
};

#endif
