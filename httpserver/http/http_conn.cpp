#include "http_conn.h"
#include <map>

using namespace std;

const char *DOC_SRC = "/home/ljh/workspace/training/t3/httpserver/src";

// 定义http响应的一些状态信息
const char *ok_200_title = "OK";
const char *error_400_title = "Bad Request";
const char *error_400_form = "Your request has bad syntax or is inherently impossible to staisfy.\n";
const char *error_403_title = "Forbidden";
const char *error_403_form = "You do not have permission to get file form this server.\n";
const char *error_404_title = "Not Found";
const char *error_404_form = "The requested file was not found on this server.\n";
const char *error_500_title = "Internal Error";
const char *error_500_form = "There was an unusual problem serving the request file.\n";

void http_conn::print_parse() // 打印解析消息
{
    cout << endl;
    cout << "............................." << endl;
    cout << "parse :" << endl;
    if (m_method == 0)
    {
        cout << "GET";
    }
    else
    {
        cout << "POST";
    }
    cout << " " << m_url << " " << m_version << endl;
    if (m_usr_agent)
    {
        cout << "Usr-Agent:" << m_usr_agent << endl;
    }
    if (m_accept)
    {
        cout << "Accept:" << m_accept << endl;
    }
    if (m_accept_Encoding)
    {
        cout << "Accept-Encoding:" << m_accept_Encoding << endl;
    }
    if (m_token)
    {
        cout << "Postman-Token:" << m_token << endl;
    }
    if (m_host)
    {
        cout << "Host:" << m_host << endl;
    }
    if (m_content_length)
    {
        cout << "Content-Length:" << m_content_length << endl;
    }
    if (m_linger)
    {
        cout << "Connection: keep-alive" << endl;
    }
    if (m_string)
    {
        cout << m_string << endl;
    }
}

http_conn::HTTP_CODE http_conn::process_read() // 解析http报文
{
    LINE_STATUS line_status = LINE_OK;
    char *text = NULL;
    HTTP_CODE ret = NO_REQUEST;
    while ((m_check_state == CHECK_STATE_CONTENT && line_status == LINE_OK) || ((line_status = parse_line()) == LINE_OK))
    {
        text = getline();
        m_start_index = m_checked_index;

        switch (m_check_state)
        {
        case CHECK_STATE_REQUESTLINE:
        {
            ret = parse_request_line(text);
            if (ret == BAD_REQUEST)
            {
                return BAD_REQUEST;
            }
            break;
        }
        case CHECK_STATE_HEADER:
        {
            ret = parse_headers(text);
            if (ret == BAD_REQUEST)
            {
                return BAD_REQUEST;
            }
            else if (ret == GET_REQUEST)
            {
                return do_request();
            }
            break;
        }

        case CHECK_STATE_CONTENT:
        {
            ret = parse_content(text);
            if (ret == GET_REQUEST)
            {
                return do_request();
            }
            line_status = LINE_OPEN;
            break;
        }
        default:
            return INTERNAL_ERROR;
        }
    }
    return NO_REQUEST;
}

http_conn::HTTP_CODE http_conn::parse_request_line(char *text) // 解析请求行
{
    m_url = strpbrk(text, " \t");
    if (!m_url)
    {
        return BAD_REQUEST;
    }
    *m_url++ = '\0';
    char *method = text;
    if (strcasecmp(method, "GET") == 0)
    {
        m_method = GET;
    }
    else if (strcasecmp(method, "POST") == 0)
    {
        m_method = POST;
    }
    else
        return BAD_REQUEST;
    m_url += strspn(m_url, " \t");
    m_version = strpbrk(m_url, " \t");
    if (!m_version)
        return BAD_REQUEST;
    *m_version++ = '\0';
    m_version += strspn(m_version, " \t");
    if (strcasecmp(m_version, "HTTP/1.1") != 0)
        return BAD_REQUEST;

    if (!m_url || m_url[0] != '/')
        return BAD_REQUEST;

    m_check_state = CHECK_STATE_HEADER;
    return NO_REQUEST;
}

http_conn::HTTP_CODE http_conn::parse_headers(char *text) // 解析请求头
{
    if (text[0] == '\0')
    {
        if (m_content_length != 0)
        {
            m_check_state = CHECK_STATE_CONTENT;
            return NO_REQUEST;
        }
        return GET_REQUEST;
    }
    else if (strncasecmp(text, "Content-length:", 15) == 0)
    {
        text += 15;
        text += strspn(text, " \t");
        m_content_length = atol(text);
    }
    else if (strncasecmp(text, "Connection:", 11) == 0)
    {
        text += 11;
        text += strspn(text, " \t");
        if (strcasecmp(text, "keep-alive") == 0)
        {
            m_linger = true;
        }
        else
        {
            m_linger = false;
        }
    }
    else if (strncasecmp(text, "Host:", 5) == 0)
    {
        text += 5;
        text += strspn(text, " \t");
        m_host = text;
    }
    else if (strncasecmp(text, "Accept:", 7) == 0)
    {
        text += 7;
        text += strspn(text, " \t");
        m_accept = text;
    }
    else if (strncasecmp(text, "Postman-Token:", strlen("Postman-Token:")) == 0)
    {
        text += strlen("Postman-Token:");
        text += strspn(text, " \t");
        m_token = text;
    }
    else if (strncasecmp(text, "Accept-Encoding:", strlen("Accept-Encoding:")) == 0)
    {
        text += strlen("Accept-Encoding:");
        text += strspn(text, " \t");
        m_accept_Encoding = text;
    }
    else if (strncasecmp(text, "User-Agent:", strlen("User-Agent:")) == 0)
    {
        text += strlen("User-Agent:");
        text += strspn(text, " \t");
        m_usr_agent = text;
    }
    else if (strncasecmp(text, "Content-Type:", strlen("Content-Type:")) == 0)
    {
        text += strlen("Content-Type:");
        text += strspn(text, " \t");
        m_content_type = text;
    }
    else if (strncasecmp(text, "Content-MD5:", strlen("Content-MD5:")) == 0)
    {
        text += strlen("Content-Type:");
        text += strspn(text, " \t");
        m_content_md5 = text;
    }
    return NO_REQUEST;
}

http_conn::HTTP_CODE http_conn::parse_content(char *text) // 解析请求体
{
    // 对POST请求的处理
    if (m_read_index >= (m_content_length + m_checked_index))
    {
        text[m_content_length] = '\0';
        m_string = text;
        return GET_REQUEST;
    }
    return NO_REQUEST;
}

http_conn::HTTP_CODE http_conn::deal_GET()
{
    /*m_string = strpbrk(m_url, "?");
    if (m_string)
    {
        *m_string++ = '\0';
    }*/
    m_log_index = m_log.show_log(m_show_log_buf);
    return Show_log;
}

int http_conn::deal_POST(char *text)
{
    if (m_string == NULL)
    {
        return 0;
    }
    if (strcasecmp(m_data.verify_md(m_string).c_str(), m_content_md5) != 0)
    {
        cout << "文件错误" << endl;
        return -1;
    }

    int ret = m_data.parse_json(m_string);
    if (ret == -2)
    {
        return -2;
    }

    if (strcmp(m_url, "/register") == 0)
    {
        m_data.Base64Decode();
        m_data.generate_salt();
        return m_data.usr_register();
    }
    else if (strcmp(m_url, "/login") == 0)
    {
        return m_data.usr_login();
    }
    return 1;
}

http_conn::HTTP_CODE http_conn::do_request() // 获取服务器资源
{
    if (strcasecmp(m_url, "/api/v1/user/register") == 0)
    {
        strcpy(m_url, "/register");
    }
    else if (strcasecmp(m_url, "/api/v1/user/login") == 0)
    {
        strcpy(m_url, "/login");
    }
    else if (strcasecmp(m_url, "/api/v1/user/list") == 0)
    {
        strcpy(m_url, "/list");
    }

    if (m_method == POST)
    {
        if (strcasecmp(m_url, "/register") == 0 || strcasecmp(m_url, "/login") == 0)
        {
            int ret = deal_POST(m_string);
            cout << "ret is " << ret << endl;
            switch (ret)
            {
            case 2000:
                return Register_success;
            case 2001:
                return User_too_long;
            case 2002:
                return User_exist;
            case 2003:
                return Password_too_long;
            case 3000:
                return Login_success;
            case 3001:
                return Login_fail;
            case -1:
                return FILE_break;
            case -2:
                return NO_PWD_USR;
            default:
                break;
            }
        }
    }
    else if (m_method == GET && strcasecmp(m_url, "/list") == 0)
    {
        return deal_GET();
    }

    sprintf(m_real_file, "%s%s.html", DOC_SRC, m_url);

    if (stat(m_real_file, &m_file_stat) < 0)
    {
        return NO_RESOURCE;
    }
    if (!(m_file_stat.st_mode & S_IROTH))
    {
        return FORBIDDEN_REQUEST;
    }
    if (S_ISDIR(m_file_stat.st_mode))
    {
        return BAD_REQUEST;
    }

    int fd = open(m_real_file, O_RDONLY);
    m_file_address = (char *)mmap(0, m_file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    return FILE_REQUEST;
}

void http_conn::unmap()
{
    if (m_file_address)
    {
        munmap(m_file_address, m_file_stat.st_size);
        m_file_address = NULL;
    }
}

void http_conn::process_write(HTTP_CODE ret) // 生成响应报文
{
    switch (ret)
    {
    case FILE_REQUEST:
    {
        add_status_line(200, ok_200_title);
        add_header(m_file_stat.st_size);
        strcat(m_write_buf, m_file_address);
        m_iv_count = 2;
        bytes_to_send = m_write_index + m_file_stat.st_size;
        return;
    }
    case NO_RESOURCE:
    {
        add_status_line(404, error_404_title);
        add_header(strlen(error_404_form));
        add_content(error_404_form);
        break;
    }
    case Register_success:
    {
        m_data.generate_json(Register_success, "成功");
        add_status_line(200, ok_200_title);
        add_header(m_data.m_send_content.size());
        add_content(m_data.m_send_content.c_str());
        break;
    }
    case User_exist:
    {
        cout << "exist" << endl;
        m_data.generate_json(User_exist, "用户名已注册");
        add_status_line(200, ok_200_title);
        add_header(m_data.m_send_content.size());
        add_content(m_data.m_send_content.c_str());
        break;
    }
    case User_too_long:
    {
        m_data.generate_json(User_too_long, "用户名过长");
        add_status_line(200, ok_200_title);
        add_header(m_data.m_send_content.size());
        add_content(m_data.m_send_content.c_str());
        break;
    }
    case Password_too_long:
    {
        m_data.generate_json(Password_too_long, "密码过长");
        add_status_line(200, ok_200_title);
        add_header(m_data.m_send_content.size());
        add_content(m_data.m_send_content.c_str());
        break;
    }
    case Login_success:
    {
        m_data.generate_json(Login_success, "登录成功");
        add_status_line(200, ok_200_title);
        add_header(m_data.m_send_content.size());
        add_content(m_data.m_send_content.c_str());
        break;
    }
    case Login_fail:
    {
        m_data.generate_json(Login_fail, "密码错误");
        add_status_line(200, ok_200_title);
        add_header(m_data.m_send_content.size());
        add_content(m_data.m_send_content.c_str());
        break;
    }
    case Show_log:
    {
        add_status_line(200, ok_200_title);
        add_header(m_log_index - 2); // 去掉末尾的 ,
        add_content(m_show_log_buf);
        break;
    }
    case FILE_break:
    {
        m_data.generate_json(FILE_break, "文件损坏");
        add_status_line(200, ok_200_title);
        add_header(m_data.m_send_content.size());
        add_content(m_data.m_send_content.c_str());
        break;
    }
    case NO_PWD_USR:
    {
        m_data.generate_json(NO_PWD_USR, "输入账号或密码");
        add_status_line(200, ok_200_title);
        add_header(m_data.m_send_content.size());
        add_content(m_data.m_send_content.c_str());
        break;
    }
    default:
        break;
    }
    if (!m_data.m_log_content.empty())
    {
        m_log.write_log(m_data.m_log_content);
    }
    else if (!m_data.m_send_content.empty())
    {
        m_log.write_log(m_data.m_send_content);
    }
    m_iv_count = 1;
    bytes_to_send = m_write_index;
}

void http_conn::add_status_line(int status, const char *title) // 生成状态行
{
    int len = sprintf(m_write_buf + m_write_index, "HTTP/1.1 %d %s\r\n", status, title);
    m_write_index += len;
}

void http_conn::add_header(int length) // 生成响应头
{
    add_linger();
    add_content_length(length);
    if (m_content_type != NULL)
    {
        add_content_tpye();
    }
    add_blank_line();
}

void http_conn::add_content_length(int length) // 添加Content-:Length:
{
    int len = sprintf(m_write_buf + m_write_index, "Content-Length:%d\r\n", length);
    m_write_index += len;
}

void http_conn::add_linger() // 添加Connction：
{
    int len = sprintf(m_write_buf + m_write_index, "Connection:");
    m_write_index += len;
    if (m_linger)
    {
        len = sprintf(m_write_buf + m_write_index, "keep-alive\r\n");
    }
    else
    {
        len = sprintf(m_write_buf + m_write_index, "close\r\n");
    }
    m_write_index += len;
}

void http_conn::add_content_tpye()
{
    int len = sprintf(m_write_buf + m_write_index, "Content-Type:%s\r\n", m_content_type);
    m_write_index += len;
}

void http_conn::add_blank_line() // 添加空行
{
    int len = sprintf(m_write_buf + m_write_index, "\r\n");
    m_write_index += len;
}

void http_conn::add_content(const char *content) // 生成响应正文
{
    int len = sprintf(m_write_buf + m_write_index, "%s", content);
    m_write_index += len;
}

char *http_conn::getline() // 读取一行
{
    return m_read_buf + m_start_index;
}

http_conn::LINE_STATUS http_conn::parse_line() // 按行解析
{
    char temp;
    for (; m_checked_index < m_read_index; ++m_checked_index)
    {
        temp = m_read_buf[m_checked_index];
        if (temp == '\r')
        {
            if ((m_checked_index + 1) == m_read_index)
                return LINE_OPEN;
            else if (m_read_buf[m_checked_index + 1] == '\n')
            {
                m_read_buf[m_checked_index++] = '\0';
                m_read_buf[m_checked_index++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
        else if (temp == '\n')
        {
            if (m_checked_index > 1 && m_read_buf[m_checked_index - 1] == '\r')
            {
                m_read_buf[m_checked_index - 1] = '\0';
                m_read_buf[m_checked_index++] = '\0';
                return LINE_OK;
            }
            return LINE_BAD;
        }
    }
    return LINE_OPEN;
}

char *http_conn::get_read_buf()
{
    return m_read_buf;
}

char *http_conn::get_write_buf()
{
    return m_write_buf;
}

void http_conn::set_read_index(int num)
{
    m_read_index = num;
}

int http_conn::get_write_index()
{
    return bytes_to_send;
}

void http_conn::process_asio()
{
    http_conn::HTTP_CODE ret = process_read();
    process_write(ret);
}

char *http_conn::get_file_address()
{
    return m_file_address;
}

int http_conn::get_file_size()
{
    return m_file_stat.st_size;
}

bool http_conn::send_html()
{
    if (m_iv_count == 2)
    {
        return true;
    }
    return false;
}

void http_conn::init_asio()
{
    m_read_index = 0;
    m_checked_index = 0;
    m_start_index = 0;
    m_check_state = CHECK_STATE_REQUESTLINE;
    m_content_length = 0;
    m_linger = false;

    m_write_index = 0;
    bytes_have_send = 0;

    memset(m_read_buf, '\0', sizeof(m_read_buf));
    memset(m_show_log_buf, '\0', sizeof(m_show_log_buf));
    m_data.init();
}
