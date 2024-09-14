#pragma once
#include <chrono>

namespace Timing
{
    std::chrono::time_point<std::chrono::high_resolution_clock> Now();
    void Sleep(const unsigned long long milliseconds);
    unsigned long long SecondsSinceEpoch();
    void Log(const std::chrono::time_point<std::chrono::high_resolution_clock>& first,
            const std::chrono::time_point<std::chrono::high_resolution_clock>& second);
}
