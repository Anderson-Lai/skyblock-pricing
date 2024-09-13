#pragma once
#include "item.h"
#include <vector>
#include <memory>

namespace PricingLibrary
{
    void Initialize();
    const std::vector<std::unique_ptr<Item>>& GetFlips();
    void CleanUp();
}
