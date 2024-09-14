#pragma once
#include <string>
#include <unordered_map>

namespace File
{
    int CreateFile(const std::string& fileName);
    std::string ReadFile(const std::string& fileName);
    void WritePrices(const std::string& fileName,
            const std::unordered_map<std::wstring, long long>& prices);
}
