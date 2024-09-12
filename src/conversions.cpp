#include "conversions.h"
#include "log.h"
#include <cstdlib>

std::wstring Conversions::ToWideString(const char* str)
{
    size_t length = std::mbstowcs(nullptr, str, 0);
    if (length == static_cast<size_t>(-1))
    {
        Log::Error("Failed to convert const char* to std::wstring");
        return L"";
    }
    
    std::wstring converted(length, L'\0');
    std::mbstowcs(&converted[0], str, length);

    return converted;
}

std::wstring Conversions::ToWideString(const std::string& str)
{
    return Conversions::ToWideString(str.c_str());
}

std::string Conversions::ToNarrowString(const std::wstring& str)
{
    const wchar_t* underlying = str.c_str();

    size_t length = std::wcstombs(nullptr, underlying, 0); 
    if (length == static_cast<size_t>(-1))
    {
        Log::Error("Failed to convert std::wstring to std::string");
        return "";
    }

    std::string converted(length, '\0');
    std::wcstombs(&converted[0], underlying, length);
    
    return converted;
}
