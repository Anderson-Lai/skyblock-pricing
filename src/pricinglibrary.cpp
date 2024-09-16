#include "pricinglibrary.h"
#include "conversions.h"
#include "curl/curl.h"
#include <clocale>
#include "api.h"
#include "log.h"
#include "timing.h"
#include "json.h"

void PricingLibrary::Initialize()
{
    curl_global_init(CURL_GLOBAL_DEFAULT); 
    std::setlocale(LC_ALL, "en_US.utf8");
}

namespace PricingLibrary
{
    AuctionHouse auctionHouse;
    std::vector<std::unique_ptr<Item>> flips;
}

long long PricingLibrary::GetPrice(const std::string& itemName)
{
    return PricingLibrary::GetPrice(Conversions::ToWideString(itemName));
}

long long PricingLibrary::GetPrice(const std::wstring& itemName)
{
    return auctionHouse.LookupPrice(itemName);
}

std::vector<std::unique_ptr<Item>>& PricingLibrary::GetFlips()
{
    return flips; 
}

void PricingLibrary::Run()
{
    Api caller("https://api.hypixel.net/v2/skyblock/auctions?page=0");
    const std::string fileName = "lbin.json";

    while (true)
    {
        const auto callBegin = Timing::Now();
        std::string& response = caller.Call();
        const auto callEnd = Timing::Now();

        std::cout << "Calling api: ";
        Timing::Log(callBegin, callEnd);
        
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

        Log::Println();
        Timing::Sleep(100);
    }
}

void PricingLibrary::CleanUp()
{
    curl_global_cleanup();
}
