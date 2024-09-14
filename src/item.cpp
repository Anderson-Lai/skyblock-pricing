#include "item.h"
#include "conversions.h"
#include <cstdint>

Item::Item(const std::string_view auctionId, const std::string_view rarity, const std::string_view category, 
        const std::string_view itemName, const std::string_view itemLore, const long long price)
    : m_auctionId(auctionId), m_rarity(rarity), m_category(category), m_price(price), m_profit(INT64_MIN)
{
    std::string name(itemName);
    m_itemName = Conversions::ToWideString(name);

    std::string lore(itemLore);
    m_itemLore = Conversions::ToWideString(lore);
}
