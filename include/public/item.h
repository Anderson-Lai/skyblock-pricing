#pragma once
#include <string>
#include "auctionhouse.h"
#include <array>

class Item
{
public:
    Item(const std::string_view uuid, const std::string_view rarity, const std::string_view category,
            const std::string_view itemName, const std::string_view itemLore, const long long price,
            const long long startTime);
    void CalculateProfit(const AuctionHouse& auctionHouse);
    const std::wstring& GetName() const;
    long long GetPrice() const;
    long long GetProfit() const;
    const std::string& GetUuid() const;
    long long GetStartTime() const;
private:
    void CleanName();
    void LowerRarity();
    void RemoveTrailingSpaces();
private:
    static bool IsImportantCharacter(const wchar_t character);
    static bool IsDuplicateReforge(const std::wstring& word);
    static bool IsReforge(const std::wstring& word);
    static bool IsRecombobulated(const std::wstring& itemLore);
private:
    std::wstring m_itemName;
    std::wstring m_itemLore;
    std::string m_uuid;
    std::string m_rarity;
    std::string m_category; // weapon, armor, misc, etc.
    long long m_price;
    long long m_profit;
    // in seconds since epoch
    long long m_startTime;
private:
    static const std::array<wchar_t, 68> s_importantCharacters;
    static const std::array<std::wstring, 10> s_dupliateReforges;
    static const std::array<std::wstring, 114> s_reforges;
    static const std::array<std::string, 8> s_rarities;
};

