
#ifndef DATA_H
#define DATA_H

#include <string>
#include "../database/Connection_pool.h"

#define register_success 2000
#define uesr_too_long 2001
#define user_exist 2002
#define password_too_long 2003

class Data
{
public:
    int parse_json(std::string m_string);
    std::string get_md_pwd();
    std::string verify_md(char *content);
    void Base64Encode();
    void Base64Decode();
    void generate_salt();
    void init();

    int usr_register();
    int usr_login();
    bool usr_list();
    void generate_json(int ret, std::string msg);
    void get_data();

private:
    std::string m_password;
    std::string m_password_md5;
    std::string m_name;
    std::string m_nickname;
    std::string m_nickname_base64;
    std::string m_salt;

public:
    std::string m_send_content;
    std::string m_log_content;
};
#endif