#include "pricinglibrary.h"
#include "timing.h"
#include "log.h"

int main()
{
    PricingLibrary::Initialize();
    while (true)
    {
        auto bins = PricingLibrary::GetFlips();
        for (const auto& bin : bins)
        {
            Log::Println(std::format("{}", bin->GetStartTime())); 
        }
        Timing::Sleep(100);
    }
    PricingLibrary::CleanUp();
    return 0;
}
