#include "parsing.h"
#include "log.h"
#include <format>
#include "timing.h"

std::vector<std::unique_ptr<Item>> Parsing::RemoveAuctions(simdjson::ondemand::array& auctions)
{
    std::vector<std::unique_ptr<Item>> recentFlips;
    for (simdjson::ondemand::object obj : auctions)
    {
        try 
        {
            if (!obj["bin"].get_bool())
            {
                continue;
            }
            const std::string_view uuid = obj["uuid"].get_string();
            const std::string_view rarity = obj["tier"].get_string();
            const std::string_view category = obj["category"].get_string();
            const std::string_view itemName = obj["item_name"].get_string();
            const std::string_view itemLore = obj["item_lore"].get_string();
            const long long price = obj["starting_bid"].get_int64();
            const long long timeStarted = obj["start"].get_int64() / 1'000;
            recentFlips.emplace_back(std::make_unique<Item>(uuid, rarity, category, itemName, itemLore, price, timeStarted));
        }
        catch (const simdjson::simdjson_error& e) 
        {
            Log::Error(std::format("Error while filtering old bins: {}", e.what()));
        }
    }
    return recentFlips;
}

std::vector<std::unique_ptr<Item>> Parsing::RemoveOldBins(std::vector<std::unique_ptr<Item>>&& bins)
{
    std::vector<std::unique_ptr<Item>> filtered;
    filtered.reserve(bins.size());

    const unsigned long long secondsSinceEpoch = Timing::SecondsSinceEpoch();
    for (auto& bin : bins)
    {
        if (secondsSinceEpoch - bin->GetStartTime() < 65)
        {
            filtered.emplace_back(std::move(bin));
        }
    }

    filtered.shrink_to_fit();
    return filtered;
}
