#include "parsing.h"
#include "log.h"
#include <format>

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
