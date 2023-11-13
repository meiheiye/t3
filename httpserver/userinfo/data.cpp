#include "data.h"
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/json.hpp>
#include <boost/json/src.hpp>
#include <sstream>
#include <iterator>
#include <string>
#include <iostream>

using namespace std;
using namespace boost::archive::iterators;
using boost::uuids::detail::md5;

map<string, string> usr_map;

void Data::generate_salt()
{
    char c;
    for (int i = 0; i < 16; i++)
    {
        c = 'a' + rand() % 26;
        m_salt.push_back(c);
    }
}

void Data::Base64Decode()
{
    using Base64DecodeIterator = transform_width<binary_from_base64<string::const_iterator>, 8, 6>;
    stringstream result;
    copy(Base64DecodeIterator(m_nickname_base64.begin()), Base64DecodeIterator(m_nickname_base64.end()), ostream_iterator<char>(result));
    m_nickname = result.str();
}

void Data::Base64Encode()
{
    using Base64EncodeIterator = base64_from_binary<transform_width<string::const_iterator, 6, 8>>;
    stringstream result;
    copy(Base64EncodeIterator(m_nickname.begin()), Base64EncodeIterator(m_nickname.end()), ostream_iterator<char>(result));
    // 末尾加=
    size_t equal_count = (3 - m_nickname.length() % 3) % 3;
    for (size_t i = 0; i < equal_count; i++)
    {
        result.put('=');
    }
    m_nickname_base64 = result.str();
}

string Data::get_md_pwd()
{
    string tmp;
    tmp = m_password + m_salt;
    md5 hash;
    md5::digest_type digest;
    hash.process_bytes(tmp.data(), tmp.size());
    hash.get_digest(digest);

    tmp.clear();
    const auto charDigest = reinterpret_cast<const char *>(&digest);
    boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(tmp));
    return tmp;
    // cout << "MD5 加密为" << m_password_md5 << endl;
}

string Data::verify_md(char *content)
{
    string tmp = content;
    md5 hash;
    md5::digest_type digest;
    hash.process_bytes(tmp.data(), tmp.size());
    hash.get_digest(digest);
    tmp.clear();
    const auto charDigest = reinterpret_cast<const char *>(&digest);
    boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(tmp));
    return tmp;
}

int Data::parse_json(std::string m_string)
{
    boost::json::value parsed_value = boost::json::parse(m_string);
    if (parsed_value.is_object())
    {
        for (const auto &pair : parsed_value.as_object())
        {
            if (strcasecmp(pair.key().data(), "username") == 0)
            {
                m_name = pair.value().as_string().c_str();
            }
            else if (strcasecmp(pair.key().data(), "password") == 0)
            {
                m_password = pair.value().as_string().c_str();
            }
            else if (strcasecmp(pair.key().data(), "nickname") == 0)
            {
                m_nickname_base64 = pair.value().as_string().c_str();
            }
        }
        if (m_name.empty() || m_password.empty())
        {
            return -2;
        }
    }
    return 0;
}

int Data::usr_register()
{
    if (m_password_md5.size() > 40)
    {
        return password_too_long;
    }
    else if (m_name.size() > 20)
    {
        return uesr_too_long;
    }

    MYSQL *con = NULL;
    connectionRAII(&con, Connection_pool::get_instance());
    m_password_md5 = get_md_pwd();

    auto it = usr_map.find(m_name);
    if (it != usr_map.end())
    {
        return user_exist;
    }
    else
    {
        char query[128];
        if (m_nickname.empty())
        {
            sprintf(query, "insert into user (user,pwd,salt) values('%s','%s','%s')", m_name.c_str(), m_password_md5.c_str(), m_salt.c_str());
        }
        else
        {
            sprintf(query, "insert into user (user,pwd,salt,nickname) values('%s','%s','%s','%s')", m_name.c_str(), m_password_md5.c_str(), m_salt.c_str(), m_nickname.c_str());
        }
        if (mysql_query(con, query) != 0)
        {
            cout << mysql_error(con) << endl;
        }
        else
        {
            usr_map.insert(pair<string, string>(m_name, m_password_md5));
            return register_success;
        }
    }
    return uesr_too_long;
}

int Data::usr_login()
{
    MYSQL *con = NULL;
    connectionRAII(&con, Connection_pool::get_instance());

    char query[512];
    sprintf(query, "select pwd,salt from user where user = '%s'", m_name.c_str());
    if (mysql_query(con, query) != 0)
    {
        cout << "不存在该用户" << endl;
        return 3001;
    }

    MYSQL_RES *result = mysql_store_result(con);

    while (MYSQL_ROW row = mysql_fetch_row(result))
    {
        m_password_md5 = row[0];
        m_salt = row[1];
    }
    string tmp = get_md_pwd();
    if (tmp == m_password_md5)
    {
        cout << "登录成功" << endl;
        return 3000;
    }
    return 3001;
}

bool Data::usr_list()
{
    return true;
}

void Data::generate_json(int ret, std::string msg)
{
    boost::json::object val;
    val["code"] = ret;
    val["msg"] = msg;
    m_send_content = boost::json::serialize(val);
    if (ret == 2000)
    {
        boost::json::object data;
        data["username"] = m_name;
        if (!m_nickname_base64.empty())
        {
            data["nickname"] = m_nickname_base64;
        }
        val["data"] = data;
        m_log_content = boost::json::serialize(val);
    }
}

void Data::get_data()
{
    MYSQL *con = NULL;
    connectionRAII(&con, Connection_pool::get_instance());
    char query[128] = "select user,pwd from user";
    if (mysql_query(con, query) != 0)
    {
        cout << mysql_error(con);
    }
    MYSQL_RES *result = mysql_store_result(con);

    while (MYSQL_ROW row = mysql_fetch_row(result))
    {
        usr_map.insert(pair<string, string>(row[0], row[1]));
    }

    for (auto it : usr_map)
    {
        cout << it.first << " " << it.second << endl;
    }
}

void Data::init()
{
    m_password.clear();
    m_password_md5.clear();
    m_name.clear();
    m_nickname.clear();
    m_nickname_base64.clear();
    m_salt.clear();
    m_send_content.clear();
    m_log_content.clear();
}