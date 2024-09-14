#include "pricinglibrary.h"
#include "curl/curl.h"
#include <clocale>
#include "api.h"
#include "log.h"
#include "simdjson.h"
#include "timing.h"

void PricingLibrary::Initialize()
{
    curl_global_init(CURL_GLOBAL_DEFAULT); 
    std::setlocale(LC_ALL, "en_US.utf8");
}

void PricingLibrary::Run()
{
    Api caller("https://api.hypixel.net/v2/skyblock/auctions?page=0");

    while (true)
    {
        const auto callBegin = Timing::Now();
        std::string& response = caller.Call();
        const auto callEnd = Timing::Now();

        std::cout << "Calling api: ";
        Timing::Log(callBegin, callEnd);
        
        const auto setupBegin = Timing::Now();
        simdjson::ondemand::parser parser;
        simdjson::padded_string jsonString(response);
        simdjson::ondemand::document doc = parser.iterate(jsonString);
        simdjson::ondemand::object jsonObject = doc.get_object();
        const auto setupEnd = Timing::Now();

        std::cout << "Setting up: ";
        Timing::Log(setupBegin, setupEnd);

        const auto arrayGetBegin = Timing::Now();
        simdjson::ondemand::array auctions = jsonObject["auctions"].get_array();
        const auto arrayGetEnd = Timing::Now();

        std::cout << "Getting array: ";
        Timing::Log(arrayGetBegin, arrayGetEnd);

        Log::Println();
        Timing::Sleep(100);
    }
}

namespace PricingLibrary
{
    inline std::vector<std::unique_ptr<Item>> flips;
}

std::vector<std::unique_ptr<Item>>& PricingLibrary::GetFlips()
{
    return flips; 
}

void PricingLibrary::CleanUp()
{
    curl_global_cleanup();
}
