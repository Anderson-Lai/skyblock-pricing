#include "pricinglibrary.h"
#include "curl/curl.h"
#include <clocale>
#include "api.h"
#include <iostream>

void PricingLibrary::Initialize()
{
    curl_global_init(CURL_GLOBAL_DEFAULT); 
    std::setlocale(LC_ALL, "en_US.utf8");
}

void PricingLibrary::Run()
{
    Api caller("https://api.hypixel.net/v2/skyblock/auctions?page=0");
    std::cout << caller.Call() << "\n";
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
