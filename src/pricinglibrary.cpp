#include "pricinglibrary.h"
#include "conversions.h"
#include "curl/curl.h"
#include <clocale>
#include "api.h"
#include "file.h"
#include "log.h"
#include "parsing.h"
#include "timing.h"
#include "json.h"

namespace PricingLibrary
{
    AuctionHouse auctionHouse;
    Api caller("https://api.hypixel.net/v2/skyblock/auctions?page=0");
    const std::string fileName = "lbin.json";
    const unsigned long long minimumProfit = 1'000'000;
}

int PricingLibrary::Initialize()
{
    curl_global_init(CURL_GLOBAL_DEFAULT); 
    std::setlocale(LC_ALL, "en_US.utf8");

    if (File::CreateFile(PricingLibrary::fileName))
    {
        Log::Error("This library can not continue without {}, exiting initialization now");
        return 1;
    }

    PricingLibrary::auctionHouse.ReadFileData(fileName);

    // constantly update the file that stores auction data
    std::thread([]()
            {
                while (true)
                {
                    const unsigned long long secondsSinceEpoch = Timing::SecondsSinceEpoch();
                    const int secondsToMinute = secondsSinceEpoch % 60;

                    if (secondsToMinute == 55)
                    {
                        const auto fileWriteBegin = Timing::Now();
                        File::WritePrices(PricingLibrary::fileName, PricingLibrary::auctionHouse.GetLbins());
                        const auto fileWriteEnd = Timing::Now();

                        Log::Println();
                        std::cout << "Writing to file: ";
                        Timing::Log(fileWriteBegin, fileWriteEnd);
                        Log::Println();

                        Timing::Sleep(1'500);
                    }
                    Timing::Sleep(100);
                }
            }).detach();

    // constantly seed in new auction house data
    std::thread([]()
            {
                while (true)
                {
                    const unsigned long long secondsSinceEpoch = Timing::SecondsSinceEpoch();
                    const int secondsToMinute = secondsSinceEpoch % 60;

                    if (secondsToMinute == 5)
                    {
                        const auto auctionScrapeBegin = Timing::Now();
                        auctionHouse.ScrapeAuction();
                        const auto auctionScrapeEnd = Timing::Now();

                        Log::Println();
                        std::cout << "Scraping auction house data: ";
                        Timing::Log(auctionScrapeBegin, auctionScrapeEnd);
                        Log::Println();

                        Timing::Sleep(1'500);
                    }
                    Timing::Sleep(100);
                }
            }).detach();

    return 0;
}

long long PricingLibrary::GetPrice(const std::string& itemName)
{
    return PricingLibrary::GetPrice(Conversions::ToWideString(itemName));
}

long long PricingLibrary::GetPrice(const std::wstring& itemName)
{
    return auctionHouse.LookupPrice(itemName);
}

std::vector<std::unique_ptr<Item>> PricingLibrary::GetFlips()
{
    Log::Println();

    const auto callBegin = Timing::Now();
    std::string& response = PricingLibrary::caller.Call();
    const auto callEnd = Timing::Now();
    std::cout << "Calling api: ";
    Timing::Log(callBegin, callEnd);

    try 
    {
        const auto setupBegin = Timing::Now();
        Json json(response);

        const auto setupEnd = Timing::Now();
        std::cout << "Setting up: ";
        Timing::Log(setupBegin, setupEnd);

        const auto arrayGetBegin = Timing::Now();
        simdjson::ondemand::array auctions = json.GetObject()["auctions"].get_array();
        const auto arrayGetEnd = Timing::Now();
        std::cout << "Getting array: ";
        Timing::Log(arrayGetBegin, arrayGetEnd);

        const auto filteringAuctionsBegin = Timing::Now();
        std::vector<std::unique_ptr<Item>> bins = Parsing::RemoveAuctions(auctions);
        const auto filteringAuctionsEnd = Timing::Now();
        std::cout << "Removing auctions: ";
        Timing::Log(filteringAuctionsBegin, filteringAuctionsEnd);

        const auto removingOldBinsBegin = Timing::Now();
        bins = Parsing::RemoveOldBins(std::move(bins));
        const auto removingOldBinsEnd = Timing::Now();
        std::cout << "Removing old bins: ";
        Timing::Log(removingOldBinsBegin, removingOldBinsEnd);

        const auto findingFlipsBegin = Timing::Now();
        bins = Parsing::FindFlips(std::move(bins), PricingLibrary::auctionHouse, PricingLibrary::minimumProfit);
        const auto findingFlipsEnd = Timing::Now();
        std::cout << "Finding flips: ";
        Timing::Log(findingFlipsBegin, findingFlipsEnd);

        return bins;
    }
    catch (const simdjson::simdjson_error& e)
    {
        Log::Error(e.what());
        return std::vector<std::unique_ptr<Item>>();
    }
}

void PricingLibrary::CleanUp()
{
    curl_global_cleanup();
}
