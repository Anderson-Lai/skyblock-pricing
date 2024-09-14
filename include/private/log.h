#pragma once
#include <string>

namespace Log
{
    void Println(const std::string& message = "");
    void Error(const std::string& error = "");
}
