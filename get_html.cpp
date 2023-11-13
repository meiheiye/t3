#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <stdlib.h>
int main()
{
    CURL *curl;
    CURLcode res;
    char http[128] = "http://192.168.146.131:9006/list";

    curl = curl_easy_init();
    if (curl != NULL)
    {
        curl_easy_setopt(curl, CURLOPT_URL, http);
        res = curl_easy_perform(curl);
        std::cout << std::endl;
        curl_easy_cleanup(curl);
    }
    return 0;
}