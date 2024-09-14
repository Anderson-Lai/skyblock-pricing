#include "api.h"
#include "log.h"

Api::Api(const char* url) : m_curl(curl_easy_init()) 
{
    if (!m_curl)
    {
        Log::Error("Error initializing CURL*");
        return;
    }
    
    m_result = curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, Api::WriteReponse);
    if (m_result != CURLE_OK)
    {
        Log::Error("Error setting writeResponse function for CURL*");
        return;
    }

    m_result = curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_buffer);
    if (m_result != CURLE_OK)
    {
        Log::Error("Error setting m_buffer for CURL*");
        return;
    }

    m_result = curl_easy_setopt(m_curl, CURLOPT_URL, url);
    if (m_result != CURLE_OK)
    {
        Log::Error("Error setting url for CURL*");
        return;
    }

    m_result = curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPALIVE, 1L);
    if (m_result != CURLE_OK)
    {
        Log::Error("Error setting TCP keepalive for CURL*");
        return;
    }

    m_result = curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPIDLE, 10L);
    if (m_result != CURLE_OK)
    {
        Log::Error("Error configuring first keepalive probe for CURL*");
        return;
    }

    m_result = curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPINTVL, 5L);
    if (m_result != CURLE_OK)
    {
        Log::Error("Error configuring keepalive probe interval");
        return;
    }
}

Api::~Api()
{
    if (m_curl)
    {
        curl_easy_cleanup(m_curl);
    }
}

size_t Api::WriteReponse(void* responseData, size_t elementSize, size_t elementCount, void* buffer)
{
    std::string* buff = static_cast<std::string*>(buffer);
    const char* response = reinterpret_cast<const char*>(responseData);
    size_t responseSize = elementSize * elementCount;

    buff->append(response, responseSize);
    return responseSize;
}

std::string& Api::Call(const char* url)
{
    m_result = curl_easy_setopt(m_curl, CURLOPT_URL, url);
    if (m_result != CURLE_OK)
    {
        Log::Error("Failed to change url for api call");
        m_buffer.clear();
        return m_buffer;
    }

    return this->Call();
}

std::string& Api::Call()
{
    m_buffer.clear();

    m_result = curl_easy_perform(m_curl);
    if (m_result != CURLE_OK)
    {
        Log::Error("Failed to call api");
        m_buffer.clear();
    }

    return m_buffer;
}
