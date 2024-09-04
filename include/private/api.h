#pragma once
#include "curl/curl.h"
#include <string>

class Api {
public:

private:
    CURL* m_curl; 
    CURLcode m_result;
    std::string m_buffer;
};
