#pragma once
#include "item.h"
#include <memory>
#include "simdjson.h"

namespace Parsing
{
    std::vector<std::unique_ptr<Item>> RemoveAuctions(simdjson::ondemand::array& auctions);
    // remove bins that have not been created in the past minute
    std::vector<std::unique_ptr<Item>> RemoveOldBins(std::vector<std::unique_ptr<Item>>&& bins);
}
