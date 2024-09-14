#include "pricinglibrary.h"
#include "curl/curl.h"
#include <clocale>
#include "api.h"
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
        std::string& response = caller.Call();

        simdjson::ondemand::parser parser;
        simdjson::padded_string jsonString(response);
        simdjson::ondemand::document doc = parser.iterate(jsonString);
        simdjson::ondemand::object jsonObject = doc.get_object();

        simdjson::ondemand::array auctions = jsonObject["auctions"].get_array();


        Timing::Sleep(100);
    }
}

namespace PricingLibrary
{
    inline std::vector<std::unique_ptr<Item>> flips;
}

const std::vector<std::unique_ptr<Item>>& PricingLibrary::GetFlips()
{
    return flips; 
}

void PricingLibrary::CleanUp()
{
    curl_global_cleanup();
}
