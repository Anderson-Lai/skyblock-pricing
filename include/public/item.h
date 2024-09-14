#pragma once
#include <string>

class Item
{
    Item(const std::string_view auctionId, const std::string_view rarity, const std::string_view category,
            const std::string_view itemName, const std::string_view itemLore, const long long price);
    void CleanName();
private:
    std::string m_auctionId;
    std::string m_rarity;
    std::string m_category; // weapon, armor, misc, etc.
    std::wstring m_itemName;
    std::wstring m_itemLore;
    long long m_price;
    long long m_profit;
};

