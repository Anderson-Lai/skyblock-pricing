#include "parsing.h"
#include "log.h"

std::vector<std::unique_ptr<Item>> Parsing::RemoveAuctions(simdjson::ondemand::array& array)
{
    std::vector<std::unique_ptr<Item>> recentFlips;
    for (simdjson::ondemand::object obj : array)
    {
        try 
        {
            if (!obj["bin"].value().get_bool())
            {
                continue;
            }
            const std::string_view uuid = obj["uuid"].value().get_string();
            const std::string_view rarity = obj["tier"].value().get_string();
            const std::string_view category = obj["category"].value().get_string();  
            const std::string_view itemName = obj["item_name"].value().get_string();
            const std::string_view itemLore = obj["item_lore"].value().get_string();
            const long long price = obj["starting_bid"].value().get_int64();
            
            recentFlips.emplace_back(std::make_unique<Item>(uuid, rarity, category, itemName, itemLore, price));
        }
        catch (...)
        {
            Log::Error("Error while filtering old bins");
        }
    }
    return recentFlips;
}
