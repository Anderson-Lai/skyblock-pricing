#pragma once
#include "curl/curl.h"
#include <string>

class Api 
{
public:
    Api(std::string&& url);
    ~Api();
    std::wstring& Call();
    std::wstring& Call(std::string&& url);
private:
    static size_t WriteReponse(void* reponseData, size_t elementSize, size_t elementCount, void* buffer);
private:
    CURL* m_curl; 
    CURLcode m_result;
    std::wstring m_buffer;
    std::string m_url;
};
