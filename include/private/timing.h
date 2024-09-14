#pragma once
#include <chrono>

namespace Timing
{
    std::chrono::time_point<std::chrono::high_resolution_clock> Now();
    void Sleep(const unsigned long long milliseconds);
    unsigned long long SecondsSinceEpoch();
}
