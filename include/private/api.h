#pragma once
#include "curl/curl.h"
#include <string>

class Api 
{
public:
    Api();
    Api(const char* url);
    ~Api();
    std::string& Call();
    std::string& Call(const char* url);
private:
    static size_t WriteReponse(void* reponseData, size_t elementSize, size_t elementCount, void* buffer);
private:
    CURL* m_curl; 
    CURLcode m_result;
    std::string m_buffer;
};
