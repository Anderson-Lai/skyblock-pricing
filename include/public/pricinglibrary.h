#pragma once
#include <vector>
#include <memory>
#include "item.h"

namespace PricingLibrary
{
    int Initialize();
    long long GetPrice(const std::string& itemName);
    long long GetPrice(const std::wstring& itemName);
    std::vector<std::unique_ptr<Item>> GetFlips();
    void CleanUp();
}
