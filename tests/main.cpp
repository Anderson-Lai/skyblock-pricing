#include "pricinglibrary.h"
#include "timing.h"

int main()
{
    PricingLibrary::Initialize();
    while (true)
    {
        PricingLibrary::GetFlips();
        Timing::Sleep(100);
    }
    PricingLibrary::CleanUp();
    return 0;
}
