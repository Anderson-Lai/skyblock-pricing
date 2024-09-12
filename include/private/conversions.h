#pragma once
#include <string>

namespace Conversions
{
    std::wstring ToWideString(const char* str);
    std::wstring ToWideString(const std::string& str);
    std::string ToNarrowString(const std::wstring& str);
}
