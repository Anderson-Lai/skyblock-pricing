#include "timing.h"
#include <thread>
#include "log.h"

std::chrono::time_point<std::chrono::high_resolution_clock> Timing::Now()
{
    return std::chrono::high_resolution_clock::now(); 
}

void Timing::Sleep(const unsigned long long milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

unsigned long long Timing::SecondsSinceEpoch()
{
    const std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
}

void Timing::Log(const std::chrono::time_point<std::chrono::high_resolution_clock>& start, 
        const std::chrono::time_point<std::chrono::high_resolution_clock>& end)
{
    const std::chrono::milliseconds elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    Log::Println(std::format("Time Elapsed: {}", elapsed));
}
