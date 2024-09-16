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
            if (!obj["bin"].pages().get_bool())
            {
                continue;
            }
            const std::string_view uuid = obj["uuid"].pages().get_string();
            const std::string_view rarity = obj["tier"].pages().get_string();
            const std::string_view category = obj["category"].pages().get_string();  
            const std::string_view itemName = obj["item_name"].pages().get_string();
            const std::string_view itemLore = obj["item_lore"].pages().get_string();
            const long long price = obj["starting_bid"].pages().get_int64();
            
            recentFlips.emplace_back(std::make_unique<Item>(uuid, rarity, category, itemName, itemLore, price));
        }
        catch (const simdjson::simdjson_error& e) 
        {
            Log::Error(std::format("Error while filtering old bins: {}", e.what()));
        }
    }
    return recentFlips;
}
