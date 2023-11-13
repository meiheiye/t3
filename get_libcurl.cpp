#include <curl/curl.h>
#include <iostream>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int main()
{
    CURL *curl;
    CURLcode res;

    // 初始化 libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        // 设置请求 URL
        curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.146.131:9006/list");

        // 设置写回调函数，用于处理响应数据
        std::string response_data;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        // 执行请求
        res = curl_easy_perform(curl);

        // 检查请求是否成功
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
            std::cout << "Response: " << response_data << std::endl;

        // 清理 libcurl 资源
        curl_easy_cleanup(curl);
    }

    // 清理全局资源
    curl_global_cleanup();

    return 0;
}
