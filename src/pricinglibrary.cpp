#include "pricinglibrary.h"
#include "conversions.h"
#include "curl/curl.h"
#include <clocale>
#include "api.h"
#include "log.h"
#include "parsing.h"
#include "timing.h"
#include "json.h"

namespace PricingLibrary
{
    AuctionHouse auctionHouse;
    Api caller("https://api.hypixel.net/v2/skyblock/auctions?page=0");
    const std::string fileName = "lbin.json";
}

void PricingLibrary::Initialize()
{
    curl_global_init(CURL_GLOBAL_DEFAULT); 
    std::setlocale(LC_ALL, "en_US.utf8");
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
