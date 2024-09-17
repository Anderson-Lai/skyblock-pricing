#include "conversions.h"
#include "pricinglibrary.h"
#include "timing.h"
#include "log.h"

int main()
{
    if (PricingLibrary::Initialize())
    {
        return 1;
    }

    while (true)
    {
        if (Timing::CurrentSecondInMinute() == 0)
        {
            const std::vector<std::unique_ptr<Item>> bins = PricingLibrary::GetFlips();
            Log::Println();
            
            for (const auto& bin : bins)
            {
                Log::Println(
                    std::format(
                        "Auction uuid: {}\nItem name: {}\nPrice: {}\nProfit: {}\n",
                        bin->GetUuid(), Conversions::ToNarrowString(bin->GetName()), 
                        bin->GetPrice(), bin->GetProfit()
                    )
                );
            }

            Timing::Sleep(1'500);
        }

        Timing::Sleep(100);
    }

    PricingLibrary::CleanUp();
    return 0;
}
