#ifndef HTTP_CONN_H
#define HTTP_CONN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <string.h>
#include <sstream>
#include <iterator>
#include <string>
#include <iostream>

#include "../userinfo/data.h"
#include "../log/log.h"

using namespace std;

const int READ_BUFFER_SIZE = 1024;
const int WRITE_BUFFER_SIZE = 2048;

class http_conn
{

public:
    // 解析报文状态码
    enum CHECK_STATE
    {
        CHECK_STATE_REQUESTLINE = 0,
        CHECK_STATE_HEADER,
        CHECK_STATE_CONTENT
    };

    // 解析行状态码
    enum LINE_STATUS
    {
        LINE_OK = 0,
        LINE_BAD,
        LINE_OPEN
    };

    // url 请求资源
    enum HTTP_CODE
    {
        NO_REQUEST,
        GET_REQUEST,
        BAD_REQUEST,
        NO_RESOURCE,
        FORBIDDEN_REQUEST,
        FILE_REQUEST,
        INTERNAL_ERROR,
        CLOSED_CONNECTION,
        Register_success = 2000,
        User_too_long,
        User_exist,
        Password_too_long,
        Login_success = 3000,
        Login_fail,
        Show_log = 4000,
        FILE_break = -1,
        NO_PWD_USR = -2
    };

    enum METHOD
    {
        GET = 0,
        POST,
        HEAD,
        PUT,
        DELETE,
        TRACE,
        OPTIONS,
        CONNECT,
        PATH
    };

    // 解析报文
    HTTP_CODE process_read();
    LINE_STATUS parse_line();
    char *getline();
    HTTP_CODE parse_request_line(char *text);
    HTTP_CODE parse_headers(char *text);
    HTTP_CODE parse_content(char *text);
    HTTP_CODE do_request();
    http_conn::HTTP_CODE deal_GET();
    int deal_POST(char *text);
    void print_parse();

    // 生成响应报文
    void process_write(HTTP_CODE ret);
    void add_status_line(int status, const char *title);
    void add_header(int length);
    void add_content_length(int content_length);
    void add_linger();
    void add_content_tpye();
    void add_blank_line();
    void add_content(const char *content);
    void unmap();

    // 异步IO的函数
    char *get_read_buf();
    char *get_write_buf();
    char *get_file_address();

    void set_read_index(int num);
    int get_write_index();
    int get_file_size();

    bool send_html();
    void init_asio();
    void process_asio();

public:
    Data m_data;
    log m_log;

private:
    sockaddr_in m_address;
    char m_read_buf[READ_BUFFER_SIZE];

    int m_read_index;
    int m_checked_index;
    int m_start_index;

    int m_write_index;
    int m_log_index;
    char m_write_buf[WRITE_BUFFER_SIZE];
    char m_show_log_buf[WRITE_BUFFER_SIZE];

    int m_check_state;
    // http请求报文信息
    char *m_url;
    char *m_version;
    METHOD m_method;

    int m_content_length;
    bool m_linger;
    char *m_host;
    char *m_string;
    char *m_usr_agent;
    char *m_accept;
    char *m_token;
    char *m_accept_Encoding;
    char *m_content_type;
    char *m_content_md5;

    char m_real_file[100];
    char *m_file_address;
    struct stat m_file_stat;
    int m_iv_count;
    int bytes_to_send;
    int bytes_have_send;
};
#endif