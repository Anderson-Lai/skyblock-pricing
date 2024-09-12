#include "log.h"
#include <iostream>

void Log::Println(const std::string& message)
{
    std::cout << message << "\n";
}

void Log::Error(const std::string& error)
{
    std::cerr << error << "\n";
}
