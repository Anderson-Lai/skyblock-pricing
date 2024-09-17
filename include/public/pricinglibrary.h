#pragma once
#include "item.h"
#include <vector>
#include <memory>

namespace PricingLibrary
{
    int Initialize();
    long long GetPrice(const std::string& itemName);
    long long GetPrice(const std::wstring& itemName);
    std::vector<std::unique_ptr<Item>> GetFlips();
    void CleanUp();
}
