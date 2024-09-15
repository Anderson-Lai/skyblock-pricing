#pragma once
#include <string>
#include "auctionhouse.h"
#include <array>

class Item
{
    Item(const std::string_view auctionId, const std::string_view rarity, const std::string_view category,
            const std::string_view itemName, const std::string_view itemLore, const long long price);
    void CalculateProfit(const AuctionHouse& auctionHouse);
private:
    void CleanName();
    void LowerRarity();
private:
    bool IsImportantCharacter(const wchar_t character);
    bool IsDuplicateReforge(const std::wstring& word);
    bool IsReforge(const std::wstring& word);
    bool IsRecombobulated(const std::wstring& itemLore);
private:
    std::string m_auctionId;
    std::string m_rarity;
    std::string m_category; // weapon, armor, misc, etc.
    std::wstring m_itemName;
    std::wstring m_itemLore;
    long long m_price;
    long long m_profit;
private:
    static const std::array<wchar_t, 68> s_importantCharacters;
    static const std::array<std::wstring, 10> s_dupliateReforges;
    static const std::array<std::wstring, 114> s_reforges;
    static const std::array<std::string, 8> s_rarities;
};

