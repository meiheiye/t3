#include <curl/curl.h>
#include <boost/algorithm/hex.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/json.hpp>
#include <boost/json/src.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <iostream>
#include <iterator>

using namespace std;
using boost::uuids::detail::md5;
using namespace boost::archive::iterators;

#define REGISTER "http://192.168.146.131:9006/register"
#define LOGIN "http://192.168.146.131:9006/login"

std::string get_md5_string(const std::string input)
{
    md5 hash;
    md5::digest_type digest;
    hash.process_bytes(input.data(), input.size());
    hash.get_digest(digest);

    const auto charDigest = reinterpret_cast<const char *>(&digest);
    std::string result;
    boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(result));
    return result;
}

string generate_content(string username, string password)
{
    boost::json::object val;
    val["username"] = username;
    val["password"] = password;
    return boost::json::serialize(val);
}

string generate_content(string username, string password, string nickname)
{
    boost::json::object val;
    val["username"] = username;
    val["password"] = password;
    val["nickname"] = nickname;
    return boost::json::serialize(val);
}

string Base64Encode(string nickname)
{
    using Base64EncodeIterator = base64_from_binary<transform_width<string::const_iterator, 6, 8>>;
    stringstream result;
    copy(Base64EncodeIterator(nickname.begin()), Base64EncodeIterator(nickname.end()), ostream_iterator<char>(result));
    // 末尾加=
    size_t equal_count = (3 - nickname.length() % 3) % 3;
    for (size_t i = 0; i < equal_count; i++)
    {
        result.put('=');
    }
    return result.str();
}

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        cout << "usage: L/R name pwd (nickname)" << endl;
        return 0;
    }
    CURL *curl;
    CURLcode res;

    // 初始化libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    string username = argv[2];
    string password = argv[3];
    string nickname = argv[4];

    nickname = Base64Encode(nickname);
    string result;
    if (nickname.empty())
    {
        result = generate_content(username, password);
    }
    else
    {
        result = generate_content(username, password, nickname);
    }

    cout << result << endl;
    char length[64], md5[256], nick_name[256];
    sprintf(length, "Content-Length: %ld", result.size());
    sprintf(md5, "Content-MD5: %s", get_md5_string(result).c_str());

    if (curl)
    {
        if (strcmp(argv[1], "R") == 0)
        {
            curl_easy_setopt(curl, CURLOPT_URL, REGISTER);
        }
        else
        {
            curl_easy_setopt(curl, CURLOPT_URL, LOGIN);
        }

        // 设置请求方法为 POST
        curl_easy_setopt(curl, CURLOPT_POST, 1);

        // 设置请求头
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, length);
        headers = curl_slist_append(headers, md5);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // 设置请求体内容
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, result.c_str());

        // 执行请求
        res = curl_easy_perform(curl);

        // 检查请求是否成功
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        cout << endl;
        // 清理请求头资源
        curl_slist_free_all(headers);

        // 清理 libcurl 资源
        curl_easy_cleanup(curl);
    }

    // 清理全局资源
    curl_global_cleanup();

    return 0;
}